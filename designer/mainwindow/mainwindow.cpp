#include "createdialog.h"
#include "elements.h"
#include "mainwindow.h"
#include "projectmanager.h"
#include "renamedialog.h"
#include "ui_mainwindow.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <optionsdialog.h>
#include <protocoleditor.h>
#include <protocollayer.h>
#include <util.h>
#include <QDebug>
#include <ui_createdialog.h>
#include <QProcess>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>

class MainWindowPrivate
{
public:
    MainWindowPrivate(MainWindow *parent)
        :p(parent)
    {}

    virtual ~MainWindowPrivate()
    {
        DesignerUtil::clearAllElementsFactory();
    }

    void init()
    {
        p->ui->elements->viewport()->installEventFilter(p);
        p->ui->elements->viewport()->setAcceptDrops(true);
        p->ui->elements->setAcceptDrops(true);

        /* Default Elements. */
        ElementsFactory ef;
        QTreeWidgetItem *parent = new QTreeWidgetItem();
        parent->setText(0,ef.name());
        QList<QTreeWidgetItem *> items = ef.createElements();
        parent->addChildren(items);
        p->ui->elements->insertTopLevelItem(0,parent);

        /* Plugins */
        QString error;
        list = DesignerUtil::findAllElementsFactory(error);
        foreach(ElementsFactory *factory , list)
        {
            QTreeWidgetItem *parent = new QTreeWidgetItem();
            parent->setText(0,factory->name());
            QList<QTreeWidgetItem *> items = factory->createElements();
            parent->addChildren(items);
            p->ui->elements->insertTopLevelItem(0,parent);
        }

        p->ui->output->append(error);
    }

    void elementsMousePressEvent(QEvent *event)
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        if(!me)
            return ;

        QPoint pos = p->ui->elements->viewport()->mapFromGlobal(QCursor::pos());
        QTreeWidgetItem *item = p->ui->elements->itemAt(pos);
        if(!item || item->childCount())
            return ;

        QVariant data = item->data(0,Qt::UserRole);
        QMimeData *mimeData = new QMimeData;
        mimeData->setData("designer/type","elements-drag");
        mimeData->setData("designer/elements-drag", "elements-data");
        mimeData->setData("elements","base");

        QDrag *drag = new QDrag(p->ui->elements);
        drag->setMimeData(mimeData);
        drag->setPixmap(item->icon(0).pixmap(24,24));

        drag->exec();
    }

    void elementsMouseReleaseEvent(QEvent *event)
    {
        Q_UNUSED(event)
    }

    void elementsMouseMoveEvent(QEvent *event)
    {
        Q_UNUSED(event)
    }

    void elementsDragEnter(QEvent *event)
    {
        QDragEnterEvent *dev = static_cast<QDragEnterEvent *>(event);
        dev->setDropAction(Qt::MoveAction);
        dev->setAccepted(true);
    }

    void elementsDragLeave(QEvent *event)
    {
        QDragLeaveEvent *dlv = static_cast<QDragLeaveEvent *>(event);
        dlv->setAccepted(false);
    }

    void creatNewProject(const QVariant &d)
    {
        QMap<QString,QVariant> m = d.toMap();
        QTreeWidgetItem *root = new QTreeWidgetItem(QStringList(m["name"].toString()));
        root->setData(0,Qt::UserRole+1,m);
        root->setData(0,Qt::UserRole,"root");

        QTreeWidgetItem *pvf = new QTreeWidgetItem(QStringList("pvf"));
        pvf->setData(0,Qt::UserRole,"pvf");
        root->addChild(pvf);

        QTreeWidgetItem *file = new QTreeWidgetItem(QStringList(m["name"].toString() + ".pvf"));
        file->setData(0,Qt::UserRole,"pvf_file");
        file->setData(0,Qt::UserRole+1,file->text(0));
        pvf->addChild(file);

        QTreeWidgetItem *config = new QTreeWidgetItem(QStringList("config"));
        config->setData(0,Qt::UserRole,"config");
        root->addChild(config);

        QTreeWidgetItem *test = new QTreeWidgetItem(QStringList("test"));
        test->setData(0,Qt::UserRole,"test");
        root->addChild(test);

        p->ui->project_tree->addTopLevelItem(root);
        pm.creatNewProject(d);

        p->openEditor(m["path"].toString() + "/" + m["name"].toString() + ".ppd");
    }

    void addConfig(const QString&id,const QVariant &d)
    {
        pm.addConfig(id,d);
    }

    void addProtocolFile(const QString &id,const QVariant &d)
    {
        pm.addProtocolFile(id,d);
    }

    void addTestFile(const QString &id,const QVariant &d)
    {
        pm.addTestFile(id,d);
    }

    QMap<QString,QWidget *> editorMap;
    QList<ElementsFactory *> list;
    MainWindow *p;
    ProjectManager pm;
};

