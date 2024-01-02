import QtQuick 2.12
import QtQuick.Window 2.12
import QParentQrenCode 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("example")

    property string textcode: textinput.text
    signal setTextCode(string str)

    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        TextInput {
            id: textinput
            Layout.alignment: Qt.AlignCenter
            color: "red"
            Layout.fillWidth: true
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            font.pointSize: 20
            text: "graycatya"
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        Rectangle {
            id : rectroot
            color: "white";
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            ParentQrenCode {
                id: qrencode
                anchors.centerIn: parent
                width: parent.width >= parent.height ? parent.height : parent.width;
                height: parent.width >= parent.height ? parent.height : parent.width;
                qrmode: ParentQrenCode.MODE_8;
                qrlevel: ParentQrenCode.LEVEL_Q;
                casesen: true;
                text: root.textcode;
            }
        }
    }

    onSetTextCode: {
        qrencode.text = str;
    }
}
