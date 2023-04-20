#include "SoundListModelItem.h"
#include <QDebug>
#include <QDirIterator>

SoundListModelItem::SoundListModelItem(QObject *parent)
    : QAbstractListModel{parent}
{
    loadAlarmList();
}

int SoundListModelItem::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return alarmSoundList.count();
}

QVariant SoundListModelItem::data(const QModelIndex &index, int role) const
{
    int nRow = index.row();

    if ( nRow < 0 || nRow >= alarmSoundList.count() ) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:
        return alarmSoundList.value(nRow);
    }

    return QVariant();
}

void SoundListModelItem::loadAlarmList()
{
    QString sPath = "C:/Windows/Media";

    QDirIterator it(sPath, QDir::Files);

    while (it.hasNext()) {
        it.next();
        if ( it.fileName().indexOf("Alarm") != -1 ) {
            alarmSoundList.append(it.fileName());
        }
    }
}
