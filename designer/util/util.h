#ifndef UTIL_H
#define UTIL_H

#include <QGradient>
#include <QObject>
#include <QPen>
#include <QSharedPointer>

class EditorControlPrivate;
class ProtocolLayer;
class ElementsFactory;

class EditorControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int layerTopOffset READ layerTopOffset WRITE setLayerTopOffset)
    Q_PROPERTY(int layerLeftOffset READ layerLeftOffset WRITE setLayerLeftOffset)
    Q_PROPERTY(int layerRightOffset READ layerRightOffset WRITE setLayerRightOffset)
    Q_PROPERTY(int layerBottomOffset READ layerBottomOffset WRITE setLayerBottomOffset)
    Q_PROPERTY(int layerSpacing READ layerSpacing WRITE setLayerSpacing)
    Q_PROPERTY(int layerHeight READ layerHeight WRITE setLayerHeight)
    Q_PROPERTY(QBrush layerBrush READ layerBrush WRITE setLayerBrush)
    Q_PROPERTY(QPen layerBorderPen READ layerBorderPen WRITE setLayerBorderPen)

    Q_PROPERTY(int elementTopOffset READ elementTopOffset WRITE setElementTopOffset)
    Q_PROPERTY(int elementLeftOffset READ elementLeftOffset WRITE setElementLeftOffset)
    Q_PROPERTY(int elementRightOffset READ elementRightOffset WRITE setElementRightOffset)
    Q_PROPERTY(int elementBottomOffset READ elementBottomOffset WRITE setElementBottomOffset)
    Q_PROPERTY(int elementSpacing READ elementSpacing WRITE setElementSpacing)
    Q_PROPERTY(int elementWidth READ elementWidth WRITE setElementWidth)
    Q_PROPERTY(int elementHeight READ elementHeight WRITE setElementHeight)
    Q_PROPERTY(QBrush elementBrush READ elementBrush WRITE setElementBrush)
    Q_PROPERTY(QPen elementBorderPen READ elementBorderPen WRITE setElementBorderPen)

    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int lineBorderWidth READ lineBorderWidth WRITE setLineBorderWidth)
    Q_PROPERTY(QBrush lineBrush READ lineBrush WRITE setLineBrush)
    Q_PROPERTY(QPen lineBorderPen READ lineBorderPen WRITE setLineBorderPen)
public:
    static EditorControl *instance();

    virtual ~EditorControl();

    int layerTopOffset()const;
    void setLayerTopOffset(int offset);

    int layerLeftOffset()const;
    void setLayerLeftOffset(int offset);

    int layerRightOffset()const;
    void setLayerRightOffset(int offset);

    int layerBottomOffset();
    void setLayerBottomOffset(int offset);

    int layerSpacing();
    void setLayerSpacing(int spacing);

    int layerHeight()const;
    void setLayerHeight(int height);

    QBrush layerBrush()const;
    void setLayerBrush(const QBrush &brush);

    QPen layerBorderPen()const;
    void setLayerBorderPen(const QPen &pen);

    int elementTopOffset()const;
    void setElementTopOffset(int offset);

    int elementLeftOffset()const;
    void setElementLeftOffset(int offset);

    int elementRightOffset()const;
    void setElementRightOffset(int offset);

    int elementBottomOffset()const;
    void setElementBottomOffset(int offset);

    int elementSpacing();
    void setElementSpacing(int spacing);

    int elementWidth();
    void setElementWidth(int width);

    int elementHeight();
    void setElementHeight(int height);

    QBrush elementBrush()const;
    void setElementBrush(const QBrush &brush);

    QPen elementBorderPen()const;
    void setElementBorderPen(const QPen &pen);

    int lineWidth()const;
    void setLineWidth(int width);

    int lineBorderWidth()const;
    void setLineBorderWidth(int width);

    QBrush lineBrush()const;
    void setLineBrush(const QBrush &brush);

    QPen lineBorderPen()const;
    void setLineBorderPen(const QPen &pen);

    QColor createRandomColor();
protected:
    EditorControl();

private:
    static EditorControl *m_instance;
    QSharedPointer<EditorControlPrivate> p_d;
};

namespace DesignerUtil
{
QList<ElementsFactory *> findAllElementsFactory(QString &error);

void clearAllElementsFactory();
}

#endif // UTIL_H
