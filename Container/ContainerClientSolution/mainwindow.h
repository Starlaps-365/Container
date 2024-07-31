#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QThread;
class QSpinBox;
class QPushButton;
class QListWidget;
class QTextEdit;
class Container;
class Pallet;
class Serialize;
class UnallocatedContainer;
class UnallocatedMemento;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addContainer();
    void moveContainer();
    void postXML();
    void displayXmlText(QString s);
    void displayLinkErrorMessage(QString msg);
    void doBackupRestore();

private:
    void closeEvent(QCloseEvent *event);

    QSpinBox *box_breadth, *box_length, *box_height, *box_weight;
    QSpinBox *cylinder_diameter, *cylinder_height, *cylinder_weight;
    QPushButton *buttonAddBox, *buttonAddCylinder;
    QListWidget *displayUnallocated;
    QSpinBox *palletNumber;
    QPushButton *buttonMoveToPallet, *buttonBackupRestore;
    QPushButton *buttonPostXML;
    QTextEdit *displayPalletXML;
    UnallocatedContainer *unallocatedContainers;
    QMap<int, Pallet*> *pallets;
    QThread *thread;
    Serialize *serialise;
    UnallocatedMemento *memento;
};

#endif // MAINWINDOW_H
