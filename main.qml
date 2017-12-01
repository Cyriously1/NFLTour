import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import SortFilterProxyModel 0.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: appWindow
    visible: true
    width: 1250
    height: 850
    title: qsTr("NFL Vacation Planner")

    FontLoader { id: localFont; source: "Pics/BebasNeueRegular.otf" }

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.foreground: Material.Blue

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: teamInfoPage
            //            anchors.fill: appWindow
            ScrollView {
                anchors.fill: parent
                ColumnLayout {
                    id: teamInfoLayout
                    spacing: 2
                    //                    anchors.horizontalCenter: parent.horizontalCenter

                    Image {
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.5
                        source: "Pics/NFL.jpg"
                    }

                    RowLayout {
                        Layout.fillWidth: true


                        Button {
                            id: teamInfoButton
                            Layout.alignment: Qt.AlignCenter
                            Layout.fillWidth: true
                            text: qsTr("Team Information")
                            onClicked: {
                                nflInfoTable.visible ? nflInfoTable.visible = false : nflInfoTable.visible = true
                                nflSearchRect.visible ? nflSearchRect.visible = false : nflSearchRect.visible = true
                                nflInfoCombo.visible ? nflInfoCombo.visible = false : nflInfoCombo.visible = true
                                showSouvButtons.visible ? showSouvButtons.visible = false : showSouvButtons.visible = true
                                if(souvInfoTable.visible) {souvInfoTable.visible = false}
                            }
                        }

                        Button {
                            id: adminLoginButton
                            text: qsTr("Admin")
                            onClicked: {
                                var loginComponent = Qt.createComponent("LoginStuff/main.qml");
                                console.log("Component Status:", loginComponent.status, loginComponent.errorString());
                                var login = loginComponent.createObject(appWindow);
                                appWindow.close();
                                login.show();
                            }
                        }
                    }



                    RowLayout {
                        id: tableManip
                        spacing: 3
                        Layout.alignment: Qt.LeftToRight
                        implicitHeight: 20

                        Rectangle {
                            id: nflSearchRect
                            visible: false
                            border.width: 2
                            border.color: "#2196F3"
                            radius: 5
                            width: appWindow.width / 7
                            height: 20
                            anchors.left: parent.left
//                            anchors.bottom: parent.bottom

                            TextInput {
                                id: nflInfoSearch
                                objectName: "qmlText"
                                signal qmlSignal(string msg)
                                clip: true
                                width: nflSearchRect.width - 5
                                color: "black"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 14
                                onTextEdited: {
                                    nflInfoTable.visible = true
                                    nflInfoTable.model = proxyModel
                                    nflInfoSearch.qmlSignal(text)
                                }
                            }
                        }

                        ComboBox {
                            id: nflInfoCombo
                            visible: false
                            Material.foreground: Material.Blue
                            model: ListModel {
                                ListElement{text: "All"}
                                ListElement{text: "AFC"}
                                ListElement{text: "NFC"}
                            }
                            onCurrentIndexChanged: if(nflInfoCombo.currentIndex == 0)
                                                   {
                                                       proxyModel.source = nflInfoModel
                                                       nflInfoTable.model = proxyModel
                                                   }
                                                   else if(nflInfoCombo.currentIndex == 1)
                                                   {
                                                       proxyModel.source = afcInfoModel
                                                       nflInfoTable.model = proxyModel
                                                   }
                                                   else
                                                   {
                                                       proxyModel.source = nfcInfoModel
                                                       nflInfoTable.model = proxyModel
                                                   }

                        }
                    }

                    TableView {
                        id: nflInfoTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }

                        model: proxyModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                        TableViewColumn{ role: "SeatingCapacity" ; title: "Seating Capacity" }
                        TableViewColumn{ role: "Location" ; title: "Location" }
                        TableViewColumn{ role: "Conference" ; title: "Conference" }
                        TableViewColumn{ role: "SurfaceType" ; title: "Surface Type" }
                        TableViewColumn{ role: "StadiumRoofType" ; title: "Stadium Roof Type" }
                        TableViewColumn{ role: "StarPlayer" ; title: "Star Player" }
                        Component.onCompleted: {
                            nflInfoTable.model = proxyModel
                            nflInfoTable.currentRow = -1

                        }
                        onClicked: {
                            console.log(nflInfoModel.index(nflInfoTable.currentRow,1, parent))
                            console.log(nflInfoModel.data(nflInfoModel.index(nflInfoTable.currentRow,1, parent), "TeamName"))
                        }
                    }
                    SortFilterProxyModel {
                        id: proxyModel
                        source: nflInfoModel

                        sortOrder: nflInfoTable.sortIndicatorOrder
                        sortCaseSensitivity: Qt.CaseInsensitive
                        sortRole: nflInfoTable.getColumn(nflInfoTable.sortIndicatorColumn).role

                        filterString: "*" + nflInfoSearch.text + "*"
                        filterSyntax: SortFilterProxyModel.Wildcard
                        filterCaseSensitivity: Qt.CaseInsensitive

                    }

                    Button {
                        id: showSouvButtons
                        visible: false
                        Layout.fillWidth: true
                        text: qsTr("Show Souvenirs")
                        onClicked: {
                            console.log(nflInfoTable.currentRow)
                            if(nflInfoTable.currentRow == -1)
                            {
                                var popupComponent = Qt.createComponent("Popup.qml");
                                var dialog = popupComponent.createObject(appWindow,{popupType: 1});
                            }
                            else
                            {
                                souvInfoTable.visible ? souvInfoTable.visible = false : souvInfoTable.visible = true

                            }
                        }
                    }
                    TableView {
                        id: souvInfoTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 4
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }

                        model: proxyModel2

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "Stadium" ; title: "Stadium Name" }
                        TableViewColumn{ role: "Name" ; title: "Souvenir" }
                        TableViewColumn{ role: "Price" ; title: "Price" }
                        Component.onCompleted: {
                            souvInfoTable.model = proxyModel2
                        }
                        onClicked: {

                        }
                    }
                    SortFilterProxyModel {
                        id: proxyModel2
                        source: souvenirModel

                        sortOrder: souvInfoTable.sortIndicatorOrder
                        sortCaseSensitivity: Qt.CaseInsensitive
                        sortRole: souvInfoTable.getColumn(souvInfoTable.sortIndicatorColumn).role

                        filterString: "*" + proxyModel.data(proxyModel.index(nflInfoTable.currentRow,1, parent), "TeamName") + "*"
                        filterSyntax: SortFilterProxyModel.Wildcard
                        filterCaseSensitivity: Qt.CaseInsensitive

                    }

                }
            }
        }

        Page {
            id: stadiumsPage
            //            anchors.fill: appWindow
            ScrollView {
                anchors.fill: parent
                ColumnLayout {
                    id: stadiumsInfoLayout
                    spacing: 2
                    //                    anchors.horizontalCenter: parent.horizontalCenter
                    Image {
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.5
                        source: "Pics/Stadiums.jpg"
                    }

                    Button {
                        id: stadiumsButton
                        Layout.alignment: Qt.AlignCenter
                        text: qsTr("Stadiums")
                        onClicked: {
//                            stadiumsInfoTable.visible ? stadiumsInfoTable.visible = false : stadiumsInfoTable.visible = true
                            allStadiumsButton.visible ? allStadiumsButton.visible = false : allStadiumsButton.visible = true
                            openStadiumsButton.visible ? openStadiumsButton.visible = false : openStadiumsButton.visible = true
                            seatingCapStadiumsButton.visible ? seatingCapStadiumsButton.visible = false : seatingCapStadiumsButton.visible = true

                            if(stadiumsInfoTable.visible || openStadiumsTable.visible || seatingCapTable.visible || seatingCapacityLabel.visible)
                            {
                                stadiumsInfoTable.visible = false
                                openStadiumsTable.visible = false
                                seatingCapTable.visible = false
                                seatingCapacityLabel.visible = false
                            }
                        }
                    }

                    RowLayout {
                        id: stadiumsTableManip
                        spacing: 10
                        Layout.alignment: Qt.AlignLeft

                        Button {
                            id: allStadiumsButton
                            visible: false
                            Layout.alignment: Qt.AlignCenter
                            text: qsTr("All Stadiums")
                            onClicked: {
                                stadiumsInfoTable.visible ? stadiumsInfoTable.visible = false : stadiumsInfoTable.visible = true
                                if(openStadiumsTable.visible || seatingCapTable.visible || seatingCapacityLabel.visible)
                                {
                                    openStadiumsTable.visible = false
                                    seatingCapTable.visible = false
                                    seatingCapacityLabel.visible = false
                                }
                            }
                        }

                        Button {
                            id: openStadiumsButton
                            visible: false
                            Layout.alignment: Qt.AlignCenter
                            text: qsTr("Open Stadiums")
                            onClicked: {
                                openStadiumsTable.visible ? openStadiumsTable.visible = false : openStadiumsTable.visible = true
                                if(stadiumsInfoTable.visible || seatingCapTable.visible || seatingCapacityLabel.visible)
                                {
                                    stadiumsInfoTable.visible = false
                                    seatingCapTable.visible = false
                                    seatingCapacityLabel.visible = false
                                }
                            }
                        }

                        Button {
                            id: seatingCapStadiumsButton
                            visible: false
                            Layout.alignment: Qt.AlignCenter
                            text: qsTr("Seating Capacity")
                            onClicked: {
                                seatingCapTable.visible ? seatingCapTable.visible = false : seatingCapTable.visible = true
                                seatingCapacityLabel.visible ? seatingCapacityLabel.visible = false : seatingCapacityLabel.visible = true
                                if(openStadiumsTable.visible || stadiumsInfoTable.visible)
                                {
                                    openStadiumsTable.visible = false
                                    stadiumsInfoTable.visible = false
                                }
                            }
                        }
                    }

                    TableView {
                        id: stadiumsInfoTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }
                        model: stadiumsModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                    }

                    TableView {
                        id: openStadiumsTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }
                        model: openStadiumsModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                    }

                    Label {
                        id: seatingCapacityLabel
                        objectName: "qmlCapacity"
                        Layout.alignment: Qt.AlignCenter
                        visible: false
                        text: qsTr("Total Seating Capacity: ")
                    }
                    TableView {
                        id: seatingCapTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }
                        model: seatingCapModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                        TableViewColumn{ role: "SeatingCapacity" ; title: "Seating Capacity" }
                    }
                }
            }
        }

        Page {
            id: starPlayersPage
            //            anchors.fill: appWindow
            ScrollView {
                anchors.fill: parent
                ColumnLayout {
                    id: starPlayersLayout
                    spacing: 2
                    //                    anchors.horizontalCenter: parent.horizontalCenter
                    Image {
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.5
                        source: "Pics/StarPlayers.jpg"
                    }

                    Button {
                        id: starPlayersButton
                        Layout.alignment: Qt.AlignCenter
                        text: qsTr("Star Players")
                        onClicked: {
                            starPlayersTable.visible ? starPlayersTable.visible = false : starPlayersTable.visible = true
                        }
                    }

                    TableView {
                        id: starPlayersTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        style: TableViewStyle
                        {
                            textColor: "#2196F3"
                            backgroundColor: "#303030"
                            alternateBackgroundColor: "#303030"
                        }
                        model: starPlayersModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StarPlayer" ; title: "Star Player" }
                    }
                }
            }
        }

    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Team Info")
        }
        TabButton {
            text: qsTr("Stadiums")
        }
        TabButton {
            text: qsTr("Star Players")
        }
    }
}
