#include "renamedialog.h"
#include "ui_renamedialog.h"

RenameDialog::RenameDialog(const QString &oldName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameDialog)
{
    ui->setupUi(this);
    ui->input->setText(oldName);
    srcName = oldName;
}

RenameDialog::~RenameDialog()
{
    delete ui;
}

QString RenameDialog::getRename() const
{
    return ui->input->text();
}

QString RenameDialog::getRename(const QString &oldName, QWidget *parent)
{
    RenameDialog rd(oldName,parent);
    int ret = rd.exec();
    if(ret == QDialog::Accepted)
        return rd.getRename();

    return oldName;
}

void RenameDialog::on_input_textEdited(const QString &arg1)
{
    if(srcName == arg1)
    {
        ui->ok->setEnabled(false);
        ui->warning->setText(tr("Please change the new name, the new name is same to old name."));
    }
}
