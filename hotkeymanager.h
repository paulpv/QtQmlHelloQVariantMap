#pragma once

#include <QVariant>

class HotkeyInfo : public QObject
{
    Q_OBJECT
public:
    HotkeyInfo(const QString& computerName, const QString& appName) :
        m_computerName(computerName),
        m_appName(appName)
    {}

    Q_PROPERTY(QString computerName MEMBER m_computerName)
    Q_PROPERTY(QString appName MEMBER m_appName)

    operator QString() const {
        return QString("HotkeyInfo(computerName=\"%1\", appName=\"%2\")")
            .arg(m_computerName, m_appName);
    }

private:
    QString m_computerName;
    QString m_appName;
};
Q_DECLARE_METATYPE(HotkeyInfo)

#define HOTKEYMANAGER_MAPHOTKEYS_STRING_VARIANT
//#define HOTKEYMANAGER_MAPHOTKEYS_STRING_HOTKEYINFO
//#define HOTKEYMANAGER_MAPHOTKEYS_INT_VARIANT
//#define HOTKEYMANAGER_MAPHOTKEYS_INT_HOTKEYINFO

#if defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_VARIANT)
// This currently only works in qml if key is a QString key and value is a QVariant.
using MapHotkeys = QMap<QString, QVariant>;
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_HOTKEYINFO)
// TODO:(pv) Find out how to get a custom QObject value to work.
using MapHotkeys = QMap<QString, HotkeyInfo*>;
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_VARIANT)
// TODO:(pv) Find out how to get **just** an int key to work.
using MapHotkeys = QMap<int, QVariant>;
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_HOTKEYINFO)
// TODO:(pv) Find out how to get an int key **and** custom QObject value to work.
using MapHotkeys = QMap<int, HotkeyInfo*>;
#endif

class HotkeyManager : public QObject
{
    Q_OBJECT
public:
    HotkeyManager() {}
    ~HotkeyManager() {
        clear();
    }

    Q_PROPERTY(MapHotkeys hotkeys MEMBER m_hotkeys)

    void add(const int key, HotkeyInfo* hotkeyInfo) {
#if defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_VARIANT)
        m_hotkeys[QString::number(key)] = QVariant::fromValue(hotkeyInfo);
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_HOTKEYINFO)
        m_hotkeys[QString::number(key)] = hotkeyInfo;
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_VARIANT)
        m_hotkeys[key] = QVariant::fromValue(hotkeyInfo);
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_HOTKEYINFO)
        m_hotkeys[key] = hotkeyInfo;
#endif
    }

    void remove(const int key) {
#if defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_VARIANT)
        auto hotkeyInfo = m_hotkeys.take(QString::number(key)).value<HotkeyInfo*>();
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_HOTKEYINFO)
        auto hotkeyInfo = m_hotkeys.take(QString::number(key));
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_VARIANT)
        auto hotkeyInfo = m_hotkeys.take(key).value<HotkeyInfo*>();
#elif defined(HOTKEYMANAGER_MAPHOTKEYS_INT_HOTKEYINFO)
        auto hotkeyInfo = m_hotkeys.take(key);
#endif
        if (hotkeyInfo != nullptr) {
            delete hotkeyInfo;
        }
    }

    void clear() {
        for (auto it = m_hotkeys.begin(); it != m_hotkeys.end(); it = m_hotkeys.erase(it)) {
#if defined(HOTKEYMANAGER_MAPHOTKEYS_STRING_VARIANT) || defined(HOTKEYMANAGER_MAPHOTKEYS_INT_VARIANT)
            auto hotkeyInfo = it.value().value<HotkeyInfo*>();
#else
            auto hotkeyInfo = it.value();
#endif
            qDebug() << "deleting hotkeyInfo=" << *hotkeyInfo << " for key=" << it.key();
            delete hotkeyInfo;
        }
    }

private:
    MapHotkeys m_hotkeys;
};
