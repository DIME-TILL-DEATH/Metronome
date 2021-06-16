import QtQuick 2.0

import StyleSettings 1.0

Gradient{
    property alias _animation : _btnAnim.running
    GradientStop{ position: 0.0; color: "grey"}
    GradientStop{
        position: 1.0
        SequentialAnimation on color{
            id: _btnAnim
            running: false
            ColorAnimation {from: Style.btnGradientBtm; to: Style.btnGradientTop; duration: 50}
            ColorAnimation {from: Style.btnGradientTop; to: Style.btnGradientBtm; duration: 50}
        }
    }
}
