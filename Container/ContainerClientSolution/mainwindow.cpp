#include "mainwindow.h"
#include <QListWidgetItem>
#include <QThread>
#include <QtWidgets>
#include "box.h"
#include "cylinder.h"
#include "containerfactory.h"
#include "pallet.h"
#include "serialize.h"
#include "unallocatedcontainer.h"
#include "unallocatedmemento.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    box_breadth{new QSpinBox()},
    box_length{new QSpinBox()},
    box_height{new QSpinBox()},
    box_weight{new QSpinBox()},
    cylinder_diameter{new QSpinBox()},
    cylinder_height{new QSpinBox()},
    cylinder_weight{new QSpinBox()},
    buttonAddBox{new QPushButton("Add box")},
    buttonAddCylinder{new QPushButton("Add cylinder")},
    displayUnallocated{new QListWidget},
    palletNumber{new QSpinBox()},
    buttonMoveToPallet{new QPushButton("Move to pallet")},
    buttonBackupRestore{new QPushButton("Backup")},
    buttonPostXML{new QPushButton("Post XML to network")},
    displayPalletXML{new QTextEdit},
    unallocatedContainers{new UnallocatedContainer},
    pallets{new QMap<int, Pallet*>},
    thread{nullptr},
    serialise{nullptr},
    memento{nullptr}
{
    // Tab 1 - Containers
    QGroupBox *boxGroup{new QGroupBox("Box")};
    QGridLayout *boxlayout{new QGridLayout};
    boxGroup->setLayout(boxlayout);
    QLabel *labelBBreadth{new QLabel("Breadth")};
    boxlayout->addWidget(labelBBreadth, 0, 0);
    boxlayout->addWidget(box_breadth, 0, 1);
    QLabel *labelBLength{new QLabel("Length")};
    boxlayout->addWidget(labelBLength, 1, 0);
    boxlayout->addWidget(box_length, 1, 1);
    QLabel *labelBHeight{new QLabel("Height")};
    boxlayout->addWidget(labelBHeight, 2, 0);
    boxlayout->addWidget(box_height, 2, 1);
    QLabel *labelBWeight{new QLabel("Weight")};
    boxlayout->addWidget(labelBWeight, 3, 0);
    boxlayout->addWidget(box_weight, 3, 1);
    boxlayout->addWidget(buttonAddBox, 4, 0, 1, 2);
    buttonAddBox->setObjectName("BoxButton");

    QGroupBox *cylinderGroup{new QGroupBox("Cylinder")};
    QGridLayout *cylinderlayout{new QGridLayout};
    cylinderGroup->setLayout(cylinderlayout);
    QLabel *labelCDiameter{new QLabel("Diameter")};
    cylinderlayout->addWidget(labelCDiameter, 0, 0);
    cylinderlayout->addWidget(cylinder_diameter, 0, 1);
    QLabel *labelCHeight{new QLabel("Height")};
    cylinderlayout->addWidget(labelCHeight, 1, 0);
    cylinderlayout->addWidget(cylinder_height, 1, 1);
    QLabel *labelCWeight{new QLabel("Weight")};
    cylinderlayout->addWidget(labelCWeight, 2, 0);
    cylinderlayout->addWidget(cylinder_weight, 2, 1);
    QLabel *labelBlank1{new QLabel};
    cylinderlayout->addWidget(labelBlank1, 3, 0);
    cylinderlayout->addWidget(buttonAddCylinder, 4, 0, 1, 2);
    buttonAddCylinder->setObjectName("CylinderButton");

    QWidget *bottomWidget{new QWidget};
    QGridLayout *bottomLayout{new QGridLayout};
    bottomWidget->setLayout(bottomLayout);
    QLabel *labelListOf{new QLabel("List of unallocated containers")};
    bottomLayout->addWidget(labelListOf, 0, 0);
    QLabel *labelClickOn{new QLabel("Click on item in list, choose a pallet number, and Move the container to that pallet")};
    labelClickOn->setWordWrap(true);
    bottomLayout->addWidget(displayUnallocated, 1, 0, 5, 1);
    bottomLayout->addWidget(labelClickOn, 1, 1);
    bottomLayout->addWidget(palletNumber, 2, 1);
    palletNumber->setMinimum(1);
    bottomLayout->addWidget(buttonMoveToPallet, 3, 1);
    QLabel *labelBlank2{new QLabel};
    cylinderlayout->addWidget(labelBlank2, 4, 1);
    bottomLayout->addWidget(buttonBackupRestore, 5, 1);

    QWidget *containerWidget{new QWidget};
    QGridLayout *tabLayoutContainer{new QGridLayout};
    tabLayoutContainer->addWidget(boxGroup, 0, 0);
    tabLayoutContainer->addWidget(cylinderGroup, 0, 1);
    tabLayoutContainer->addWidget(bottomWidget, 1, 0, 1, 2);
    containerWidget->setLayout(tabLayoutContainer);

    // Tab 2 - Post XML
    QWidget *postWidget{new QWidget};
    QVBoxLayout *postLayout{new QVBoxLayout};
    postWidget->setLayout(postLayout);
    postLayout->addWidget(buttonPostXML);
    postLayout->addWidget(displayPalletXML);

    // setting central widget
    QTabWidget *tabs{new QTabWidget};
    tabs->addTab(containerWidget, "Containers");
    tabs->addTab(postWidget, "Post XML");
    setCentralWidget(tabs);

    connect(buttonAddBox, SIGNAL(clicked()), this, SLOT(addContainer()));
    connect(buttonAddCylinder, SIGNAL(clicked()), this, SLOT(addContainer()));
    connect(buttonMoveToPallet, SIGNAL(clicked()), this, SLOT(moveContainer()));
    connect(buttonPostXML, SIGNAL(clicked()), this, SLOT(postXML()));
    connect(buttonBackupRestore, SIGNAL(clicked()), this, SLOT(doBackupRestore()));
}

