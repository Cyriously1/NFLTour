import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import SortFilterProxyModel 0.1
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

            Button {
                id: teamInfoButton
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                text: qsTr("Commit Change(s)")
                onClicked: {
                    messageDialog.open()
                }
                MessageDialog {
                    id: messageDialog
                    title: "Warning"
                    icon: StandardIcon.Warning
                    standardButtons: StandardButton.Yes | StandardButton.No
                    text: "Are you sure you want to commit changes to the database?"
                    detailedText: "Clicking yes will update the database with currently displayed table's data."
                    onYes: {
                        adminModel.submitAll()
                        console.log("Changes were made to the database...")
                    }
                    onNo: {
                        console.log("No changes made to the database...")
                    }

                    Component.onCompleted: visible = false
                }
            }

            Rectangle {
                id: nflSearchRect
                visible: true
                border.width: 2
                border.color: "#2196F3"
                radius: 5
                width: mainPage.width / 7
                height: 20
                anchors.left: parent.left

                TextInput {
                    id: nflInfoSearch
                    objectName: "qmlText"
                    clip: true
                    width: nflSearchRect.width - 5
                    color: "black"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 14
                    onTextEdited: {

                    }
                }
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
                            height: 30
                        }
                itemDelegate: Rectangle {
                    //            color: "transparent"
                    color: {
                        var bgColor = model.index%2 ? "#303030" : "#404040"
                        var activeRow = adminInfoTable.currentRow === styleData.row
                        var activeColumn = adminInfoTable.currentColumn === styleData.column
                        activeRow && activeColumn ? "#202020" : bgColor
                    }
                    Text {
                        id: textDelegate
                        text: styleData.value
                        focus:true
                        color: "#2196F3"
                    }

                    Loader {
                            id: editLoader
                        }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            print("(onClick) index: (" + model.index + "," + adminInfoTable.currentColumn+ ")")
                            adminInfoTable.currentRow = styleData.row
                            adminInfoTable.currentColumn = styleData.column
                            model.currentIndex = styleData.row
                            parent.forceActiveFocus()
                            console.log(styleData.role)
                            console.log(proxyModel.data(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent)))
                        }
                        onDoubleClicked:
                        {
                            adminInfoTable.currentRow = styleData.row
                            adminInfoTable.currentColumn = styleData.column
                            model.currentIndex = styleData.row
//                            parent.forceActiveFocus()
                            textDelegate.visible = false
                            editLoader.visible = true
                            if(styleData.role == "Beginning" ||
                               styleData.role == "Ending" ||
                               styleData.role == "TeamName" ||
                               styleData.role == "StadiumName" ||
                               styleData.role == "Location" ||
                               styleData.role == "StarPlayer" ||
                               styleData.role == "Stadium" ||
                               styleData.role == "Name")
                            {
                                editLoader.sourceComponent = textInputDelegate
                            }
                            editLoader.forceActiveFocus()
                        }
                    }
                    Component {
                        id: textInputDelegate
                        Item {
                            TextInput {
                                id: textInput
                                text: styleData.value
                                focus:true
                                color: "#2196F3"
                                validator: RegExpValidator { regExp: /[a-zA-Z\\s(,)(.)( )]+/ }
                                Loader {
                                    id: confirmLoader
                                }

                                onAccepted:
                                {
                                    textDelegate.text = text
                                    textDelegate.visible = true
//                                    textInput.visible = false
                                    editLoader.visible = false
                                    proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),text,2)
                                }
                            }
                        }
                    }

                }

                model: proxyModel

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
            SortFilterProxyModel {
                id: proxyModel
                source: adminModel

                sortOrder: adminInfoTable.sortIndicatorOrder
                sortCaseSensitivity: Qt.CaseInsensitive
                sortRole: adminInfoTable.getColumn(adminInfoTable.sortIndicatorColumn).role

                filterString: "*" + nflInfoSearch.text + "*"
                filterSyntax: SortFilterProxyModel.Wildcard
                filterCaseSensitivity: Qt.CaseInsensitive

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

//    Component {
//        id: textInputDelegate

//        Item {
//            TextInput {
//                id: textInput
//                text: styleData.value
//                focus:true
//                color: "#2196F3"
//                Keys.onEnterPressed: {

//                }
//            }
//        }
//    }
}


