import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Window {
    id : settingDlg
    property int winWidth : 200
    property int winHeight : 240

    property color backColor : "black"
    property double dOpacity: 1
    property bool bAlwaysOnTop : false

    width: winWidth
    height: winHeight

    minimumWidth: winWidth
    minimumHeight: winHeight

    maximumWidth: winWidth
    maximumHeight: winHeight

    signal emit_changeColor(color back);
    signal emit_changeOpcaity(double dOpacity);
    signal emit_changeAlwaysOnTop(bool bChecked);

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent
        columnSpacing: 0
        columns : 2

        Layout.alignment: Qt.AlignCenter

        property int nWidth : 50
        property int nHeight : 30

        Label {
            Layout.preferredWidth: parent.nWidth
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            text : "타이머 색상"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            id : colorBtn
            Layout.preferredWidth: parent.nWidth
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignCenter
            background: Rectangle {
                color: backColor
            }
            onClicked: {
                colorDialog.open()
            }
        }

        Label {
            text : "상단 고정"
            Layout.preferredWidth: parent.nWidth
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Switch {
            Layout.preferredWidth: parent.nWidth
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignCenter
            checked: bAlwaysOnTop
            onCheckedChanged: {
                settingDlg.emit_changeAlwaysOnTop(checked)
            }
        }

        Label {
            text : "투명도"
            Layout.preferredWidth: parent.nWidth
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Slider {
            from:1
            to:0
            stepSize: 0.1
            value : dOpacity
            Layout.preferredWidth: parent.nWidth + 20
            Layout.preferredHeight: parent.nHeight
            Layout.alignment: Qt.AlignCenter

            onValueChanged: {
                settingDlg.emit_changeOpcaity(value)
            }
        }
    }

    ColorDialog {
        id:colorDialog
        modality: Qt.WindowModal
        title:"Timer Color"
        color:backColor
        onAccepted: {
            backColor = colorDialog.color
            settingDlg.emit_changeColor(backColor)
        }
    }
}
