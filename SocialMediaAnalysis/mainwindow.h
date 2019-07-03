#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"

#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QFileDialog>

#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int main(int argc, char *argv[]);

private slots:
    void InitUI();
    void browsefun();
    void DrawGraph(string directory) ;
    void ShowCentrality();
private:

    Ui::MainWindow *ui;
    QWidget *centralWidget;

    //Graph widget
    GraphWidget *widget;

    //colors and pallete
    QPalette *mainPalette;

    //Layouts
    QFormLayout *firstInputPage;
    QHBoxLayout *mainLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *GraphLayout;
    //PushButtons
    QPushButton *browse;
    QPushButton *Simulate;
    //label
    QLabel *firstPagetitle;
    QLabel *AlgorithmLabel;

    //combobox
    QComboBox *algorithm;


    Graph *G1;
};

#endif // MAINWINDOW_H
