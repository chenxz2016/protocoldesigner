#include "protocoleditor.h"
#include "ui_protocoleditor.h"
#include <QFile>
#include <QGraphicsView>
#include <baseelement.h>
#include <protocollayer.h>
#include <util.h>

class ProtocolEditorPrivate
{
public:
    ProtocolEditorPrivate(ProtocolEditor *parent)
        :p(parent)
    {}

    void init()
    {
        p->ui->view->setScene(new QGraphicsScene);

        adder = new LayerAdder(p);
        p->ui->view->scene()->addItem(adder);
        QObject::connect(adder,SIGNAL(clicked()),p,SLOT(addNewLayer()));

        ProtocolLayer *layer = new ProtocolLayer(p);
        p->appendLayer(layer);

        BaseElement *element = new BaseElement();
        layer->appendElement(element);

        element = new BaseElement();
        layer->appendElement(element);
    }

    void viewDropEvent(QEvent *event)
    {
        Q_UNUSED(event)
    }

    ProtocolEditor *p;
    QList<ProtocolLayer *> list;
    QList<ProtocolLayer *> removed;
    LayerAdder *adder;
};

ProtocolEditor::ProtocolEditor(QWidget *parent)
    :QWidget(parent)
    ,p_d(new ProtocolEditorPrivate(this))
    ,ui(new Ui::ProtocolEditor)
{
    ui->setupUi(this);
    p_d->init();
}

ProtocolEditor::~ProtocolEditor()
{

}

void ProtocolEditor::appendLayer(ProtocolLayer *layer)
{
    p_d->list.append(layer);
    ui->view->scene()->addItem(layer);
}

void ProtocolEditor::removeLayer(ProtocolLayer *layer)
{
    p_d->list.removeAll(layer);
    p_d->removed.append(layer);
    ui->view->scene()->addItem(layer);
}

int ProtocolEditor::layersCount() const
{
    return p_d->list.count();
}

QList<ProtocolLayer *> ProtocolEditor::layers()
{
    return p_d->list;
}

bool ProtocolEditor::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->view)
    {
        switch(event->type())
        {
        case QEvent::Drop:
            p_d->viewDropEvent(event);
            break;
        case QEvent::DragEnter:
            break;
        case QEvent::DragLeave:
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void ProtocolEditor::resizeEvent(QResizeEvent *event)
{
    ui->view->scene()->setSceneRect(0,0,ui->view->width(),ui->view->height());
    QWidget::resizeEvent(event);
}

void ProtocolEditor::addItem(QGraphicsItem *item)
{
    ui->view->scene()->addItem(item);
}

void ProtocolEditor::addNewLayer()
{
    appendLayer(new ProtocolLayer(this));
}

int ProtocolEditor::currentLayerIndex(const ProtocolLayer *layer) const
{
    int index = 0;
    foreach(ProtocolLayer *l , p_d->list)
    {
        if(l == layer)
            return index;
        index++;
    }
    return -1;
}

void ProtocolEditor::update()
{
    foreach(ProtocolLayer *l , p_d->list)
        l->update();
    QWidget::update();
}

ProtocolEditor *ProtocolEditor::openProtocolEditor(const QString &fileName, QString &error)
{
    QFile file(fileName);
    if(!file.exists())
    {
        error = file.errorString();
        return nullptr;
    }

    ProtocolEditor *editor = new ProtocolEditor;

    return editor;
}

namespace DesignerEditor
{

QWidget *openFile(const QString &fileName, QString &error)
{
    ProtocolEditor *editor = ProtocolEditor::openProtocolEditor(fileName,error);
    return editor;
}

}
