/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QVector>
//! [0]
GraphWidget::GraphWidget(QWidget *parent )
    : QGraphicsView(parent), timerId(0)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //Control Graph layoutSize
    scene->setSceneRect(-200, -200, 1100, 850);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
//! [0]

    ;
//! [1]

}
//! [1]

void GraphWidget::Draw(QWidget *parent , Graph *G1 ){

    QList<QGraphicsItem*> all = scene->items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        if(gi->parentItem()==NULL) {
            delete gi;
        }
    }

    //vector of Nodes
    QVector<Node*> Nodes;

    QString tooltiptext ;
    //Creating Nodes and append to vector
    for(int i=0 ; i<G1->Get_numNodes(); i++){
        Nodes.append(new Node(this));
        scene->addItem(Nodes[i]);

        tooltiptext = "<html><body><h3>Node " +  QString::number(i) +"</h3>"
                       "</body></html>";
        Nodes[i]->QGraphicsItem::setToolTip(tooltiptext);
        Nodes[i]->QGraphicsItem::update();

    }

    for(int i=0 ; i<G1->Get_AdjList().size();i++){
        for(int j=0;j<G1->Get_AdjList()[i].size(); j++){
            scene->addItem(new Edge(Nodes[i],Nodes[G1->Get_AdjList()[i][j].first]));
        }
    }
    this->shuffle();


}

void GraphWidget:: ShowCentrality(QWidget *parent , Graph *G1  ,QString algo_str){

    QList<QGraphicsItem*> all = scene->items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        if(gi->parentItem()==NULL) {
            delete gi;
        }
    }
    vector<float> output (G1->Get_numNodes());

    if (algo_str == "Degree Centrality")
        output = G1->Degree_Centrality();
    else if (algo_str == "Closeness Centrality")
        output = G1->Closeness_Centrality();
    else if (algo_str == "Betweenness Centrality")
        output = G1->Betweenness_Centrality();

    //vector of Nodes
    QVector<Node*> Nodes;

    QString tooltiptext ;

    //Creating Nodes and append to vector
    for(int i=0 ; i<G1->Get_numNodes(); i++){
        Nodes.append(new Node(this));
        scene->addItem(Nodes[i]);
        tooltiptext = "<html><body><h3>Node " +  QString::number(i) +"</h3>"
                       "</body></html>";
        Nodes[i]->QGraphicsItem::setToolTip(tooltiptext);
        Nodes[i]->QGraphicsItem::update();

        qreal scale = output[i];
        if (algo_str == "Closeness Centrality")
              scale = output[i]*10;
        Nodes[i]->setScale(scale);


    }
    for(int i=0 ; i<G1->Get_AdjList().size();i++){
        for(int j=0;j<G1->Get_AdjList()[i].size(); j++){
            scene->addItem(new Edge(Nodes[i],Nodes[G1->Get_AdjList()[i][j].first]));
        }
    }
    this->shuffle();
}


//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);


    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys \nHover on the node to see it's number" ));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor )
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
