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
                        nflSouvenirsModel.submitAll()
                        console.log("Changes were made to the database...")
                    }
                    onNo: {
                        console.log("No changes made to the database...")
                    }

                    Component.onCompleted: visible = false
                }
            }
            Button {
                id: addSouvenirButton
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                text: qsTr("Add Souvenir")
                onClicked: {
                    addSouvColumn.visible ? addSouvColumn.visible = false : addSouvColumn.visible = true
                }
            }

            ColumnLayout {
                id: addSouvColumn
                Layout.alignment: Qt.AlignCenter
                visible: false
                Label {
                    Layout.alignment: Qt.AlignCenter
                    text: "Add Souvenir"
                    font.pixelSize: 24
                    font.bold: true
                }

                RowLayout {
                    Layout.alignment: Qt.AlignCenter
                    Label {
                        Layout.alignment: Qt.AlignCenter
                        text: "Choose a Stadium:     "
                    }
                    ComboBox {
                        id: chooseStadiumCombo
                        Layout.preferredWidth: mainPage.width / 5
                        Layout.alignment: Qt.AlignRight
                        height: 35
                        model: ListModel {
                            id: model
                            ListElement { text: "AT&T Stadium"}
                            ListElement { text: "Arrowhead Stadium" }
                            ListElement { text: "Bank of America Stadium" }
                            ListElement { text: "CenturyLink Field" }
                            ListElement { text: "EverBank Field" }
                            ListElement { text: "FedExField" }
                            ListElement { text: "FirstEnergy Stadium" }
                            ListElement { text: "Ford Field" }
                            ListElement { text: "Georgia Dome" }
                            ListElement { text: "Gillette Stadium" }
                            ListElement { text: "Hard Rock Stadium" }
                            ListElement { text: "Heinz Field" }
                            ListElement { text: "Lambeau Field" }
                            ListElement { text: "Levi's Stadium" }
                            ListElement { text: "Lincoln Financial Field" }
                            ListElement { text: "Los Angeles Memorial Coliseum" }
                            ListElement { text: "Lucas Oil Stadium" }
                            ListElement { text: "M&T Bank Stadium" }
                            ListElement { text: "Mercedes-Benz Superdome" }
                            ListElement { text: "MetLife Stadium" }
                            ListElement { text: "NRG Stadium" }
                            ListElement { text: "Nissan Stadium" }
                            ListElement { text: "Oakland Alameda Coliseum" }
                            ListElement { text: "Paul Brown Stadium" }
                            ListElement { text: "Qualcomm Stadium" }
                            ListElement { text: "Ralph Wilson Stadium" }
                            ListElement { text: "Raymond James Stadium" }
                            ListElement { text: "Soldier Field" }
                            ListElement { text: "Sports Authority Field at Mile High" }
                            ListElement { text: "Stub Hub Stadium" }
                            ListElement { text: "U.S. Bank Stadium" }
                            ListElement { text: "University of Phoenix Stadium" }
                        }
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignCenter
                    Label {
                        Layout.alignment: Qt.AlignCenter
                        text: "New Souvenir Name:     "
                    }
                    Rectangle {
                        id: newSouvRect
                        visible: true
                        border.width: 2
                        border.color: "#2196F3"
                        radius: 5
                        width: mainPage.width / 7
                        Layout.alignment: Qt.AlignRight
                        height: 20
                        //                        anchors.left: parent.left
                        TextInput {
                            id: newSouvName
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.left: parent.left
                            color: "black"
                            padding: 5
                            validator: RegExpValidator { regExp: /[a-zA-Z\s( )]+/ }
                        }
                    }
                } //NewSouv RowLayout

                RowLayout {
                    Layout.alignment: Qt.AlignCenter
                    Label {
                        Layout.alignment: Qt.AlignCenter
                        text: "New Souvenir Price:      "
                    }
                    Rectangle {
                        id: newSouvPriceRect
                        visible: true
                        border.width: 2
                        border.color: "#2196F3"
                        radius: 5
                        width: mainPage.width / 7
                        Layout.alignment: Qt.AlignRight
                        height: 20
                        //                        anchors.left: parent.left
                        TextInput {
                            id: newSouvPrice
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.left: parent.left
                            color: "black"
                            padding: 5
                            validator: DoubleValidator { bottom:1; top: 5000; decimals: 2}
                            onTextEdited: {
                                if(!newSouvPrice.acceptableInput && newSouvPrice.text.length != 0)
                                {
                                    invalidInputMsg.open()
                                    newSouvPrice.undo()
                                    console.log("Invalid Input...")
                                }
                            }

                            MessageDialog {
                                id: invalidInputMsg
                                title: "Warning"
                                icon: StandardIcon.Warning
                                text: "Invalid Price. Please enter a double between 1 and 5000"
                                onAccepted: {
                                    void close()
                                }
                                Component.onCompleted: visible = false
                            }
                        }
                    }
                }

                Button {
                    id: addSouvenirFinal
                    text: "Add Souvenir"
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredWidth: mainPage.width / 4
                    onClicked: {
                        addSouvFinalMsg.open()
                    }
                    MessageDialog {
                        id: addSouvFinalMsg
                        title: "Confirm Souvenir Addition"
                        icon: StandardIcon.Warning
                        standardButtons: StandardButton.Yes | StandardButton.No
                        text: "Are you sure you want to add this souvenir to the database?"
                        detailedText: "Clicking yes will update the database with the newly created souvenir."
                        onYes: {

                            console.log("Changes were made to the database...")
                        }
                        onNo: {
                            console.log("No changes made to the database...")
                        }

                        Component.onCompleted: visible = false
                    }
                }
            }

            Button {
                id: deleteSouvenirButton
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                text: qsTr("Delete Souvenir")
                onClicked: {
                    //do
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
                                    styleData.role === "Stadium" ||
                                    styleData.role === "Name")
                            {
                                editLoader.sourceComponent = textInputDelegate
                            }
                            else if(styleData.role === "Price")
                            {
                                editLoader.sourceComponent = spinBoxDelegate
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
                                //                                validator: IntValidator { bottom:1; top: 3000}
                                validator: DoubleValidator { bottom:1; top: 5000; decimals: 2}

                                onAccepted:
                                {
                                    if(textInput.acceptableInput)
                                    {
                                        textDelegate.text = text
                                        textDelegate.visible = true
                                        editLoader.visible = false
                                        proxyModel.setData(proxyModel.index(adminInfoTable.currentRow,adminInfoTable.currentColumn,parent),text,2)
                                    }
                                    else
                                    {
                                        textInput.text = textDelegate.text
                                        textDelegate.visible = true
                                        editLoader.visible = false
                                    }
                                }
                                onTextEdited: {
                                    if(!textInput.acceptableInput && textInput.text.length != 0)
                                    {
                                        invalidInput.open()
                                        textInput.undo()
                                        console.log("Invalid Input...")
                                    }
                                }

                                MessageDialog {
                                    id: invalidInput
                                    title: "Warning"
                                    icon: StandardIcon.Warning
                                    text: "Invalid Input. Please enter a double between 1 and 5000"
                                    onAccepted: {
                                        void close()
                                    }
                                    Component.onCompleted: visible = false
                                }
                            }
                        }
                    }

                }

                model: proxyModel

                TableViewColumn{ role: "TeamName" ; title: "Team Name"; width: mainPage.width / 4}
                TableViewColumn{ role: "Stadium" ; title: "Stadium"; width: mainPage.width / 4 }
                TableViewColumn{ role: "Name" ; title: "Name"; width: mainPage.width / 4 }
                TableViewColumn{ role: "Price" ; title: "Price"; width: mainPage.width / 4 }
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
                source: nflSouvenirsModel

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


