#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QVariant>

class QTreeWidgetItem;
class BaseElement;
class ElementsFactory
{
public:
    ElementsFactory();
    virtual ~ElementsFactory();

    virtual QList<QTreeWidgetItem *> createElements();
    virtual BaseElement *createElement(const QVariant &info);

    QString name() const;
    QString version() const;
};

#endif // ELEMENTS_H
