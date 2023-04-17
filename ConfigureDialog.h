#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QObject>
#include <QQuickWindow>
#include <QQmlApplicationEngine>

typedef struct _TimerSetting {
    QColor color;
    double opacity;
    bool bAlwaysOnTop;

    _TimerSetting() {
        color.setRgb(0,0,0);
        opacity = 0;
        bAlwaysOnTop = false;
    }
} TimerSetting;

class ConfigureDialog : public QObject
{
    Q_OBJECT
public:
    explicit ConfigureDialog(QObject *parent = nullptr, QQmlApplicationEngine* engine= NULL);
    ~ConfigureDialog();
    void Show();
    void SetSettingValue(TimerSetting& setValue);
signals:
    void Emit_setColor(QColor color);
    void Emit_setOpacity(double dOpacity);
    void Emit_setAlwaysOnTop(bool bChecked);
    void Emit_Close();

public slots:
    void Slot_GetColor(QColor color);
    void Slot_GetOpacity(double dOpacity);
    void Slot_GetAlwaysOnTop(bool bChecked);
    void Slot_Close();

private:
    QQuickWindow* m_pView;
    QQmlApplicationEngine* m_pEngine;
};

#endif // CONFIGUREDIALOG_H
