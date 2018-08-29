#ifndef PROTOCOLLAYER_H
#define PROTOCOLLAYER_H

#include <QGraphicsItem>
#include <QObject>
#include <QColor>

class BaseElement;
class ProtocolLayerPrivate;
class QMouseEvent;
class QPainterEvent;
class ProtocolEditor;

class ProtocolLayer : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ProtocolLayer(ProtocolEditor *parent = nullptr);

    ProtocolEditor *parentEditor()const;

    void appendElement(BaseElement *element);
    void insertElement(BaseElement *element, const QPoint &point);
    void removeElement(BaseElement *element);
    void removeElement(const QPoint &point);

    BaseElement *element(const QPoint &point)const;

    QList<BaseElement *> elements()const;

    int indexOfElement(const BaseElement *element) const;
    int index() const;
signals:
    void elementClicked(BaseElement *element);
public slots:

protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
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
    QSharedPointer<ProtocolLayerPrivate> p_d;
};


class LayerAdderPrivate;
class LayerAdder : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LayerAdder(ProtocolEditor *parent = nullptr);
    ~LayerAdder();

signals:
    void clicked();
protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
//    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
//    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
//    void dropEvent(QGraphicsSceneDragDropEvent *event);
//    void focusInEvent(QFocusEvent *event);
//    void focusOutEvent(QFocusEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;

private:
    QSharedPointer<LayerAdderPrivate> p_d;
};


#endif // PROTOCOLLAYER_H
