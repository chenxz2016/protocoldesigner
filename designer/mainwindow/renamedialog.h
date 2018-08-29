#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>

namespace Ui {
class RenameDialog;
}

class RenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameDialog(const QString &oldName,QWidget *parent = 0);
    ~RenameDialog();

    QString getRename() const;

    static QString getRename(const QString &oldName, QWidget *parent = nullptr);
private slots:
    void on_input_textEdited(const QString &arg1);

private:
    Ui::RenameDialog *ui;
    QString srcName;
};

#endif // RENAMEDIALOG_H
