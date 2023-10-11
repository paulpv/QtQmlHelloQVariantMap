#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "hotkeymanager.h"


// NOLINTBEGIN(clang-analyzer-cplusplus.NewDeleteLeaks)
void initializeMessages(HotkeyManager& hotkeyManager)
{
    // Ignore NewDeleteLeaks; ~HotkeyManager frees all added HotkeyInfos.
    hotkeyManager.add(1, new HotkeyInfo("computer1", "app2"));
    hotkeyManager.add(2, new HotkeyInfo("computer2", "app4"));
}
// NOLINTEND(clang-analyzer-cplusplus.NewDeleteLeaks)

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    HotkeyManager hotkeyManager;
    initializeMessages(hotkeyManager);

    engine.rootContext()->setContextProperty("hotkeyManager", &hotkeyManager);

    engine.loadFromModule("QtQmlHelloQVariantMap", "Main");

    return app.exec();
}
