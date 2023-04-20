#ifndef SoundListModelItem_H
#define SoundListModelItem_H

#include <QAbstractListModel>

class SoundListModelItem : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SoundListModelItem(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void loadAlarmList();

private:
    QStringList alarmSoundList;
};

#endif // SoundListModelItem_H