inline static QAction *createSeparator()
{
    QAction *separator = new QAction;
    separator->setSeparator(true);
    return separator;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_d(new MainWindowPrivate(this))
{
    ui->setupUi(this);
    p_d->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openEditor(const QString &filename)
{
    QString error;
    QWidget *editor = DesignerEditor::openFile(filename,error);
    if(!editor)
    {
        QMessageBox::information(this,tr("Open Failed"),error,QMessageBox::Ok);
        return ;
    }

    p_d->editorMap[editor->property("id").toString()] = editor;
    ui->stacked->addWidget(editor);
    ui->stacked->setCurrentWidget(editor);

    QFileInfo fi(filename);
    ui->files_switcher->addItem(fi.baseName(),filename);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->elements->viewport())
    {
        switch(event->type())
        {
        case QEvent::MouseButtonPress:
            p_d->elementsMousePressEvent(event);
            break;
        case QEvent::MouseButtonRelease:
            p_d->elementsMouseReleaseEvent(event);
            break;
        case QEvent::MouseMove:
            p_d->elementsMouseMoveEvent(event);
            break;
        case QEvent::DragEnter:
            p_d->elementsDragEnter(event);
            break;
        case QEvent::DragLeave:
            p_d->elementsDragLeave(event);
            break;
        default:
            break;
        }
    }
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog od;

    QList<QPair<const char *,QVariant> > list;

    od.setPropertyList("editor",list);

    int ret = od.exec();
    if(ret==QDialog::Rejected)
        return ;

    list = od.getPropertyList("editor");
    for(int i = 0;i < ui->stacked->count(); i++)
    {
        QWidget *w= ui->stacked->widget(i);
        QPair<const char *,QVariant> v;
        foreach(v , list)
            w->setProperty(v.first,v.second);
    }
}

void MainWindow::on_project_tree_customContextMenuRequested(const QPoint &pos)
{
    QList<QAction *> list;
    QTreeWidgetItem *item = ui->project_tree->itemAt(pos);
    if(!item)
    {
        if(ui->project_tree->topLevelItemCount())
        {
            list.append(ui->actionBuild_all_project);
            list.append(ui->actionClear_all_project);
            list.append(ui->actionRebuild_all_projects);
            list.append(createSeparator());
        }

        list.append(ui->actionCreate);
        list.append(ui->actionOpen);

        if(ui->project_tree->topLevelItemCount())
        {
            list.append(createSeparator());
            list.append(ui->actionClose_All_Projects);
        }

        list.append(createSeparator());
        list.append(ui->actionCollapse_All);

        QMenu::exec(list,ui->project_tree->mapToGlobal(pos));
        return ;
    }

    QString str = item->data(0,Qt::UserRole).toString();
    if(str == "root")
    {
        list.append(ui->actionBuild_current_file);
        list.append(ui->actionOpen_In_Explore);
        list.append(ui->actionAdd_Existed);
        list.append(ui->actionClose_Current_Project);
        list.append(ui->actionClose_All_Projects);
    }

    if(str == "pvf" || str == "test")
    {
        list.append(ui->actionCreate);
    }

    if(str == "pvf_file" || str == "test_file")
    {
        list.append(ui->actionOpen_File);
        list.append(ui->actionRemove_File);
        list.append(ui->actionRename);
    }

    QMenu::exec(list,ui->project_tree->mapToGlobal(pos));
}

void MainWindow::on_actionCreate_triggered()
{
    CreateDialog cd;
    int ret = cd.exec();
    if(ret != QDialog::Accepted)
        return ;

    CreateDialog::CreateType ct = cd.getCreateType();
    switch(ct)
    {
    case CreateDialog::Project:
        p_d->creatNewProject(cd.getData());
        break;
    case CreateDialog::Config:
        p_d->addConfig("",cd.getData());
        break;
    case CreateDialog::PVF:
        p_d->addProtocolFile("",cd.getData());
        break;
    case CreateDialog::Test:
        p_d->addTestFile("",cd.getData());
        break;
    default:
        break;
    }
}

void MainWindow::on_actionOpen_In_Explore_triggered()
{
    QString path = QDir::currentPath();
    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}

void MainWindow::on_actionAdd_Existed_triggered()
{
    QList<QString> list = QFileDialog::getOpenFileNames(this,"add existed files",QDir::currentPath(),"*.pvf");

    QTreeWidgetItem *item = ui->project_tree->currentItem();
    if(!item)
        return ;

    QString str = item->data(0,Qt::UserRole).toString();
    if(str == "root")
    {
        for(int i = 0; i<item->childCount(); i++)
            if(item->child(i)->data(0,Qt::UserRole).toString() == "pvf")
                item = item->child(i);
    }

    foreach(QString file,list)
    {
        QFileInfo fi(file);
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(fi.fileName()));
        child->setData(0,Qt::UserRole+1,file);
        item->addChild(child);
    }
}

