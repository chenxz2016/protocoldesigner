#include "createdialog.h"
#include "ui_createdialog.h"

#include <QFileDialog>
#include <QListWidget>


class CreateDialogPrivate
{
public:
    CreateDialogPrivate(CreateDialog *parent)
        :p(parent)
        ,type(CreateDialog::Project)
        ,projectEditFlag(false)
        ,configEditFlag(false)
        ,pvdEditFlag(false)
        ,testEditFlag(false)
    {}

    void init()
    {
        QListWidgetItem *item = new QListWidgetItem(QObject::tr("Create new project"));
        p->ui->list->addItem(item);
        map[item] = p->ui->create_project_page;

        item = new QListWidgetItem(QObject::tr("Create new protocol design file"));
        p->ui->list->addItem(item);
        map[item] = p->ui->create_pdv_page;

        item = new QListWidgetItem(QObject::tr("Create new protocol test file"));
        p->ui->list->addItem(item);
        map[item] = p->ui->create_test_page;

        item = new QListWidgetItem(QObject::tr("Create new project configure file"));
        p->ui->list->addItem(item);
        map[item] = p->ui->create_config_page;
    }

    bool projectIsAllEdited()
    {
        return true;
    }

    bool pvfIsAllEdited()
    {
        return true;
    }

    bool testIsAllEdited()
    {
        return true;
    }

    CreateDialog *p;
    CreateDialog::CreateType type;
    QMap<QListWidgetItem *,QWidget *> map;

    bool projectEditFlag;
    bool configEditFlag;
    bool pvdEditFlag;
    bool testEditFlag;
};

CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog),
    p_d(new CreateDialogPrivate(this))
{
    ui->setupUi(this);
    p_d->init();
}

CreateDialog::~CreateDialog()
{
    delete ui;
}

CreateDialog::CreateType CreateDialog::getCreateType() const
{
    return p_d->type;
}

QVariant CreateDialog::getData()
{
    switch(p_d->type)
    {
    case CreateDialog::Project:
    {
        QMap<QString,QVariant> map;
        map["id"] = ui->project_name_input->text();
        map["name"] = ui->project_name_input->text();
        map["path"] = ui->project_path_input->text();
        QList<QVariant> list;
        QMap<QString,QVariant> m;
        m["name"] = ui->project_name_input->text() + ".pvf";
        list.append(m);
        map["pvf_files"] = list;
        return map;
    }
    case CreateDialog::Test:
        return ui->test_name_input->text();
    case CreateDialog::PVF:
        return ui->pvf_name_input->text();
    case CreateDialog::Config:
    default:
        return QVariant();
    }
}

void CreateDialog::on_list_itemClicked(QListWidgetItem *item)
{
    QWidget *widget = p_d->map[item];
    if(widget)
        ui->stackedWidget->setCurrentWidget(widget);

    if(widget == ui->create_config_page)
        p_d->type = Config;

    if(widget == ui->create_pdv_page)
        p_d->type = PVF;

    if(widget == ui->create_test_page)
        p_d->type = Test;

    if(widget == ui->create_project_page)
        p_d->type = Project;
}

void CreateDialog::on_project_name_input_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->ok->setEnabled(p_d->projectIsAllEdited());
}

void CreateDialog::on_project_path_input_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->ok->setEnabled(p_d->projectIsAllEdited());
}

void CreateDialog::on_project_path_button_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if(!path.isEmpty())
        ui->project_path_input->setText(path);

    ui->ok->setEnabled(p_d->projectIsAllEdited());
}

void CreateDialog::on_pvf_name_input_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->ok->setEnabled(p_d->pvfIsAllEdited());
}

void CreateDialog::on_test_name_input_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->ok->setEnabled(p_d->testIsAllEdited());
}
