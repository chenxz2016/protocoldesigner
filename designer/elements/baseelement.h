#ifndef BASEELEMENT_H
#define BASEELEMENT_H

#include <QObject>
#include <QColor>
#include <QGraphicsItem>

class BaseElementPrivate;
class ProtocolLayer;

class BaseElement : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum Unit
    {
        Bit,
        KBit,
        MBit,
        GBit,
        Byte,
        KByte,
        MByte,
        GByte,
    };

    explicit BaseElement(ProtocolLayer *parent = nullptr);

    void setUnit(Unit uint);
    Unit unit()const;

    void setSize(int size);
    int size()const;

    ProtocolLayer *layer()const;
    void setLayer(ProtocolLayer *layer);
signals:

public slots:

protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
//    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
//    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
//    void dropEvent(QGraphicsSceneDragDropEvent *event);
//    void focusInEvent(QFocusEvent *event);
//    void focusOutEvent(QFocusEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;
private:
    QSharedPointer<BaseElementPrivate> d;
};

#endif // BASEELEMENT_H
