#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    this->setWindowTitle("Memory Management Algorithms");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);

    this->setWindowTitle("Graph Centrality");
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#define inf 1e9

using namespace std;


Graph * readFile (string path ){

    ifstream file;
    file.open(path);
    int n , m;

    // n ---> number of nodes  , m ---> number of edges
    file>>n>>m;

    //Creating a graph
    Graph *G1 = new Graph(n,m);
    G1->adj_list.resize(n);

    int a, b, c;

    // Building the adjacency List
    for (int i=0; i<m ;i++){
        file>>a>>b>>c;
        G1->adj_list[a].push_back(make_pair(b,c));
        G1->adj_list[b].push_back(make_pair(a,c));
    }
    file.close();
    return G1;
}


void MainWindow::InitUI()
{
/*
    int n , m;
    browsefun();
    Graph *G1 = readFile(directory,n,m);

    //sending my Graph as a parameter to the GraphWidget to be drawen
     widget = new GraphWidget(0,G1);
*/
    widget = new GraphWidget(0);


    //remove border of the Graph layout
    widget->setStyleSheet("border:0px;");

    QFont font1("Volkhov",13,QFont::Light,true);
    QFont font2("Volkhov",11,QFont::Light,true);


    //Input file button -> browse
    browse = new QPushButton();
    browse->setText("Browse File");
    browse->setMinimumHeight(35);
    browse->setFont(font2);

    //combobox labels
    AlgorithmLabel = new QLabel("Centrality Property :");
    AlgorithmLabel->setFont(font1);

    //combox
    algorithm = new QComboBox;
    algorithm->addItem("Degree Centrality");
    algorithm->addItem("Closeness Centrality");
    algorithm->addItem("Betweenness Centrality");

    algorithm->setMinimumHeight(35);
    algorithm->setFont(font2);

    //Simulate button
    Simulate = new QPushButton();
    Simulate->setText("Simulate");
    Simulate->setMinimumHeight(35);
    Simulate->setFont(font2);



    //page title
    firstPagetitle = new QLabel("Graph Centrality Visulization");
    QFont font("Volkhov",15,QFont::Bold,true);
    firstPagetitle->setFont(font);

    //init input layout
    inputLayout = new QHBoxLayout;

    //adding to form layout
    firstInputPage = new QFormLayout;
    firstInputPage->setContentsMargins(10,10,10,10);
    firstInputPage->setSpacing(20);
    firstInputPage->addRow(firstPagetitle);


    firstInputPage->addRow(browse);
    firstInputPage->addRow(AlgorithmLabel,algorithm);
    firstInputPage->addRow(Simulate);

    GraphLayout = new QHBoxLayout;
    GraphLayout -> addWidget(widget);

    //add form lautout to input layout
    inputLayout->addItem(firstInputPage);

    mainLayout = new QHBoxLayout;
    mainLayout->addItem(inputLayout);
    mainLayout->addItem(GraphLayout);

    //adding main layout to central widget of window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    //making signals for buttons
    QObject::connect(browse,SIGNAL(clicked()),this,SLOT(browsefun()));
    QObject::connect(Simulate,SIGNAL(clicked()),this,SLOT(ShowCentrality()));

}

void MainWindow::browsefun()
{

    QString filename = QFileDialog::getOpenFileName(this,
                                                 tr("Open File"),
                                                 "H:\Nader 2014\CSE_1stYear\2nd Term \Data Structure\Project",
                                                    "Text files (*.txt)");

    string directory = filename.toStdString();

    DrawGraph(directory);
}

void MainWindow :: DrawGraph(string directory) {

    G1 = new Graph(0,0);
    G1 = readFile(directory);


    //sending my Graph as a parameter to the GraphWidget to be drawen
    widget->Draw(0,G1);
}
void MainWindow :: ShowCentrality(){

    QString algo_str = algorithm->currentText();
    widget->ShowCentrality(0,G1,algo_str);
}
