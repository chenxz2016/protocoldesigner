#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QVariant>

class ProjectManagerPrivate;
class ProjectManager
{
public:
    ProjectManager();
    virtual ~ProjectManager();

    bool creatNewProject(const QVariant &d);

    bool addConfig(const QString &id,const QVariant &d);

    bool addProtocolFile(const QString &id,const QVariant &d);

    bool addTestFile(const QString &id,const QVariant &d);

    bool saveNewProject(const QString &id,const QVariant &d);

    bool saveConfig(const QString &id,const QVariant &d);

    bool saveProtocolFile(const QString &id,const QVariant &d);

    bool saveTestFile(const QString &id,const QVariant &d);

    QString errorString() const;
private:
    friend class ProjectManagerPrivate;
    ProjectManagerPrivate *p_d;
};

#endif // PROJECTMANAGER_H