void MainWindow::on_actionRemove_File_triggered()
{
    QTreeWidgetItem *item = ui->project_tree->currentItem();
    if(!item)
        return ;

    int ret = QMessageBox::warning(this,tr("Remove File"),tr("Do you want to remove this file?"),QMessageBox::Yes|QMessageBox::No);
    if(ret != QMessageBox::Yes)
        return ;

    QTreeWidgetItem *parent = item->parent();
    if(parent)
        parent->removeChild(item);
}

void MainWindow::on_actionOpen_File_triggered()
{

}

void MainWindow::on_actionRename_triggered()
{
    QTreeWidgetItem *item = ui->project_tree->currentItem();
    if(!item)
        return ;

    QString name = RenameDialog::getRename(item->text(0)+".rename",this);
    item->setText(0,name);
}

void MainWindow::on_actionBuild_current_project_triggered()
{

}

void MainWindow::on_files_switcher_currentTextChanged(const QString &arg1)
{
    if(arg1 == "No Files")
        ui->close->setEnabled(false);
}

void MainWindow::on_close_clicked()
{
    QWidget *widget = ui->stacked->currentWidget();
    ui->stacked->removeWidget(widget);
    widget->deleteLater();
    QString id = widget->property("id").toString();
    p_d->editorMap.remove(id);
}

void MainWindow::on_actionClose_Current_Project_triggered()
{
    QTreeWidgetItem *item = ui->project_tree->currentItem();
    if(!item)
        return ;

    int row = ui->project_tree->indexOfTopLevelItem(item);
    ui->project_tree->takeTopLevelItem(row);
}

void MainWindow::on_actionClose_All_Projects_triggered()
{
    ui->project_tree->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Existed Project",QDir::currentPath(),"*.ppc");
}

void MainWindow::on_actionOpen_Project_triggered()
{
    QList<QString> list = QFileDialog::getOpenFileNames(this,"Open Existed Project",QDir::currentPath(),"*.ppc");
    foreach(QString fileName, list)
    {
        Q_UNUSED(fileName)
    }
}

void MainWindow::on_actionCollapse_All_triggered()
{
    ui->project_tree->collapseAll();
}

void MainWindow::on_files_switcher_customContextMenuRequested(const QPoint &pos)
{
    QList<QAction*> list = ui->actions->menu()->actions();
    QMenu menu(ui->files_switcher);
    menu.addActions(list);
    menu.exec();
}
