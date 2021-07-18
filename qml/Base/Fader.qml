import QtQuick 2.0
import QtQuick.Controls 2.15
import StyleSettings 1.0

Rectangle{
    signal faderMove(name: string, volume: double)

    width: parent.width/8
    height: parent.height

    color: "transparent"
    border.width: 1
    border.color: Style.borderColorDefault

    Slider{
        id: _slider

        width: parent.width
        height: parent.height*0.7

        orientation: Qt.Vertical

        from: 0
        to: 1
        value: volume

        onMoved: {
            faderMove(name, value)
        }
    }

    Text{
        width: parent.width
        height: parent.height*0.5
        anchors.top: _slider.bottom
        horizontalAlignment: Text.AlignHCenter

        maximumLineCount: 3
        elide: Text.ElideRight
        wrapMode: Text.Wrap

        color: Style.textColorMain

        text: name
    }
}
