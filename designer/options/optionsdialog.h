#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialogPrivate;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

    QList<QPair<const char *,QVariant> > getPropertyList(const QString &name);

    void setPropertyList(const QString &name,const QList<QPair<const char *,QVariant> > &list);

protected:
    void reject();
private slots:
    void on_layer_top_valueChanged(int arg1);

    void on_layer_bottom_valueChanged(int arg1);

    void on_layer_left_valueChanged(int arg1);

    void on_layer_right_valueChanged(int arg1);

    void on_layer_border_width_valueChanged(int arg1);

    void on_layer_border_color_clicked();

    void on_layer_border_style_currentIndexChanged(const QString &arg1);

    void on_layer_background_color_clicked();

    void on_layer_spacing_valueChanged(int arg1);

    void on_layer_background_style_currentIndexChanged(const QString &arg1);

    void on_elements_currentIndexChanged(const QString &arg1);

    void on_elements_top_valueChanged(int arg1);

    void on_elements_bottom_valueChanged(int arg1);

    void on_elements_left_valueChanged(int arg1);

    void on_elements_right_valueChanged(int arg1);

    void on_elements_spacing_valueChanged(int arg1);

    void on_elements_border_width_valueChanged(int arg1);

    void on_elements_border_color_clicked();

    void on_elements_border_style_currentIndexChanged(const QString &arg1);

    void on_elements_background_color_clicked();

private:
    friend class OptionsDialogPrivate;
    QSharedPointer<OptionsDialogPrivate> p_d;
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
