#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QWidget>

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigEditor(QWidget *parent = 0);
    ~ConfigEditor();
signals:
    void edited();
private:
    Ui::ConfigEditor *ui;
};

#endif // CONFIGEDITOR_H
