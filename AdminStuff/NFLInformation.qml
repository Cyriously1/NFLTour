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
                        nflInformationModel.submitAll()
                        nflInformationModel.select()
                        console.log("Changes were made to the database...")
                    }
                    onNo: {
                        nflInformationModel.select()
                        console.log("No changes made to the database...")
                    }

                    Component.onCompleted: visible = false
                }
            }
            Button {
                id: addSailorsButton
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                text: qsTr("Add Sailors")
                onClicked: {
                    addSailorsButton.visible = false
                    fileDialog.open()
                }

                FileDialog {
                    id: fileDialog
                    title: "Please choose a file"
                    nameFilters: ["Text file (*.txt)"]
                    selectExisting: true
                    onAccepted: {
                        console.log("You chose: " + fileDialog.fileUrls)
                        slotObject.setInput(fileDialog.fileUrl)
                        slotObject.addSailors()
                        nflInformationModel.select()
                        addSailorsMsg.open()
                    }
                    onRejected: {
                        console.log("Canceled")
                        addSailorsButton.visible = true
                    }
                    Component.onCompleted: visible = false
                }

                MessageDialog {
                    id: addSailorsMsg
                    title: "Add Sailors Status"
                    icon: StandardIcon.Information
                    standardButtons: StandardButton.Ok
                    text: "The San Diego Sailors have been successfully added to the database."

                    Component.onCompleted: visible = false
                }
            }
            Button {
                id: moveRamsButton
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                text: qsTr("Move Rams")
                onClicked: {
                    moveRamsMsg.open()
                    moveRamsButton.visible = false
                    slotObject.moveRams()
                    nflInformationModel.select()
                }

                MessageDialog {
                    id: moveRamsMsg
                    title: "Move Rams Status"
                    icon: StandardIcon.Information
                    standardButtons: StandardButton.Ok
                    text: "The Los Angeles Rams have been successfully moved to the Farmers Field."

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
                            if(styleData.role === "TeamName" ||
                               styleData.role === "StadiumName" ||
                               styleData.role === "Location" ||
                               styleData.role === "StarPlayer")
                            {
                                editLoader.sourceComponent = textInputDelegate
                            }
                            else if(styleData.role === "SeatingCapacity")
                            {
                                editLoader.sourceComponent = seatingDelegate
                            }
                            else if(styleData.role === "Conference")
                            {
                                editLoader.sourceComponent = conferenceDelegate
                                mouseArea.visible = false
                            }
                            else if(styleData.role === "StadiumRoofType")
                            {
                                editLoader.sourceComponent = roofTypeDelegate
                                mouseArea.visible = false
                            }
                            else if(styleData.role === "SurfaceType")
                            {
                                editLoader.sourceComponent = surfaceTypeDelegate
                                mouseArea.visible = false
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
                                validator: RegExpValidator { regExp: /[a-zA-Z\\s(&)(,)(.)( )]+/ }

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
                        id: seatingDelegate
                        Item {
                            TextInput {
                                id: textInput
                                text: styleData.value
                                focus:true
                                color: "#2196F3"
                                validator: RegExpValidator { regExp: /^\d{1,3}(,\d{3})*(\\d+)?$/ }

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
                    Component {
                        id: conferenceDelegate
                        Item {
                            ComboBox {
                                id: comboBox
                                height: 35
                                width: mainPage.width /8
                                font.pixelSize: 10
                                model: ListModel {
                                        id: model
                                        ListElement { text: "National Football Conference" }
                                        ListElement { text: "American Football Conference" }
                                    }
                                onActivated: {
                                    textDelegate.text = comboBox.currentText
                                    textDelegate.visible = true
                                    editLoader.visible = false
                                    proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),comboBox.currentText,2)
                                    mouseArea.visible = true
                                }
                            }
                        }
                    }
                    Component {
                        id: roofTypeDelegate
                        Item {
                            ComboBox {
                                id: comboBox
                                height: 35
                                width: mainPage.width /8
                                font.pixelSize: 12
                                model: ListModel {
                                        id: model
                                        ListElement { text: "Open" }
                                        ListElement { text: "Retractable" }
                                        ListElement { text: "Fixed" }
                                    }
                                onActivated: {
                                    textDelegate.text = comboBox.currentText
                                    textDelegate.visible = true
                                    editLoader.visible = false
                                    proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),comboBox.currentText,2)
                                    mouseArea.visible = true
                                }
                            }
                        }
                    }
                    Component {
                        id: surfaceTypeDelegate
                        Item {
                            ComboBox {
                                id: comboBox
                                height: 35
                                width: mainPage.width /8
                                font.pixelSize: 9
                                model: ListModel {
                                        id: model
                                        ListElement { text: "A-Turf Titan 50 (artificial)" } //0
                                        ListElement { text: "Bandera Bermuda Grass" } //1
                                        ListElement { text: "Desso GrassMaster" } //2
                                        ListElement { text: "FieldTurf Classic HD" } //3
                                        ListElement { text: "FieldTurf Revolution" } //4
                                        ListElement { text: "Hybrid Grass-Synthetic" } //5
                                        ListElement { text: "Kentucky Bluegrass" } //6
                                        ListElement { text: "Latitude 36 Bermuda Grass" } //7
                                        ListElement { text: "Matrix RealGrass artificial turf" } //8
                                        ListElement { text: "Platinum TE Paspalum" } //9
                                        ListElement { text: "Santa Ana Bermuda Grass" } //10
                                        ListElement { text: "TifSport Bermuda Grass" } //11
                                        ListElement { text: "Tifway 419 Bermuda Grass" } //12
                                        ListElement { text: "Tifway II Bermuda Grass" } //13
                                        ListElement { text: "Tifway II Bermuda Grass Perennial Ryegrass mixture" } //14
                                        ListElement { text: "UBU Speed Series S5-M Synthetic Turf" } //15
                                        ListElement { text: "Voyager Bermuda Grass" } //16
                                    }
                                onActivated: {
                                    textDelegate.text = comboBox.currentText
                                    textDelegate.visible = true
                                    editLoader.visible = false
                                    proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),comboBox.currentText,2)
                                    mouseArea.visible = true
                                }
                            }
                        }
                    }

                }

                model: proxyModel

                TableViewColumn{ role: "TeamName" ; title: "Team Name"; width: mainPage.width / 8}
                TableViewColumn{ role: "StadiumName" ; title: "Stadium Name"; width: mainPage.width / 8}
                TableViewColumn{ role: "SeatingCapacity" ; title: "Seating Capacity"; width: mainPage.width / 8}
                TableViewColumn{ role: "Location" ; title: "Location"; width: mainPage.width / 8}
                TableViewColumn{ role: "Conference" ; title: "Conference"; width: mainPage.width / 8}
                TableViewColumn{ role: "SurfaceType" ; title: "Surface Type"; width: mainPage.width / 8}
                TableViewColumn{ role: "StadiumRoofType" ; title: "Stadium Roof Type"; width: mainPage.width / 8}
                TableViewColumn{ role: "StarPlayer" ; title: "Star Player"; width: mainPage.width / 8}
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
                source: nflInformationModel

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


