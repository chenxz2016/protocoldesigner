#include "util.h"

#include <QColor>
#include <QDir>
#include <QLibrary>
#include <QSet>
#include <protocollayer.h>


EditorControl *EditorControl::m_instance = 0;

class EditorControlPrivate
{
public:
    EditorControlPrivate()
        :layerTopOffset(10)
        ,layerLeftOffset(5)
        ,layerRightOffset(5)
        ,layerBottomOffset(5)
        ,layerSpacing(5)
        ,layerHeight(48)
        ,layerBrush(Qt::white)
        ,layerBorderPen(Qt::gray)
        ,elementTopOffset(5)
        ,elementLeftOffset(5)
        ,elementRightOffset(5)
        ,elementBottomOffset(5)
        ,elementSpacing(24)
        ,elementWidth(48)
        ,elementHeight(36)
        ,elementBrush(Qt::black)
        ,elementBorderPen(Qt::gray)
        ,index(125)
        ,start(Qt::black)
        ,lineWidth(8)
        ,lineBorderWidth(1)
        ,lineBrush(Qt::black)
        ,linePen(Qt::gray)
    {
        layerBorderPen.setStyle(Qt::DashLine);
//        set << Qt::black << Qt::white
//             << Qt::darkGray << Qt::gray
//             << Qt::lightGray << Qt::red
//             << Qt::green << Qt::blue
//             << Qt::cyan << Qt::magenta
//             << Qt::yellow << Qt::darkRed
//             << Qt::darkGreen << Qt::darkBlue
//             << Qt::darkCyan << Qt::darkMagenta
//             << Qt::darkYellow;
    }

    int layerTopOffset;
    int layerLeftOffset;
    int layerRightOffset;
    int layerBottomOffset;
    int layerSpacing;
    int layerHeight;
    QBrush layerBrush;
    QPen layerBorderPen;

    int elementTopOffset;
    int elementLeftOffset;
    int elementRightOffset;
    int elementBottomOffset;
    int elementSpacing;
    int elementWidth;
    int elementHeight;
    QBrush elementBrush;
    QPen elementBorderPen;

    int lineWidth;
    int lineBorderWidth;
    QBrush lineBrush;
    QPen linePen;

    int index;
    QColor start;
};

EditorControl *EditorControl::instance()
{
    if(!m_instance)
        m_instance = new EditorControl;
    return m_instance;
}

EditorControl::~EditorControl()
{
}

int EditorControl::layerTopOffset() const
{
    return p_d->layerTopOffset;
}

void EditorControl::setLayerTopOffset(int offset)
{
    p_d->layerTopOffset = offset;
}

int EditorControl::layerLeftOffset() const
{
    return p_d->layerLeftOffset;
}

void EditorControl::setLayerLeftOffset(int offset)
{
    p_d->layerLeftOffset = offset;
}

int EditorControl::layerRightOffset() const
{
    return p_d->layerRightOffset;
}

void EditorControl::setLayerRightOffset(int offset)
{
    p_d->layerRightOffset = offset;
}

int EditorControl::layerBottomOffset()
{
    return p_d->layerBottomOffset;
}

void EditorControl::setLayerBottomOffset(int offset)
{
    p_d->layerBottomOffset = offset;
}

int EditorControl::layerSpacing()
{
    return p_d->layerSpacing;
}

void EditorControl::setLayerSpacing(int spacing)
{
    p_d->layerSpacing = spacing;
}

int EditorControl::layerHeight() const
{
    return p_d->layerHeight;
}

void EditorControl::setLayerHeight(int height)
{
    p_d->layerHeight = height;
}

QBrush EditorControl::layerBrush() const
{
    return p_d->layerBrush;
}

void EditorControl::setLayerBrush(const QBrush &brush)
{
    p_d->layerBrush = brush;
}

QPen EditorControl::layerBorderPen() const
{
    return p_d->layerBorderPen;
}

void EditorControl::setLayerBorderPen(const QPen &pen)
{
    p_d->layerBorderPen = pen;
}

int EditorControl::elementTopOffset() const
{
    return p_d->elementTopOffset;
}

void EditorControl::setElementTopOffset(int offset)
{
    p_d->elementTopOffset = offset;
}

