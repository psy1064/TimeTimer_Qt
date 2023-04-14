#ifndef TIMETIMERMGR_H
#define TIMETIMERMGR_H

#include <QObject>
#include <QTimer>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ConfigureDialog.h"


class TimeTimerMgr : public QObject
{
    Q_OBJECT
public:
    explicit TimeTimerMgr(QObject *parent = nullptr);
    ~TimeTimerMgr();

    void SetEngine(QQmlApplicationEngine *engine);
    void InitIteragte();

    Q_INVOKABLE void showDialog();

public slots:
    void Slot_Start();
    void Slot_Pause();
    void Slot_Stop();
    void Slot_Timeout();

    void Slot_GetColor(QColor color);
    void Slot_GetOpacity(double dOpacity);
    void Slot_GetAlwaysOnTop(bool bChecked);

signals:

private:
    ConfigureDialog* pDialog;
    QQmlApplicationEngine* m_engine;
    QObject* m_pWindow;
    QObject* m_pTimeCanvas;
    QTimer timer;
    int m_nTime;
    int m_nCount;
};

#endif // TIMETIMERMGR_H
