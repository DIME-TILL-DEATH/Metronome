import QtQuick 2.0
import QtQuick.Controls 2.15

RoundButton {
    id: control

    property bool isWide: false
    property string displayText: "BTN"

    width: parent.width * 0.5 * 0.975   // может размеры как-то по-другому определять?
    height: isWide ? parent.height * 0.5 * 0.9
                   : parent.height * 0.25 * 0.9


    background: Rectangle{
        border.width: 1
        radius: 20
        gradient: BaseButtonGradient{}

        opacity: enabled ? 1 : 0.3
        border.color: control.down ? "darkgrey" : "white"
    }

    contentItem: Text {
             text: displayText

             font: control.font
             opacity: enabled ? 1.0 : 0.3
             color: control.down ? "#17a81a" : "#21be2b"

             horizontalAlignment: Text.AlignHCenter
             verticalAlignment: Text.AlignVCenter
             elide: Text.ElideRight
    }
}
