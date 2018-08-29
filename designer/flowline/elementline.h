#ifndef ELEMENTLINE_H
#define ELEMENTLINE_H

#include <QObject>
#include <QColor>
#include <QGraphicsItem>


class ElementLinePrivate;

class ElementLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(bool arrayEnable READ arrayEnable WRITE setArrayEnable)
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ElementLine(QGraphicsItem *head,QGraphicsItem *tail);

    void setArrayEnable(bool enable);
    bool arrayEnable()const;


    void setHead(QGraphicsItem *head);
    QGraphicsItem *head()const;

    void setTail(QGraphicsItem *tail);
    QGraphicsItem *tail()const;
signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
     QSharedPointer<ElementLinePrivate> p_d;
};

#endif // ELEMENTLINE_H
