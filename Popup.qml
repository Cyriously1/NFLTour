import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2



MessageDialog {
    id: messageDialog
    title: "Warning"
    icon: StandardIcon.Warning
    text: "Please select a Team from the table."
    onAccepted: {
        void close()
    }
    Component.onCompleted: visible = true
}

