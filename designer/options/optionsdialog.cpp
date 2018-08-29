#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QColorDialog>
#include <protocoleditor.h>
#include <util.h>

const QMap<QString,Qt::PenStyle> pen_style_map
{
    {"SolidLine",Qt::SolidLine},
    {"DashLine",Qt::DashLine},
    {"DotLine",Qt::DotLine},
    {"DashDotLine",Qt::DashDotLine},
    {"DashDotDotLine",Qt::DashDotDotLine}
};

const QMap<QString,Qt::BrushStyle> brush_style_map =
{
    {"SolidPattern",Qt::SolidPattern},
    {"Dense1Pattern",Qt::Dense1Pattern},
    {"Dense2Pattern",Qt::Dense2Pattern},
    {"Dense3Pattern",Qt::Dense3Pattern},
    {"Dense4Pattern",Qt::Dense4Pattern},
    {"Dense5Pattern",Qt::Dense5Pattern},
    {"Dense6Pattern",Qt::Dense6Pattern},
    {"Dense7Pattern",Qt::Dense7Pattern},
    {"HorPattern",Qt::HorPattern},
    {"VerPattern",Qt::VerPattern},
    {"CrossPattern",Qt::CrossPattern},
    {"BDiagPattern",Qt::BDiagPattern},
    {"FDiagPattern",Qt::FDiagPattern},
    {"DiagCrossPattern",Qt::DiagCrossPattern},
    {"LinearGradientPattern",Qt::LinearGradientPattern},
    {"ConicalGradientPattern",Qt::ConicalGradientPattern},
    {"RadialGradientPattern",Qt::RadialGradientPattern},
    {"TexturePattern",Qt::TexturePattern}
};

inline static Qt::PenStyle string_to_style(const QString &str)
{
    if(str=="SolidLine")
        return Qt::SolidLine;

    if(str=="DashLine")
        return Qt::DashLine;

    if(str=="DotLine")
        return Qt::DotLine;

    if(str=="DashDotLine")
        return Qt::DashDotLine;

    if(str=="DashDotDotLine")
        return Qt::DashDotDotLine;
}

inline static QString style_to_string(Qt::PenCapStyle style)
{
    switch(style)
    {
    case Qt::SolidLine:
        return "SolidLine";
    case Qt::DashLine:
        return "DashLine";
    case Qt::DotLine:
        return "DotLine";
    case Qt::DashDotLine:
        return "DashDotLine";
    case Qt::DashDotDotLine:
        return "DashDotDotLine";
    default:
        break;
    }
    return "";
}

class OptionsDialogPrivate
{
public:
    OptionsDialogPrivate()
        :initBorderTopOffset(EditorControl::instance()->layerTopOffset())
        ,initBorderBottomOffset(EditorControl::instance()->layerBottomOffset())
        ,initBorderLeftOffset(EditorControl::instance()->layerLeftOffset())
        ,initBorderRightOffset(EditorControl::instance()->layerRightOffset())
        ,initLayerSpacing(EditorControl::instance()->layerSpacing())
        ,initLayerHeight(EditorControl::instance()->layerHeight())
        ,initLayerBorderPen(EditorControl::instance()->layerBorderPen())
        ,initLayerBrush(EditorControl::instance()->layerBrush())
        ,editor(nullptr)
    {
    }

    void init(OptionsDialog *dialog)
    {
        dialog->ui->layer_top->setValue(initBorderTopOffset);
        dialog->ui->layer_bottom->setValue(initBorderBottomOffset);
        dialog->ui->layer_left->setValue(initBorderLeftOffset);
        dialog->ui->layer_right->setValue(initBorderRightOffset);
        dialog->ui->layer_spacing->setValue(initBorderRightOffset);

        QPalette p = dialog->ui->layer_border_color->palette();
        p.setColor(QPalette::Background,initLayerBorderPen.color());
        dialog->ui->layer_border_color->setPalette(p);

        dialog->ui->layer_border_width->setValue(initLayerBorderPen.width());
        dialog->ui->layer_border_style->setCurrentText(style_to_string(initLayerBorderPen.capStyle()));
    }

    void updateEditor()
    {
        if(editor)
            editor->update();
    }

    int initBorderTopOffset;
    int initBorderBottomOffset;
    int initBorderLeftOffset;
    int initBorderRightOffset;
    int initLayerSpacing;
    int initLayerHeight;
    QPen initLayerBorderPen;
    QBrush initLayerBrush;


