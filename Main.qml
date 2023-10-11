import QtQuick
import QtQuick.Window

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component.onCompleted: {
        console.log(`Component.onCompleted`)
        console.log(`hotkeyManager=${hotkeyManager}`)
        var hotkeys = hotkeyManager.hotkeys
        console.log(`hotkeys=${hotkeys}`)
        var hotkeyInfo1 = hotkeys[1]
        console.log(`hotkeyInfo1=${hotkeyInfo1}`)
        console.log(`hotkeyInfo1.computerName=${hotkeyInfo1.computerName}`)
        console.log(`hotkeyInfo1.appName=${hotkeyInfo1.appName}`)
        var hotkeyInfo2 = hotkeys[2]
        console.log(`hotkeyInfo2=${hotkeyInfo2}`)
        console.log(`hotkeyInfo2.computerName=${hotkeyInfo2.computerName}`)
        console.log(`hotkeyInfo2.appName=${hotkeyInfo2.appName}`)
    }
}
