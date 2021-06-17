import QtQuick 2.10
import QtQuick.Controls 2.3

import Views 1.0
import Base 1.0
import StyleSettings 1.0
import ResourceProvider 1.0

Page {
    id: _page

    background: Rectangle{
        z: -100
        gradient: Style.buttonGradient
    }

    header: Rectangle {
        id: _headerRectangle

        height: parent.height / 15

        radius: 5

        border.color: "white"
        border.width: 1

        gradient: Gradient{
            GradientStop{ position: 0.0; color: "skyblue"}
            GradientStop{ position: 1.0; color: "royalblue"}
        }

        ToolButton{
            anchors.left: parent.left
            width: parent.width / 10
            height: parent.height


            icon.source: Resources.interfaceElements.menuIcon
            icon.height: parent.height * 0.4
            icon.width: parent.height * 0.4

            onClicked: {
                // working, but disabled for future use
//                 _page.SwipeView.view.incrementCurrentIndex()
            }
        }

        Text {
            id: _presetName

            anchors.centerIn: _headerRectangle
            text: "Base page"

            font.pixelSize: Qt.application.font.pixelSize * 2
        }
    }

    Column{
        anchors.fill: parent

        PatternView{
            id: _patternview1
            patternModel: mainPattern
        }

        PatternView{
            id: _patternview2
            patternModel: secondaryPattern
        }

        MetronomeButtonsView{
            id: _metronomeButtonsView

        }
    }
}
