#include "mainwindow.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QRegularExpression>
#include <QtWidgets>
#include <QStandardItemModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    tcpServer{nullptr},
    tcpSocket{nullptr},
    model{new QStandardItemModel(this)},
    buttonStartListening{new QPushButton("Start listening")},
    labelStatus{new QLabel("Status")},
    view{new QTableView}
{
    QGridLayout *layout{new QGridLayout()};
    layout->addWidget(buttonStartListening, 0, 0);
    layout->addWidget(labelStatus, 0, 1);
    layout->addWidget(view, 1, 0, 1, 2);

    QWidget *widget{new QWidget()};
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle("Container server");
    setMinimumSize(800, 100);

    setModelHeadings();
    adjustSize();

    view->setModel(model);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(buttonStartListening, SIGNAL(clicked()), this, SLOT(startListening()));
}

MainWindow::~MainWindow()
{
    if (tcpServer!=nullptr)
    {
        tcpServer->close();
        tcpServer->deleteLater();
    }
    if (tcpSocket!=nullptr)
    {
        tcpSocket->close();
        tcpSocket->deleteLater();
    }
}

void MainWindow::startListening()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 6164))
    {
        QMessageBox::critical(this, "Container Server", QString("Unable to start the server: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }
    labelStatus->setText("Listening on port 6164");
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::handleConnection);
}

void MainWindow::handleConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MainWindow::readyRead()
{
    model->clear();
    setModelHeadings();

    QByteArray data{tcpSocket->readAll()};
    reader.addData(data);

    bool collect{false};
    QStringList detail;
    QString palletNumber;
    QRegularExpression re("20[0-9]{2}/(0[1-9]|1[0-2])/[BC][1-9]\\d{0,3}");

    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType tt{reader.readNext()};
        switch (tt)
        {
            case QXmlStreamReader::StartElement:
            {
                if (reader.name().toString()=="pallet")
                {
                    QXmlStreamAttributes attrs{reader.attributes()};
                    palletNumber = attrs.value("number").toString();
                }
                else if (reader.name().toString()=="Box" || reader.name().toString()=="Cylinder")
                {
                    detail << reader.name().toString();
                }
                else if (reader.name().toString()=="code" || reader.name().toString()=="height" || reader.name().toString()=="breadth"  || reader.name().toString()=="weight" || reader.name().toString()=="diameter" || reader.name().toString()=="length")
                {
                    detail << reader.name().toString();
                    collect=true;
                }
                break;
            }
            case QXmlStreamReader::Characters:
            {
                if (collect)
                    detail << reader.text().toString();
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                if (reader.name().toString()=="code" || reader.name().toString()=="height" || reader.name().toString()=="breadth"  || reader.name().toString()=="weight" || reader.name().toString()=="diameter" || reader.name().toString()=="length")
                    collect=false;
                else if (reader.name().toString()=="Box" || reader.name().toString()=="Cylinder")
                {
                    QList<QStandardItem*> row;
                    QStandardItem *itemPalletNumber{new QStandardItem(palletNumber)};
                    QStandardItem *itemContainer{new QStandardItem(detail.at(0))};
                    QStandardItem *itemCode{nullptr};
                    QStandardItem *itemHeight{nullptr};
                    QStandardItem *itemBreadthDiameter{nullptr};
                    QStandardItem *itemLength{nullptr};
                    QStandardItem *itemWeight{nullptr};

                    for (int i=1; i< detail.size(); i+=2)
                    {
                        if (detail.at(i) == "code")
                        {
                            QString c = detail.at(i+1);
                            if (!re.match(c).hasMatch())
                                c = "****";
                            itemCode = new QStandardItem(c);
                        }
                        else if (detail.at(i) == "height")
                            itemHeight = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "breadth" || detail.at(i) == "diameter")
                            itemBreadthDiameter = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "length")
                            itemLength = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "weight")
                            itemWeight = new QStandardItem(detail.at(i+1));
                    }

                    if (detail.at(0) == "Box")
                        row << itemPalletNumber << itemContainer << itemCode << itemHeight << itemBreadthDiameter << itemLength << itemWeight;
                    else if (detail.at(0) == "Cylinder")
                        row << itemPalletNumber << itemContainer << itemCode << itemHeight << itemBreadthDiameter << nullptr << itemWeight;
                    model->appendRow(row);
                    detail.clear();
                }
                break;
            }
            default:
                break;
        }
    }
    reader.clear();
}

void MainWindow::setModelHeadings()
{
    QStringList headerRow;
    headerRow.append("Pallet");
    headerRow.append("Container");
    headerRow.append("Code");
    headerRow.append("Height");
    headerRow.append("Breadth/Diameter");
    headerRow.append("Length");
    headerRow.append("Weight");
    model->setHorizontalHeaderLabels(headerRow);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int answer;
    answer = QMessageBox::warning(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
