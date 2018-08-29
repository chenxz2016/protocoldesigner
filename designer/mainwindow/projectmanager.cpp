#include "projectmanager.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>

class ProjectManagerPrivate
{
public:
    ProjectManagerPrivate(ProjectManager *parent)
        :p(parent)
    {}


    bool saveProjectFile(const QString &pro,const QMap<QString,QVariant> &properties)
    {
        QFile file(pro);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
        {
            error = file.errorString();
            qDebug() << "output:" << pro << error;
            return false;
        }

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("project");
        writer.writeAttribute("tool", "protocoldesigner");
        writer.writeAttribute("version", "1.0.0");
        writer.writeEndElement();

        writer.writeStartElement("pvf");
        writer.writeAttribute("compiler", "protocolcompiler");
        writer.writeAttribute("version", "1.0.0");
        QList<QVariant> list = properties["pvf_files"].toList();
        foreach(QVariant d, list)
        {
            writer.writeStartElement("file");
            writer.writeAttribute("name",d.toMap()["name"].toString());
            writer.writeEndElement();
        }
        writer.writeEndElement();

        writer.writeStartElement("test");
        writer.writeAttribute("monitor", "protocolsimulator");
        writer.writeAttribute("version", "1.0.0");
        list = properties["test_files"].toList();
        foreach(QVariant d, list)
        {
            writer.writeStartElement("file");
            writer.writeAttribute("name",d.toMap()["name"].toString());
            writer.writeEndElement();
        }
        writer.writeEndElement();

        writer.writeEndDocument();

        return true;
    }

    bool saveConfigFile(const QString &fileName,const QMap<QString,QVariant> &properties)
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
        {
            error = file.errorString();
            return false;
        }

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("config");
        writer.writeAttribute("tool", "protocoldesigner");
        writer.writeAttribute("version", "1.0.0");
        writer.writeEndElement();

        writer.writeStartElement("properties");
        QList<QVariant> list = properties["properties"].toList();
        foreach(QVariant d, list)
        {
            writer.writeStartElement("property");
            QMap<QString,QVariant> m = d.toMap();
            for(QMap<QString,QVariant>::Iterator i = m.begin(); i!= m.end();i++)
                writer.writeAttribute(i.key(),i.value().toString());
            writer.writeEndElement();
        }

        writer.writeEndElement();

        writer.writeEndDocument();

        return true;
    }

    bool saveTestFile(const QString &fileName)
    {
        Q_UNUSED(fileName)
        return true;
    }

    QString error;
    ProjectManager *p;
    QMap<QString,QVariant> map;
};

ProjectManager::ProjectManager()
    :p_d(new ProjectManagerPrivate(this))
{
}

ProjectManager::~ProjectManager()
{
    delete p_d;
}

QString ProjectManager::errorString() const
{
    return p_d->error;
}

bool ProjectManager::creatNewProject(const QVariant &d)
{
    QMap<QString,QVariant> m = d.toMap();
    p_d->map[m["id"].toString()] = d;
    QString filename = m["path"].toString() + "/" + m["name"].toString() + ".ppd";
    if(!p_d->saveProjectFile(filename,m))
        return false;

    filename = m["path"].toString() + "/" + m["name"].toString() + ".ppc";
    return p_d->saveConfigFile(filename,m);
}

bool ProjectManager::addConfig(const QString &id,const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)

    return true;
}

bool ProjectManager::addProtocolFile(const QString &id,const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}

bool ProjectManager::addTestFile(const QString &id,const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}

bool ProjectManager::saveNewProject(const QString &id, const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}

bool ProjectManager::saveConfig(const QString &id, const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}

bool ProjectManager::saveProtocolFile(const QString &id, const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}

bool ProjectManager::saveTestFile(const QString &id, const QVariant &d)
{
    Q_UNUSED(id)
    Q_UNUSED(d)
    return true;
}
