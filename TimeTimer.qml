import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id:windows
    objectName:"windows"
    property int windowWidth : 300;
    property int windowHeight : 420;

    property double dOpacity: 1
    property bool bAlwaysOnTop : false

    opacity: dOpacity

    width: windowWidth
    height: windowHeight

    minimumWidth: windowWidth
    maximumWidth: windowWidth

    minimumHeight: windowHeight
    maximumHeight: windowHeight

    visible: true
    signal emit_Start();
    signal emit_Pause();
    signal emit_Stop();

    Item {
        anchors.fill: parent
        ColumnLayout {
            spacing : 10
            anchors.centerIn : parent
            Button {
                Layout.preferredWidth: 40
                Layout.preferredHeight:30
                Layout.alignment: Qt.AlignRight
                icon.name: "setting"
                icon.source: "qrc:/icon/setting.png"
                onClicked: {
                    timerMgr.showDialog()
                }
            }

            Rectangle {
                border.width: 1
                Layout.preferredWidth: 280
                Layout.preferredHeight:280

                Canvas {
                    id:backgroundCanvas
                    anchors.fill: parent
                    property int centerX: parent.width / 2
                    property int centerY: parent.height / 2
                    property int radius : parent.width / 2 - 39
                    property color backColor : "white"

                    onPaint: {
                        var ctx = backgroundCanvas.getContext("2d");
                        ctx.beginPath()
                        ctx.fillStyle = backColor
                        ctx.arc(centerX, centerY, radius, 0, 2*Math.PI)
                        ctx.fill()
                        ctx.closePath()
                    }
                }

                Canvas {
                    id:timerCanvas
                    objectName:"timeCanvas"
                    anchors.fill: parent
                    property int centerX: parent.width / 2
                    property int centerY: parent.height / 2
                    property int radius : parent.width / 2 - 41

                    property int setMinute: 60
                    property int setSecond: setMinute*60

                    property color timeColor : "red"

                    onPaint: {
                        var time = setSecond;
                        var end = (45-(time/60))*6;
                        var ctx = timerCanvas.getContext("2d");
                        ctx.reset()
                        ctx.beginPath()
                        ctx.fillStyle = timeColor
                        ctx.moveTo(centerX,centerY);
                        ctx.arc(centerX, centerY, radius, (Math.PI/180)*end, (Math.PI/180)*270);
                        ctx.fill()
                        ctx.closePath()
                    }

                    function rePaint() {
                        timerCanvas.requestPaint()
                    }
                }

                Canvas {
                    id:clockNumber
                    anchors.fill: parent

                    property int centerX: parent.width / 2
                    property int centerY: parent.height / 2

                    onPaint: {
                        var ctx = clockNumber.getContext("2d");
                        ctx.font = "20px sans-serif";
                        ctx.textAlign = "center";
                        ctx.textBaseline = "middle";
                        ctx.fillStyle = "black";
                        ctx.beginPath()
                        ctx.translate(centerX,centerY);
                        for ( var number = 1; number <= 12; number++ ){
                            var angle = (Math.PI / 180) * 30;
                            ctx.rotate( angle );
                            ctx.fillText( number, 0, -120);
                        }
                        ctx.closePath()
                    }
                }

                Rectangle {
                    anchors.centerIn: parent
                    opacity: 0.5
                    width : 70
                    height : 40
                    Label {
                        id:remainTime
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 15
                        text : (parseInt(timerCanvas.setSecond / 60)).toString().padStart(2,'0')
                               + ":" + (parseInt(timerCanvas.setSecond % 60)).toString().padStart(2,'0')
                    }
                }
            }

            SpinBox {
                id:spinBox
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight:35
                from: 0
                value: 60
                to: 60
                stepSize: 1
                onValueChanged: {
                    timerCanvas.setMinute = value
                    timerCanvas.requestPaint()
                }
            }

            RowLayout {
                spacing : 10
                Layout.alignment: Qt.AlignHCenter
                Button {
                    Layout.preferredWidth: 40
                    Layout.preferredHeight:30
                    icon.name: "start"
                    icon.source: "qrc:/icon/start.png"
                    onClicked: {
                        windows.emit_Start()
                    }
                }
                Button {
                    Layout.preferredWidth: 40
                    Layout.preferredHeight:30
                    icon.name: "pause"
                    icon.source: "qrc:/icon/pause.png"
                    onClicked: {
                        windows.emit_Pause()
                    }
                }
                Button {
                    Layout.preferredWidth: 40
                    Layout.preferredHeight:30
                    icon.name: "reset"
                    icon.source: "qrc:/icon/reset.png"
                    onClicked: {
                        windows.emit_Stop()
                    }
                }
            }
        }
    }
}
