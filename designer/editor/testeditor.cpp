#include "testeditor.h"
#include "ui_testeditor.h"

TestEditor::TestEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestEditor)
{
    ui->setupUi(this);
}

TestEditor::~TestEditor()
{
    delete ui;
}