MainWindow::~MainWindow()
{
    delete unallocatedContainers;
    while (pallets->size()>0)
    {
        Pallet *tempPallet = pallets->take(pallets->firstKey());
        delete tempPallet;
    }
    delete pallets;
    if ((thread != nullptr) && (thread->isRunning()))
    {
        thread->quit();
        thread->deleteLater();
        serialise->deleteLater();
    }
    if (memento != nullptr)
        delete memento;
}

void MainWindow::addContainer()
{
    QString objType = QObject::sender()->objectName();
    int data[4];
    if (objType == "BoxButton")
    {
        data[0] = box_breadth->value();
        data[1] = box_length->value();
        data[2] = box_height->value();
        data[3] = box_weight->value();
        box_breadth->setValue(0);
        box_length->setValue(0);
        box_height->setValue(0);
        box_weight->setValue(0);
    }
    else if (objType == "CylinderButton")
    {
        data[0] = cylinder_diameter->value();
        data[1] = cylinder_height->value();
        data[2] = cylinder_weight->value();
        data[3] = 0;
        cylinder_diameter->setValue(0);
        cylinder_height->setValue(0);
        cylinder_weight->setValue(0);
    }
    ContainerFactory cf;
    Container *c = cf.createContainer(objType, data);
    unallocatedContainers->insert(c->getCode(), c);
    new QListWidgetItem(c->getCode(), displayUnallocated);
}

void MainWindow::moveContainer()
{
    if (displayUnallocated->currentItem() != nullptr)
    {
        QString code{displayUnallocated->currentItem()->text()};
        int number{palletNumber->value()};
        if (pallets->contains(number))
        {
            Pallet *temp{pallets->value(number)};
            temp->append(unallocatedContainers->value(code));
            pallets->insert(number, temp);
        }
        else
        {
            Pallet *p{new Pallet};
            p->append(unallocatedContainers->value(code));
            pallets->insert(number, p);
        }
        unallocatedContainers->remove(code);
        displayUnallocated->takeItem(displayUnallocated->currentRow());
    }
}

void MainWindow::postXML()
{
    displayPalletXML->clear();
    serialise = new Serialize(pallets);
    thread = new QThread();
    serialise->moveToThread(thread);
    connect(serialise, SIGNAL(xmlText(QString)), this, SLOT(displayXmlText(QString)));
    connect(thread, SIGNAL(started()), serialise, SLOT(doSerialize()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), serialise, SLOT(deleteLater()));
    connect(serialise, SIGNAL(linkError(QString)), this, SLOT(displayLinkErrorMessage(QString)));
    thread->start();
}

void MainWindow::displayXmlText(QString s)
{
    displayPalletXML->append(s);
}

void MainWindow::displayLinkErrorMessage(QString msg)
{
   displayPalletXML->append(msg) ;
}

void MainWindow::doBackupRestore()
{
    if (buttonBackupRestore->text() == "Backup")
    {
        memento = unallocatedContainers->createMemento();
        buttonBackupRestore->setText("Restore");
    }
    else //Restore button
    {
        displayUnallocated->clear();
        unallocatedContainers->setMemento(memento);
        foreach (QString s, unallocatedContainers->keys())
        {
            new QListWidgetItem(s, displayUnallocated);
        }
        buttonBackupRestore->setText("Backup");
    }
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
