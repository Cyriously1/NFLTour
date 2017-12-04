import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: adminWindow
    visible: true
    width: 1350
    height: 850
    title: qsTr("Admin Window")
//    property int fontSize: 15
//    font.pixelSize: fontSize

//    FontLoader { id: localFont; source: "qrc:/Pics/BebasNeueRegular.otf" }

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

    header: ToolBar {
        id: toolBar
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                font.pixelSize: 30
                onClicked: {
                    showMainWindow()
                }
            }
            Label {
                text: "Administration"
                color: "#2196F3"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                id: toolButton
                text: qsTr("⋮")
                font.pixelSize: 30
                onClicked: menu.open()
            }
        }
        background: Rectangle {
            color: "#303030"

        }
    }

    Menu {
        id: menu
        x: toolBar.width
        property string currentPage: "NFLDistances"
        MenuItem {
            id: showNFLDistances
            text: "Show NFL Distances"
            onClicked: {
                if(menu.currentPage != "NFLDistances")
                {
                    stackView.pop(stackView.currentItem)
                    stackView.push("qrc:/AdminStuff/NFLDistances.qml")
                    menu.currentPage = "NFLDistances"
//                    fontSize = 15
                }
            }
        }
        MenuItem {
            id: showNFLSouvenirs
            text: "Show NFL Souvenirs"
            onClicked: {
                if(menu.currentPage != "NFLSouvenirs")
                {
                    stackView.pop(stackView.currentItem)
                    stackView.push("qrc:/AdminStuff/NFLSouvenirs.qml")
                    menu.currentPage = "NFLSouvenirs"
//                    fontSize = 12
                }
            }
        }
        MenuItem {
            id: showNFLTeams
            text: "Show NFL Teams"
            onClicked: {
                if(menu.currentPage != "NFLInformation")
                {
                    stackView.pop(stackView.currentItem)
                    stackView.push("qrc:/AdminStuff/NFLInformation.qml")
//                    fontSize = 15
                    menu.currentPage = "NFLInformation"
                }
            }
        }
    }
}
