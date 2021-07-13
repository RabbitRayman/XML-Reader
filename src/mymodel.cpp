#include "mymodel.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>




MyModel::MyModel(QObject * parent) : QAbstractTableModel(parent)
{

}

int MyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return cCount;
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _Authors.size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return _Authors[_Authors.keys()[index.row()]].lastname;
        case 1:
            return _Authors[_Authors.keys()[index.row()]].firstname;
        case 2:
            return _Authors[_Authors.keys()[index.row()]].middlename;
        case 3:
            return _Authors[_Authors.keys()[index.row()]].birthdate;

        }
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation==Qt::Horizontal)
    {
        if(role==Qt::DisplayRole)
        {
            switch(section)
            {
            case cFN:
                return "Фамилия";
            case cLN:
                return "Имя";
            case cMN:
                return "Отчество/Среднее имя";
            case cBD:
                return "Дата рождения";
            }
        }
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

void MyModel::AddAuthor(const QString &lastname, const QString &firstname, const QString &middlename, const QString &birthdate)
{
    beginInsertRows(QModelIndex(), _Authors.size(),_Authors.size());
    Auth _a;
    _a.lastname=lastname;
    _a.firstname=firstname;
    _a.middlename=middlename;
    _a.birthdate=birthdate;
    uint id=0;
    if (_Authors.size()>0)
    {
        id=_Authors.keys()[_Authors.size()-1]+1;
    }
    if (_Authors.keys().contains(id))
    {
        do
        {
            id++;
        }
        while (_Authors.keys().contains(id));
    }
    _Authors.insert(id,_a);
    endInsertRows();
}

void MyModel::DelAuth(int row)
{
    if (_Authors.size()>0)
    {
        beginRemoveRows(QModelIndex(), row, row);
        _Authors.remove(_Authors.keys()[row]);
        endRemoveRows();
    }
}

void MyModel::UpdAuth(int row, const QString &lastname, const QString &firstname, const QString &middlename, const QString &birthdate)
{
    if (_Authors.size()>0)
    {
        Auth _a;
        _a.lastname=lastname;
        _a.firstname=firstname;
        _a.middlename=middlename;
        _a.birthdate=birthdate;
        _Authors[_Authors.keys()[row]]=_a;
        emit dataChanged(index(row,cLN),index(row,cBD));
    }
}

QString MyModel::SerializeXML()
{
    QDomDocument document;
    QDomElement root = document.createElement("authors");
    document.appendChild(root);
    int i=0;
    for (Auth a: _Authors)
    {
        QDomElement authnode = document.createElement("author");
        authnode.setAttribute("id",_Authors.keys()[i]);

        QDomElement lnnode = document.createElement("lastname");
        lnnode.appendChild(document.createTextNode(a.lastname));
        authnode.appendChild(lnnode);

        QDomElement fnnode = document.createElement("firstname");
        fnnode.appendChild(document.createTextNode(a.firstname));
        authnode.appendChild(fnnode);

        QDomElement mnnode = document.createElement("middlename");
        mnnode.appendChild(document.createTextNode(a.middlename));
        authnode.appendChild(mnnode);

        QDomElement bdnode = document.createElement("birthdate");
        bdnode.appendChild(document.createTextNode(a.birthdate));
        authnode.appendChild(bdnode);

        root.appendChild(authnode);

        i++;
    }

    return document.toString();
}

void MyModel::DeserializeXML(const QString &xml)
{
    beginResetModel();
    _Authors.clear();
    QDomDocument document;

    if(!document.setContent(xml))
        return;

    QDomElement root = document.firstChildElement("authors");
    QDomElement authnode = root.firstChildElement("author");
    while (!authnode.isNull())
    {
        Auth a;
        quint32 i=authnode.attributeNode("id").value().toUInt();
        QDomElement lnnode=authnode.firstChildElement("lastname");
        a.lastname=lnnode.firstChild().nodeValue();
        QDomElement fnnode=authnode.firstChildElement("firstname");
        a.firstname=fnnode.firstChild().nodeValue();
        QDomElement mnnode=authnode.firstChildElement("middlename");
        a.middlename=mnnode.firstChild().nodeValue();
        QDomElement bdnode=authnode.firstChildElement("birthdate");
        a.birthdate=bdnode.firstChild().nodeValue();

        _Authors.insert(i,a);

        authnode = authnode.nextSiblingElement("author");
    }
    endResetModel();
}
