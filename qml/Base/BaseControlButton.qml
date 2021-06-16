import QtQuick 2.15
import QtQuick.Controls 2.15

import StyleSettings 1.0
import Base 1.0

RoundButton {
    id: control

    property bool isWide: false
    property string displayText: "BTN"
    property int fontSize: 14

    width: parent.width * 0.5 * 0.975   // может размеры как-то по-другому определять?
    height: isWide ? parent.height * 0.5 * 0.9
                   : parent.height * 0.25 * 0.9

    background: Rectangle{
        border.width: 1
        radius: 20
        gradient: AnimatedGradient{id: _gradient}
        border.color: control.down ? Style.borderColorPressed
                                   : Style.borderColorDefault
    }

    onClicked: {
        _gradient._animation = true
    }

    contentItem: Text{
        font.pointSize: fontSize

        text: displayText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        color: control.down ? Style.textColorPressed
                            : Style.textColorMain
    }
}
