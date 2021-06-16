import QtQuick 2.7
import QtQuick.Controls 2.15

import StyleSettings 1.0

SpinBox{
    id: _control

    property int fontsize: 25
    property int indicatorWidth: _control.width/4
    property int delay: 50

    font.pointSize: fontsize

    width: parent.width * 0.5 * 0.975
    height: parent.height * 0.5 * 0.9

    editable: true

    background: Rectangle{
        id: _baseRectangle
        border.width: 1
        radius: 20
        gradient: Style.buttonGradient
        border.color: Style.borderColorDefault
    }

    contentItem: TextInput{
        font.pointSize: fontsize

        text: _control.displayText
        maximumLength: 3

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: Style.textColorMain

        readOnly: !_control.editable
        validator: _control.validator
        inputMethodHints: Qt.ImhDigitsOnly

        onAccepted: {
            parent.focus = false
        }
    }

    up.indicator: BaseControlButton{
         x: parent.width - width
         width: indicatorWidth
         height: parent.height
         fontSize: fontsize
         displayText: "+"

         autoRepeat: true
         autoRepeatDelay: delay*2
         autoRepeatInterval: delay
         onClicked: { value++ }
    }

    down.indicator: BaseControlButton{
         x: 0
         width: indicatorWidth
         height: parent.height
         fontSize: fontsize
         displayText: "-"

         autoRepeat: true
         autoRepeatDelay: delay*2
         autoRepeatInterval: delay
         onClicked: { value-- }
    }
}
