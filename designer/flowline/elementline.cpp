#include "elementline.h"

#include <QPainter>
#include <util.h>



class ElementLinePrivate
{
public:
    ElementLinePrivate(QGraphicsItem *h,QGraphicsItem *t,ElementLine *parent)
        :p(parent)
        ,head(h)
        ,tail(t)
    {}

    bool arrayEnable;
    ElementLine *p;
    QGraphicsItem *head;
    QGraphicsItem *tail;
};

ElementLine::ElementLine(QGraphicsItem *head,QGraphicsItem *tail)
    : QObject(nullptr)
    ,QGraphicsItem(nullptr)
    ,p_d(new ElementLinePrivate(head,tail,this))
{

}

void ElementLine::setArrayEnable(bool enable)
{
    p_d->arrayEnable = enable;
}

bool ElementLine::arrayEnable() const
{
    return p_d->arrayEnable;
}

void ElementLine::setHead(QGraphicsItem *head)
{
    p_d->head = head;
}

QGraphicsItem *ElementLine::head() const
{
    return p_d->head;
}

void ElementLine::setTail(QGraphicsItem *tail)
{
    p_d->tail = tail;
}

QGraphicsItem *ElementLine::tail() const
{
    return p_d->tail;
}


static QPolygonF calculate_polyline(QGraphicsItem *head, QGraphicsItem *tail)
{
    QPolygonF polygon;
    QPointF hc = head->boundingRect().center();
    QPointF tc = tail->boundingRect().center();
    if(hc.x() > tc.x())
    {
        polygon.append(QPointF(head->boundingRect().right(),hc.y()));
        polygon.append(QPointF((hc.x() + tc.x())/2, (hc.y() + tc.y())/2));
        polygon.append(QPointF(tail->boundingRect().left(),tc.y()));
    }
    else if(hc.x() < tc.x())
    {
        polygon.append(QPointF(head->boundingRect().right(),hc.y()));
        polygon.append(QPointF((hc.x() + tc.x())/2, (hc.y() + tc.y())/2));
        polygon.append(QPointF(tail->boundingRect().left(),tc.y()));
    }
    else
    {
        polygon.append(QPointF(hc.x(),head->boundingRect().bottom()));
        polygon.append(QPointF(tc.x(),head->boundingRect().top()));
    }

    return polygon;
}

void ElementLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!p_d->head || !p_d->tail)
        return ;

    painter->save();
    painter->setPen(EditorControl::instance()->lineBorderPen());
    painter->setBrush(EditorControl::instance()->lineBrush());
    painter->drawPolyline(calculate_polyline(p_d->head,p_d->tail));
    painter->restore();
}

QRectF ElementLine::boundingRect() const
{
    if(!p_d->head || !p_d->tail)
        return QRectF(0,0,0,0);

    QPointF start = p_d->head->boundingRect().topLeft();
    QPointF end = p_d->tail->boundingRect().bottomRight();
    return QRectF(start,end);
}


