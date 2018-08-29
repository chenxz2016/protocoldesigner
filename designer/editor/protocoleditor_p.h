#ifndef PROTOCOLEDITOR_P_H
#define PROTOCOLEDITOR_P_H

class ProtocolEditor;
class QKeyEvent;
class QMouseEvent;
class QPainterEvent;
class ProtocolLayer;

template <typename T>
class QList;

class ProtocolEditorPrivate
{
public:
    ProtocolEditorPrivate(ProtocolEditor *parent)
        :p(parent)
    {}
    ProtocolEditor *p;

    void paintEvent(QPainterEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressedEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QList<ProtocolLayer *> layers;
};

#endif // PROTOCOLEDITOR_P_H
