#ifndef MYMODEL_H
#define MYMODEL_H


#include <QAbstractTableModel>

struct Auth{
    QString lastname;
    QString firstname;
    QString middlename;
    QString birthdate;
};

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns
    {
        cFN,
        cLN,
        cMN,
        cBD,
        cCount
    };
    MyModel(QObject * parent = nullptr);
    int columnCount (const QModelIndex &parent) const;
    int rowCount (const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void AddAuthor(const QString &lastname,const QString &firstname,const QString &middlename,const QString &birthdate);
    void DelAuth(int row);
    void UpdAuth(int row,const QString &lastname,const QString &firstname,const QString &middlename,const QString &birthdate);
    QString SerializeXML();
    void DeserializeXML(const QString &xml);
private:
    QMap<quint32,Auth> _Authors;
};

#endif // MYMODEL_H
