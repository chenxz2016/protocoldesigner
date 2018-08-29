#include "configeditor.h"
#include "ui_configeditor.h"

ConfigEditor::ConfigEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigEditor)
{
    ui->setupUi(this);
}

ConfigEditor::~ConfigEditor()
{
    delete ui;
}
