import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.2

ApplicationWindow {
    id: adminWindow
    visible: true
    width: 1250
    height: 850
    title: qsTr("Admin Window")

    FontLoader { id: localFont; source: "qrc:/Pics/BebasNeueRegular.otf" }

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.foreground: Material.Blue

    // Main stackview
    StackView{
        id: stackView
        focus: true
        anchors.fill: parent
    }

    Component.onCompleted: {
        stackView.push("qrc:/AdminStuff/NFLDistances.qml")   //initial page
    }

    function showMainWindow()
    {
        var mainComponent = Qt.createComponent("qrc:/main.qml");
        console.log("Component Status:", mainComponent.status, mainComponent.errorString());
        var main = mainComponent.createObject(adminWindow);
        adminWindow.close();
        main.show();
    }
}
