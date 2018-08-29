#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindowPrivate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openEditor(const QString &filename);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionOptions_triggered();

    void on_project_tree_customContextMenuRequested(const QPoint &pos);

    void on_actionCreate_triggered();

    void on_actionOpen_In_Explore_triggered();

    void on_actionAdd_Existed_triggered();

    void on_actionRemove_File_triggered();

    void on_actionOpen_File_triggered();

    void on_actionRename_triggered();

    void on_actionBuild_current_project_triggered();

    void on_files_switcher_currentTextChanged(const QString &arg1);

    void on_close_clicked();

    void on_actionClose_Current_Project_triggered();

    void on_actionClose_All_Projects_triggered();

    void on_actionOpen_triggered();

    void on_actionOpen_Project_triggered();

    void on_actionCollapse_All_triggered();

    void on_files_switcher_customContextMenuRequested(const QPoint &pos);

private:
    friend class MainWindowPrivate;
    QSharedPointer<MainWindowPrivate> p_d;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
