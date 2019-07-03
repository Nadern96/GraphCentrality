#include "mainwindow.h"
#include <QApplication>



#include <QTime>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //GraphWidget *widget = new GraphWidget;

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);

/*
    //w.setCentralWidget(widget);
    // n ---> number of nodes  , m ---> number of edges

    int n , m;

    //Graph G1
    Graph *G1 = readFile("H:\\Nader 2014\\CSE_1stYear\\2nd Term \\Data Structure\\Project\\inputFile.txt",n,m);

    widget = new GraphWidget(0,G1);


    //Displays the nodes connected to each node
    for (int i=0; i< n; i++){
        cout<<"The nodes directly connected to node "<<i<<" are: ";
        for(int j=0; j<G1->Get_AdjList()[i].size(); j++){
            cout<<"(node: "<<G1->Get_AdjList()[i][j].first<<" , weight: "<<G1->Get_AdjList()[i][j].second<<") "<<endl;
        }
        cout<<"\n";
    }


    vector<int> Degrees (n);
    Degrees = G1->Degree_Centrality();

    for (auto i : Degrees)
        cout<<Degrees[i]<<endl;

    cout<<endl;

    vector<float> Closeness (n);
    Closeness = G1->Closeness_Centrality();

    for (int i =0 ; i< Closeness.size(); i++)
        cout<<Closeness[i]<<endl;

    cout<<endl;
  */
  w.show();
    return a.exec();
}
