#include "ConfigureDialog.h"
#include <QQmlComponent>
#include <QQmlContext>

ConfigureDialog::ConfigureDialog(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
    , m_pView(NULL)
    , m_pEngine(engine)
{
    m_pView = new QQuickWindow();
}

void ConfigureDialog::Show()
{
    if ( m_pView == NULL ) { return; }

    QQmlComponent comp(m_pEngine, QUrl(QStringLiteral("qrc:/SettingDialog.qml")));
    m_pView = qobject_cast<QQuickWindow*>(comp.create(m_pEngine->rootContext()));
    connect(m_pView, SIGNAL(emit_changeColor(QColor)), this, SLOT(Slot_GetColor(QColor)), Qt::UniqueConnection);
    connect(m_pView, SIGNAL(emit_changeOpcaity(double)), this, SLOT(Slot_GetOpacity(double)), Qt::UniqueConnection);
    connect(m_pView, SIGNAL(emit_changeAlwaysOnTop(bool)), this, SLOT(Slot_GetAlwaysOnTop(bool)), Qt::UniqueConnection);
    connect(m_pView, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(Slot_Close()), Qt::UniqueConnection);

    m_pEngine->rootContext()->setContextProperty("contorlDlg",this);

    m_pView->show();

    if ( m_pEngine->rootObjects().count() < 1 ) { return; }

    QQuickWindow* pObject = qobject_cast<QQuickWindow*>(m_pEngine->rootObjects().value(0));
    m_pView->show();
    int x = m_pView->geometry().x() + pObject->width();
    m_pView->setX(x);
}

void ConfigureDialog::SetSettingValue(TimerSetting &setValue)
{
    m_pView->setProperty("backColor", setValue.color);
    m_pView->setProperty("dOpacity", setValue.opacity);
    m_pView->setProperty("bAlwaysOnTop", setValue.bAlwaysOnTop);
}

void ConfigureDialog::Slot_GetColor(QColor color)
{
    emit Emit_setColor(color);
}

void ConfigureDialog::Slot_GetOpacity(double dOpacity)
{
    emit Emit_setOpacity(dOpacity);
}

void ConfigureDialog::Slot_GetAlwaysOnTop(bool bChecked)
{
    emit Emit_setAlwaysOnTop(bChecked);
}

void ConfigureDialog::Slot_Close()
{
    emit Emit_Close();
}

ConfigureDialog::~ConfigureDialog()
{
    if ( m_pView != NULL ) {
        delete m_pView;
        m_pView = NULL;
    }
}
