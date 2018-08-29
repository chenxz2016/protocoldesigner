#ifndef FLOWPOINTER_H
#define FLOWPOINTER_H

#include <QObject>

class FlowPointer : public QObject
{
    Q_OBJECT
public:
    explicit FlowPointer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FLOWPOINTER_H