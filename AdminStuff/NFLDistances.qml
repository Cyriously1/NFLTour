import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
//import SortFilterProxyModel 0.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Page {
    id: mainPage

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.foreground: Material.Blue

    ScrollView {
        anchors.fill: parent
        ColumnLayout {
            id: mainPageLayout
            spacing: 2
            Layout.fillWidth: true
            //                    anchors.horizontalCenter: parent.horizontalCenter
            Image {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: mainPage.width
                Layout.preferredHeight: mainPage.height / 1.5
                source: "qrc:/Pics/Admin.jpg"
            }

            TableView {
                id: adminInfoTable
                visible: true
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: mainPage.width
                Layout.preferredHeight: mainPage.height / 1.25
                property int currentColumn: 0
                highlightOnFocus: false
                style: TableViewStyle
                {
                    textColor: "#2196F3"
                    backgroundColor: "#303030"
                    alternateBackgroundColor: "#303030"
                }

                rowDelegate: Rectangle {
                            color: "#fff"
                        }
                itemDelegate: Rectangle {
                    //            color: "transparent"
                    color: {
                        var bgColor = model.index%2 ? "#303030" : "#404040"
                        var activeRow = adminInfoTable.currentRow === styleData.row
                        var activeColumn = adminInfoTable.currentColumn === styleData.column
                        activeRow && activeColumn ? "steelblue" : bgColor
                    }
                    Text {
                        text: styleData.value
                        color: "#2196F3"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            print("(onClick) index: (" + model.index + "," + adminInfoTable.currentColumn+ ")")
                            adminInfoTable.currentRow = styleData.row
                            adminInfoTable.currentColumn = styleData.column
                            model.currentIndex = styleData.row
                            parent.forceActiveFocus()
                        }
                    }
                    Keys.onRightPressed: {
                        console.log("Delegate Right")
                        if (adminInfoTable.currentColumn < adminInfoTable.columnCount - 1)
                            adminInfoTable.currentColumn++
                        parent.forceActiveFocus()
                        print("(Right) index: (" + adminInfoTable.currentRow + "," + adminInfoTable.currentColumn+ ")")
                    }

                    Keys.onLeftPressed: {
                        console.log("Delegate Left")
                        if (adminInfoTable.currentColumn > 0)
                            adminInfoTable.currentColumn--
                        parent.forceActiveFocus()
                        print("(Left) index: (" + adminInfoTable.currentRow + "," + adminInfoTable.currentColumn+ ")")
                    }
                }

                model: adminModel

                TableViewColumn{ role: "TeamName" ; title: "Team Name"}
                TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                TableViewColumn{ role: "SeatingCapacity" ; title: "Seating Capacity" }
                TableViewColumn{ role: "Location" ; title: "Location" }
                TableViewColumn{ role: "Conference" ; title: "Conference" }
                TableViewColumn{ role: "SurfaceType" ; title: "Surface Type" }
                TableViewColumn{ role: "StadiumRoofType" ; title: "Stadium Roof Type" }
                TableViewColumn{ role: "StarPlayer" ; title: "Star Player" }
                Component.onCompleted: {
                    //                adminInfoTable.model = proxyModel
                    //                adminInfoTable.currentRow = -1

                }
                onClicked: {
                    //                console.log(nflInfoModel.index(nflInfoTable.currentRow,1, parent))
                    //                console.log(nflInfoModel.data(nflInfoModel.index(nflInfoTable.currentRow,1, parent), "TeamName"))
                }
            }

        }
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
        MenuItem {
            text: "Show NFL Distances"
        }
        MenuItem {
            text: "Show NFL Souvenirs"
        }
        MenuItem {
            text: "Show NFL Teams"
        }
    }

    Component {
        id: textInputDelegate

        Item {
            TextInput
            {
                visible: false
                color: "#2196F3"
                anchors.fill: parent
                text: styleData.value
                font.pixelSize: 12
            }
        }
    }
}


