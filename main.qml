import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    id: appWindow
    visible: true
    width: 1250
    height: 850
    title: qsTr("Hello World")

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.foreground: Material.Blue

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: teamInfoPage
            anchors.fill: appWindow
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

                    Button {
                        id: teamInfoButton
                        Layout.alignment: Qt.AlignCenter
                        text: qsTr("Team Information")
                        onClicked: {
                            nflInfoTable.visible ? nflInfoTable.visible = false : nflInfoTable.visible = true
                            nflSearchRect.visible ? nflSearchRect.visible = false : nflSearchRect.visible = true
                            nflInfoCombo.visible ? nflInfoCombo.visible = false : nflInfoCombo.visible = true
                        }
                    }

                    RowLayout {
                        id: tableManip
                        spacing: 3
                        Layout.alignment: Qt.LeftToRight

                        Rectangle {
                            id: nflSearchRect
                            visible: false
                            border.width: 2
                            border.color: "teal"
                            radius: 5
                            width: appWindow.width / 7
                            height: 36
                            anchors.left: parent.left

                            TextInput {
                                id: nflInfoSearch
                                clip: true
                                width: nflSearchRect.width - 5
                                color: "black"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter

                                font.pixelSize: 22
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

                        }
                    }

                    TableView {
                        id: nflInfoTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
                        model: nflInfoModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                        TableViewColumn{ role: "SeatingCapacity" ; title: "Seating Capacity" }
                        TableViewColumn{ role: "Location" ; title: "Location" }
                        TableViewColumn{ role: "Conference" ; title: "Conference" }
                        TableViewColumn{ role: "SurfaceType" ; title: "Surface Type" }
                        TableViewColumn{ role: "StadiumRoofType" ; title: "Stadium Roof Type" }
                        TableViewColumn{ role: "StarPlayer" ; title: "Star Player" }
                    }
                }
            }
        }

        Page {
            id: stadiumsPage
            anchors.fill: appWindow
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
                            stadiumsInfoTable.visible ? stadiumsInfoTable.visible = false : stadiumsInfoTable.visible = true

                            allStadiumsButton.visible ? allStadiumsButton.visible = false : allStadiumsButton.visible = true
                            openStadiumsButton.visible ? openStadiumsButton.visible = false : openStadiumsButton.visible = true
                            seatingCapStadiumsButton.visible ? seatingCapStadiumsButton.visible = false : seatingCapStadiumsButton.visible = true
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
                                if(openStadiumsTable.visible || seatingCapTable.visible)
                                {
                                    openStadiumsTable.visible = false
                                    seatingCapTable.visible = false
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
                                if(stadiumsInfoTable.visible || seatingCapTable.visible)
                                {
                                    stadiumsInfoTable.visible = false
                                    seatingCapTable.visible = false
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
                        model: openStadiumsModel

                        TableViewColumn{ role: "TeamName" ; title: "Team Name" }
                        TableViewColumn{ role: "StadiumName" ; title: "Stadium Name" }
                    }

                    TableView {
                        id: seatingCapTable
                        visible: false
                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredWidth: appWindow.width
                        Layout.preferredHeight: appWindow.height / 1.25
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
            anchors.fill: appWindow
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
