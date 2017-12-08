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
                        nflDistancesModel.submitAll()
                        nflDistancesModel.select()
                        console.log("Changes were made to the database...")
                    }
                    onNo: {
                        nflDistancesModel.select()
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
                        id: mouseArea
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
                            if(styleData.role === "Beginning" ||
                                    styleData.role === "Ending")
                            {
                                editLoader.sourceComponent = textInputDelegate
                            }
                            else if(styleData.role === "Distance")
                            {
                                editLoader.sourceComponent = spinBoxDelegate
//                                mouseArea.visible = false
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
                                validator: RegExpValidator { regExp: /[a-zA-Z\s(&)(.)( )]+/ }

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
                    Component {
                        id: spinBoxDelegate
                        Item {
                            TextInput {
                                id: textInput
                                text: styleData.value
                                focus:true
                                color: "#2196F3"
//                                validator: RegExpValidator { regExp: /([1-9]|[1-8][0-9]|9[0-9]|[1-8][0-9]{2}|9[0-8][0-9]|99[0-9]|[12][0-9]{3}|3000)/ }
                                validator: IntValidator { bottom:1; top: 3000}

                                onAccepted:
                                {
                                    textDelegate.text = text
                                    textDelegate.visible = true
                                    editLoader.visible = false
                                    proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),text,2)
                                }
                            }
                        }
                    }

                }

                model: proxyModel

                TableViewColumn{ role: "Beginning" ; title: "Beginning"; width: mainPage.width / 3}
                TableViewColumn{ role: "Ending" ; title: "Ending"; width: mainPage.width / 3 }
                TableViewColumn{ role: "Distance" ; title: "Distance"; width: mainPage.width / 3 }
                Component.onCompleted: {
                    //                    distanceColumn.resizeToContents()
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
                source: nflDistancesModel

                sortOrder: adminInfoTable.sortIndicatorOrder
                sortCaseSensitivity: Qt.CaseInsensitive
                sortRole: adminInfoTable.getColumn(adminInfoTable.sortIndicatorColumn).role

                filterString: "*" + nflInfoSearch.text + "*"
                filterSyntax: SortFilterProxyModel.Wildcard
                filterCaseSensitivity: Qt.CaseInsensitive

            }

        }
    }
}


