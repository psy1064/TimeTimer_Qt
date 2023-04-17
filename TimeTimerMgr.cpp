#include "TimeTimerMgr.h"
#include <QQmlProperty>

TimeTimerMgr::TimeTimerMgr(QObject *parent)
    : QObject{parent}
    , m_pDialog(NULL)
    , m_engine(NULL)
    , m_pWindow(NULL)
    , m_pTimeCanvas(NULL)
    , m_nTime(0)
    , m_nCount(0)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(Slot_Timeout()), Qt::UniqueConnection);
}

void TimeTimerMgr::showDialog()
{
    if ( m_pDialog != NULL ) { return; }
    m_pDialog = new ConfigureDialog(this, m_engine);

    connect(m_pDialog, SIGNAL(Emit_setColor(QColor)), this, SLOT(Slot_GetColor(QColor)), Qt::UniqueConnection);
    connect(m_pDialog, SIGNAL(Emit_setOpacity(double)), this, SLOT(Slot_GetOpacity(double)), Qt::UniqueConnection);
    connect(m_pDialog, SIGNAL(Emit_setAlwaysOnTop(bool)), this, SLOT(Slot_GetAlwaysOnTop(bool)), Qt::UniqueConnection);
    connect(m_pDialog, SIGNAL(Emit_Close()), this, SLOT(Slot_DialogClose()), Qt::UniqueConnection);

    TimerSetting settingValue;
    settingValue.color        = m_pTimeCanvas->property("timeColor").value<QColor>();
    settingValue.opacity      = m_pWindow->property("dOpacity").toDouble();
    settingValue.bAlwaysOnTop = m_pWindow->property("bAlwaysOnTop").toBool();

    m_pDialog->Show();
    m_pDialog->SetSettingValue(settingValue);
}

void TimeTimerMgr::Slot_Start()
{
    m_nTime = m_pTimeCanvas->property("setMinute").toInt();
    timer.start(1000);
}

void TimeTimerMgr::Slot_Pause()
{
    timer.stop();
}

void TimeTimerMgr::Slot_Stop()
{
    timer.stop();
    m_pTimeCanvas->setProperty("setSecond", (m_nTime*60));
    QMetaObject::invokeMethod(m_pTimeCanvas, "rePaint");
    m_nCount = 0;
}

void TimeTimerMgr::Slot_Timeout()
{
    m_nCount++;
    m_pTimeCanvas->setProperty("setSecond", (m_nTime*60-m_nCount));
    QMetaObject::invokeMethod(m_pTimeCanvas, "rePaint");

    if ( m_nTime*60 == m_nCount ) {
        timer.stop();
    }
}

void TimeTimerMgr::Slot_GetColor(QColor color)
{
    m_pTimeCanvas->setProperty("timeColor", color);
    QMetaObject::invokeMethod(m_pTimeCanvas, "rePaint");
}

void TimeTimerMgr::Slot_GetOpacity(double dOpacity)
{
    m_pWindow->setProperty("dOpacity", dOpacity);
}

void TimeTimerMgr::Slot_GetAlwaysOnTop(bool bChecked)
{
    m_pWindow->setProperty("bAlwaysOnTop", bChecked);

    m_pWindow->setFlag(Qt::WindowStaysOnTopHint, bChecked);
}

void TimeTimerMgr::Slot_DialogClose()
{
    m_pDialog = NULL;
}

TimeTimerMgr::~TimeTimerMgr()
{
    if ( m_pDialog != NULL ) {
        delete m_pDialog;
        m_pDialog = NULL;
    }
}

void TimeTimerMgr::SetEngine(QQmlApplicationEngine* engine)
{
    m_engine = engine;
    InitIteragte();
}

void TimeTimerMgr::InitIteragte()
{
    if ( m_engine == NULL ) { return; }
    m_engine->rootContext()->setContextProperty("timerMgr",this);
    QList<QObject*> objectList = m_engine->rootObjects();

    if ( objectList.count() < 1 ) { return; }
    m_pWindow = qobject_cast<QQuickWindow*>(objectList.value(0));

    if ( m_pWindow == NULL ) { return; }
    connect(m_pWindow, SIGNAL(emit_Start()), this, SLOT(Slot_Start()), Qt::UniqueConnection);
    connect(m_pWindow, SIGNAL(emit_Pause()), this, SLOT(Slot_Pause()), Qt::UniqueConnection);
    connect(m_pWindow, SIGNAL(emit_Stop()), this, SLOT(Slot_Stop()), Qt::UniqueConnection);

    m_pTimeCanvas = m_pWindow->findChild<QObject*>("timeCanvas");
}