int EditorControl::elementLeftOffset() const
{
    return p_d->elementLeftOffset;
}

void EditorControl::setElementLeftOffset(int offset)
{
    p_d->elementLeftOffset = offset;
}

int EditorControl::elementRightOffset() const
{
    return p_d->elementRightOffset;
}

void EditorControl::setElementRightOffset(int offset)
{
    p_d->elementRightOffset = offset;
}

int EditorControl::elementBottomOffset() const
{
    return p_d->elementBottomOffset;
}

void EditorControl::setElementBottomOffset(int offset)
{
    p_d->elementBottomOffset = offset;
}

int EditorControl::elementSpacing()
{
    return p_d->elementSpacing;
}

void EditorControl::setElementSpacing(int spacing)
{
    p_d->elementSpacing = spacing;
}

int EditorControl::elementWidth()
{
    return p_d->elementWidth;
}

void EditorControl::setElementWidth(int width)
{
    p_d->elementWidth = width;
}

int EditorControl::elementHeight()
{
    return p_d->elementHeight;
}

void EditorControl::setElementHeight(int height)
{
    p_d->elementHeight = height;
}

QBrush EditorControl::elementBrush() const
{
    return p_d->elementBrush;
}

void EditorControl::setElementBrush(const QBrush &brush)
{
    p_d->elementBrush = brush;
}

QPen EditorControl::elementBorderPen() const
{
    return p_d->elementBorderPen;
}

void EditorControl::setElementBorderPen(const QPen &pen)
{
    p_d->elementBorderPen = pen;
}

int EditorControl::lineWidth() const
{
    return p_d->lineWidth;
}

void EditorControl::setLineWidth(int width)
{
    p_d->lineWidth = width;
}

int EditorControl::lineBorderWidth() const
{
    return p_d->lineBorderWidth;
}

void EditorControl::setLineBorderWidth(int width)
{
    p_d->lineBorderWidth = width;
}

QBrush EditorControl::lineBrush() const
{
    return p_d->lineBrush;
}

void EditorControl::setLineBrush(const QBrush &brush)
{
    p_d->lineBrush = brush;
}

QPen EditorControl::lineBorderPen() const
{
    return p_d->linePen;
}

void EditorControl::setLineBorderPen(const QPen &pen)
{
    p_d->linePen = pen;
}

QColor EditorControl::createRandomColor()
{
    int r = p_d->start.red() + p_d->index;
    int g = p_d->start.green() + p_d->index;
    int b = p_d->start.blue() + p_d->index;
    bool flag = false;
    if(r > 255)
    {
        flag = true;
        r = 0;
    }

    if(g > 255)
    {
        flag = true;
        g = 0;
    }

    if(b > 255)
    {
        flag = true;
        b = 0;
    }

    if(flag)
        p_d->index = sqrt(p_d->index);

    return QColor(r,g,b);
}

EditorControl::EditorControl()
    :QObject(nullptr)
    ,p_d(new EditorControlPrivate)
{
}


namespace DesignerUtil
{
QList<QLibrary*>  libs;

typedef ElementsFactory * (*CreateElementsFactory)();
}

QList<ElementsFactory *> DesignerUtil::findAllElementsFactory(QString &error)
{
    QDir dir("plugins");
    QList<ElementsFactory *> list;
    if(dir.exists())
        return list;
    QStringList filters;
    filters.append("..");
    filters.append(".");
    QStringList strList = dir.entryList(filters);
    foreach(QString name, strList)
    {
        QLibrary *lib = new QLibrary(dir.absoluteFilePath(name));
        if(!lib->load())
            error += lib->errorString() + "\n";
        CreateElementsFactory createElementFactory = (CreateElementsFactory)lib->resolve("CreateElementsFactory");
        if(!createElementFactory)
        {
            error += name + "doesn't contains 'CreateElementsFactory' Function.\n";
            delete lib;
            continue;
        }
        ElementsFactory *factory = createElementFactory();
        list.append(factory);
        libs.append(lib);
    }
    return list;
}

void DesignerUtil::clearAllElementsFactory()
{
    foreach(QLibrary* lib , libs)
        delete lib;

    libs.clear();
}
