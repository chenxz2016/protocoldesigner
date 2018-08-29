#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateDialog;
}

class QListWidgetItem;
class CreateDialogPrivate;

class CreateDialog : public QDialog
{
    Q_OBJECT
public:
    enum CreateType
    {
        None,
        Project,
        Config,
        PVF,
        Test
    };

    explicit CreateDialog(QWidget *parent = 0);
    ~CreateDialog();

    CreateType getCreateType() const;
    QVariant getData();
protected:

private slots:
    void on_list_itemClicked(QListWidgetItem *item);

    void on_project_name_input_textEdited(const QString &arg1);

    void on_project_path_input_textEdited(const QString &arg1);

    void on_project_path_button_clicked();

    void on_pvf_name_input_textEdited(const QString &arg1);

    void on_test_name_input_textEdited(const QString &arg1);

private:
    Ui::CreateDialog *ui;
    friend class CreateDialogPrivate;
    QSharedPointer<CreateDialogPrivate> p_d;
};

#endif // CREATEDIALOG_H
