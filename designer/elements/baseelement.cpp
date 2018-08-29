#include "baseelement.h"

#include <QPainter>
#include <protocollayer.h>
#include <util.h>

class BaseElementPrivate
{
public:
    BaseElementPrivate(BaseElement *parent,ProtocolLayer *l)
        :p(parent)
        ,layer(l)
    {}

    ProtocolLayer *layer;
    BaseElement *p;
    QColor color;
    BaseElement::Unit unit;
    int size;
};

BaseElement::BaseElement(ProtocolLayer *parent)
    :QObject(parent)
    ,QGraphicsItem(parent)
    ,d(new BaseElementPrivate(this,parent))
{

}

void BaseElement::setUnit(BaseElement::Unit unit)
{
    d->unit = unit;
}

BaseElement::Unit BaseElement::unit() const
{
    return d->unit;
}

void BaseElement::setSize(int size)
{
    d->size = size;
}

int BaseElement::size() const
{
    return d->size;
}

ProtocolLayer *BaseElement::layer() const
{
    return d->layer;
}

void BaseElement::setLayer(ProtocolLayer *layer)
{
    setParent(layer);
    setParentItem(layer);
    d->layer = layer;
}

void BaseElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setPen(EditorControl::instance()->elementBorderPen());
    painter->setBrush(EditorControl::instance()->elementBrush());
    painter->drawRect(boundingRect());
    painter->restore();
}

QRectF BaseElement::boundingRect() const
{
    if(!d->layer)
        return QRectF(0,0,0,0);

    int eindex = d->layer->indexOfElement(this);
    int lindex = d->layer->index();

    int offset = EditorControl::instance()->elementSpacing() + EditorControl::instance()->elementWidth();
    int left = EditorControl::instance()->elementLeftOffset() + EditorControl::instance()->layerLeftOffset() +\
            eindex * offset;
    int top = lindex * (EditorControl::instance()->layerHeight() + EditorControl::instance()->layerSpacing()) +\
            EditorControl::instance()->layerTopOffset() + EditorControl::instance()->elementTopOffset();

    return QRectF(left,top,EditorControl::instance()->elementWidth(),EditorControl::instance()->elementHeight());
}
