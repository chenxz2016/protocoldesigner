#include "elements.h"

#include <QListWidget>
#include <QTreeWidget>
#include <baseelement.h>

ElementsFactory::ElementsFactory()
{

}

ElementsFactory::~ElementsFactory()
{

}

QList<QTreeWidgetItem *> ElementsFactory::createElements()
{
    QList<QTreeWidgetItem *>  list;
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setIcon(0,QIcon(":/res/icon.jpg"));
    item->setFlags(Qt::ItemIsEnabled);
    item->setText(0,QString("DefaultElements"));
    list.append(item);
    return list;
}

BaseElement *ElementsFactory::createElement(const QVariant &info)
{
    Q_UNUSED(info)
    return new BaseElement();
}

QString ElementsFactory::name() const
{
    return "DefaultElements";
}

QString ElementsFactory::version() const
{
    return "1.0.0";
}