    ProtocolEditor *editor;
};

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    p_d(new OptionsDialogPrivate)
{
    ui->setupUi(this);
    QHBoxLayout *l = new QHBoxLayout;
    l->setSpacing(0);
    l->setMargin(0);
    p_d->editor = new ProtocolEditor;
    l->addWidget(p_d->editor);
    ui->canvas->setLayout(l);

    p_d->init(this);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

QList<QPair<const char *,QVariant> > OptionsDialog::getPropertyList(const QString &name)
{
    Q_UNUSED(name)
    QList<QPair<const char *,QVariant> > list;
    return list;
}

void OptionsDialog::setPropertyList(const QString &name, const QList<QPair<const char *, QVariant> > &list)
{
    Q_UNUSED(name)
    Q_UNUSED(list)
}

void OptionsDialog::reject()
{
    EditorControl::instance()->setLayerTopOffset(p_d->initBorderTopOffset);
    EditorControl::instance()->setLayerBottomOffset(p_d->initBorderBottomOffset);
    EditorControl::instance()->setLayerLeftOffset(p_d->initBorderLeftOffset);
    EditorControl::instance()->setLayerRightOffset(p_d->initBorderRightOffset);
    EditorControl::instance()->setLayerSpacing(p_d->initLayerSpacing);
    EditorControl::instance()->setLayerHeight(p_d->initLayerHeight);
    EditorControl::instance()->setLayerBorderPen(p_d->initLayerBorderPen);
    EditorControl::instance()->setLayerBrush(p_d->initLayerBrush);
    QDialog::reject();
}

void OptionsDialog::on_layer_top_valueChanged(int arg1)
{
    EditorControl::instance()->setLayerTopOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_bottom_valueChanged(int arg1)
{
    EditorControl::instance()->setLayerBottomOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_left_valueChanged(int arg1)
{
    EditorControl::instance()->setLayerLeftOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_right_valueChanged(int arg1)
{
    EditorControl::instance()->setLayerRightOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_border_width_valueChanged(int arg1)
{
    QPen p = EditorControl::instance()->layerBorderPen();
    p.setWidth(arg1);
    EditorControl::instance()->setLayerBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_border_color_clicked()
{
    QPen p = EditorControl::instance()->layerBorderPen();
    QColor c = QColorDialog::getColor(p.color());
    p.setColor(c);
    EditorControl::instance()->setLayerBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_border_style_currentIndexChanged(const QString &arg1)
{
    Qt::PenStyle style = pen_style_map[arg1];
    QPen p = EditorControl::instance()->layerBorderPen();
    p.setStyle(style);
    EditorControl::instance()->setLayerBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_background_color_clicked()
{
    QBrush b = EditorControl::instance()->layerBrush();
    QColor c = QColorDialog::getColor(b.color());
    b.setColor(c);
    EditorControl::instance()->setLayerBrush(b);
    p_d->updateEditor();
}

void OptionsDialog::on_layer_spacing_valueChanged(int arg1)
{
    EditorControl::instance()->setLayerSpacing(arg1);
    p_d->updateEditor();
}


void OptionsDialog::on_layer_background_style_currentIndexChanged(const QString &arg1)
{
    Qt::BrushStyle style = brush_style_map[arg1];
    QBrush b = EditorControl::instance()->layerBrush();
    b.setStyle(style);
    EditorControl::instance()->setLayerBrush(b);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
}

void OptionsDialog::on_elements_top_valueChanged(int arg1)
{
    EditorControl::instance()->setElementTopOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_bottom_valueChanged(int arg1)
{
    EditorControl::instance()->setElementBottomOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_left_valueChanged(int arg1)
{
    EditorControl::instance()->setElementLeftOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_right_valueChanged(int arg1)
{
    EditorControl::instance()->setElementRightOffset(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_spacing_valueChanged(int arg1)
{
    EditorControl::instance()->setElementSpacing(arg1);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_border_width_valueChanged(int arg1)
{
    QPen p = EditorControl::instance()->elementBorderPen();
    p.setWidth(arg1);
    EditorControl::instance()->setElementBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_border_color_clicked()
{
    QPen p = EditorControl::instance()->elementBorderPen();
    QColor c = QColorDialog::getColor(p.color());
    p.setColor(c);
    EditorControl::instance()->setElementBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_border_style_currentIndexChanged(const QString &arg1)
{
    Qt::PenStyle style = pen_style_map[arg1];
    QPen p = EditorControl::instance()->elementBorderPen();
    p.setStyle(style);
    EditorControl::instance()->setElementBorderPen(p);
    p_d->updateEditor();
}

void OptionsDialog::on_elements_background_color_clicked()
{
    QBrush b = EditorControl::instance()->elementBrush();
    QColor c = QColorDialog::getColor(b.color());
    b.setColor(c);
    EditorControl::instance()->setElementBrush(b);
    p_d->updateEditor();
}
