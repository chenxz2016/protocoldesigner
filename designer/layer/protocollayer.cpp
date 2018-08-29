#include "protocollayer.h"

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <baseelement.h>
#include <elementline.h>
#include <elements.h>
#include <protocoleditor.h>
#include <util.h>


class ProtocolLayerPrivate
{
public:
    ProtocolLayerPrivate(ProtocolLayer *parent, ProtocolEditor *e)
        :p(parent)
        ,editor(e)
    {}

    void init()
    {
        p->setAcceptDrops(true);
    }

    void updateLine()
    {
        if(elements.count() <= 1)
        {
            foreach(ElementLine *line, lines)
            {
                line->setParent(nullptr);
                line->setParentItem(nullptr);
                delete line;
            }

            lines.clear();
            return ;
        }

        QList<ElementLine *> l;
        QList<BaseElement *>::Iterator first = elements.begin();
        QList<BaseElement *>::Iterator second = elements.begin();
        second++;
        for(;second!=elements.end();second++)
        {
            QGraphicsItem *h = static_cast<QGraphicsItem *>(*first);
            QGraphicsItem *t = static_cast<QGraphicsItem *>(*second);
            ElementLine *line = new ElementLine(h,t);
            l.append(line);
            line->setParentItem(p);
            first++;
        }
        editor->update();
    }

    int height;
    QColor borderColor;
    int borderWidth;

    ProtocolEditor *editor;

    QList<BaseElement *> elements;
    QList<ElementLine *> lines;
    ProtocolLayer *p;
};

ProtocolLayer::ProtocolLayer(ProtocolEditor *parent)
    :QGraphicsItem(0)
    ,QObject(0)
    ,p_d(new ProtocolLayerPrivate(this,parent))
{
    p_d->init();
}

ProtocolEditor *ProtocolLayer::parentEditor() const
{
    return p_d->editor;
}

void ProtocolLayer::appendElement(BaseElement *element)
{
    element->setParent(this);
    element->setParentItem(this);
    p_d->elements.append(element);
    element->setLayer(this);
    p_d->updateLine();
}

void ProtocolLayer::insertElement(BaseElement *element, const QPoint &point)
{
    Q_UNUSED(point)
    p_d->elements.insert(1,element);
    p_d->updateLine();
}

void ProtocolLayer::removeElement(BaseElement *element)
{
    p_d->elements.removeAll(element);
    p_d->updateLine();
}

void ProtocolLayer::removeElement(const QPoint &point)
{
    Q_UNUSED(point)
    p_d->updateLine();
}

BaseElement *ProtocolLayer::element(const QPoint &point) const
{
    Q_UNUSED(point)
    return nullptr;
}

QList<BaseElement *> ProtocolLayer::elements() const
{
    return QList<BaseElement *>();
}

int ProtocolLayer::indexOfElement(const BaseElement *element) const
{
    int index = 0;
    foreach(BaseElement *e , p_d->elements)
    {
        if(e == element)
            return index;
        index++;
    }
    return -1;
}

int ProtocolLayer::index() const
{
    if(!p_d->editor)
        return 0;

    return p_d->editor->currentLayerIndex(this);
}

void ProtocolLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    const QMimeData *mime = event->mimeData();
    if(mime->data("designer/type") == "elements-drag")
        event->setAccepted(true);

    QGraphicsItem::dragEnterEvent(event);
}

void ProtocolLayer::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
    QGraphicsItem::dragLeaveEvent(event);
}

void ProtocolLayer::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    ElementsFactory ef;
    const QMimeData *mime = event->mimeData();
    if(mime->data("designer/type") == "elements-drag")
    {
        BaseElement *element = ef.createElement(mime->data("elements"));
        appendElement(element);
    }
    QGraphicsItem::dropEvent(event);
}

void ProtocolLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    painter->setBrush(EditorControl::instance()->layerBrush());
    painter->setPen(EditorControl::instance()->layerBorderPen());
    auto a = mapRectToScene(boundingRect());
    painter->drawPolygon(a);

    painter->restore();
}

QRectF ProtocolLayer::boundingRect() const
{
    if(!p_d->editor)
        return QRectF();

    int index = p_d->editor->currentLayerIndex(this);
    int offset = EditorControl::instance()->layerTopOffset() + EditorControl::instance()->layerBottomOffset() + EditorControl::instance()->layerHeight();
    int x = EditorControl::instance()->layerLeftOffset();
    int y = EditorControl::instance()->layerTopOffset() + index * offset;
    int width = p_d->editor->width() - EditorControl::instance()->layerLeftOffset() - EditorControl::instance()->layerRightOffset();
    return QRectF(x,y,width,EditorControl::instance()->layerHeight());
}



class LayerAdderPrivate
{
public:
    LayerAdderPrivate(LayerAdder *parent,ProtocolEditor *e)
        :p(parent)
        ,editor(e)
        ,hoverEnterColor(Qt::blue)
        ,hoverLeaveColor(Qt::gray)
        ,pressedColor(Qt::red)
    {
        lineColor = hoverLeaveColor;
    }

    LayerAdder *p;
    ProtocolEditor *editor;

    QColor hoverEnterColor;
    QColor hoverLeaveColor;
    QColor pressedColor;
    QColor lineColor;
};

LayerAdder::LayerAdder(ProtocolEditor *parent)
    :QGraphicsItem(0)
    ,QObject(0)
    ,p_d(new LayerAdderPrivate(this,parent))
{
    setAcceptHoverEvents(true);
}

LayerAdder::~LayerAdder()
{

}

void LayerAdder::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    p_d->lineColor = p_d->hoverEnterColor;
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void LayerAdder::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    p_d->lineColor = p_d->hoverLeaveColor;
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void LayerAdder::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    p_d->lineColor = p_d->pressedColor;
    update();
}

void LayerAdder::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(contains(event->pos()))
        p_d->lineColor = p_d->hoverEnterColor;
    else
        p_d->lineColor = p_d->hoverLeaveColor;

    update();
    emit clicked();
}

void LayerAdder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    painter->setBrush(EditorControl::instance()->layerBrush());
    QPen pen(Qt::DashLine);
    pen.setColor(p_d->lineColor);
    painter->setPen(pen);
    auto a = mapRectToScene(boundingRect());
    painter->drawPolygon(a);
    painter->drawText(a,"Click to add new layer.",QTextOption(Qt::AlignCenter));

    painter->restore();
}

QRectF LayerAdder::boundingRect() const
{
    if(!p_d->editor)
        return QRectF();

    int index = p_d->editor->layersCount();
    int offset = EditorControl::instance()->layerTopOffset() + EditorControl::instance()->layerBottomOffset() + EditorControl::instance()->layerHeight();
    int x = EditorControl::instance()->layerLeftOffset();
    int y = EditorControl::instance()->layerTopOffset() + index * offset;
    int width = p_d->editor->width() - EditorControl::instance()->layerLeftOffset() - EditorControl::instance()->layerRightOffset();
    return QRectF(x,y,width,EditorControl::instance()->layerHeight());
}
