#ifndef PROTOCOLEDITOR_H
#define PROTOCOLEDITOR_H

#include <QWidget>

namespace Ui {
class ProtocolEditor;
}


class ProtocolEditorPrivate;
class ProtocolLayer;
class BaseElement;
class QGraphicsItem;
class ProtocolEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ProtocolEditor(QWidget *parent = nullptr);
    ~ProtocolEditor();

    void appendLayer(ProtocolLayer *layer);
    void removeLayer(ProtocolLayer *layer);

    int layersCount()const;
    QList<ProtocolLayer *> layers();

    int currentLayerIndex(const ProtocolLayer *layer) const;
    void update();

    static ProtocolEditor *openProtocolEditor(const QString &fileName,QString &error);
signals:
    void edited();
    void elementsClicked(BaseElement *element);
    void layerClicked(ProtocolLayer *layer);
public slots:
//    void redo();
//    void undo();
//    void save();
//    void close();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *event);

    void isSaved();

    void addItem(QGraphicsItem *item);
private slots:
    void addNewLayer();
private:
    friend class ProtocolEditorPrivate;
    friend class ProtocolLayer;
    Ui::ProtocolEditor *ui;
    QSharedPointer<ProtocolEditorPrivate> p_d;
};


namespace DesignerEditor
{

QWidget *openFile(const QString &fileName, QString &error);

}


#endif // PROTOCOLEDITOR_H
