import QtQuick 2.10
import QtQuick.Controls 2.3

import Views 1.0
import Base 1.0
import StyleSettings 1.0
import ResourceProvider 1.0

import "../Functions.js" as Functions

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

        border{
            color: "white"
            width: 1
        }

        gradient: Gradient{
            GradientStop{ position: 0.0; color: "skyblue"}
            GradientStop{ position: 1.0; color: "royalblue"}
        }

        ToolButton{
            anchors.left: parent.left
            width: parent.width / 10
            height: parent.height

            icon{
                source: Resources.interfaceElements.menuIcon
                height: parent.height * 0.4
                width: parent.height * 0.4
            }

            onClicked: { _swipeView.pop() }
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
            patternModel: Metronome.pattern(1)
        }

        MetronomeButtonsView{
            id: _metronomeButtonsView

        }
    }

    Component.onCompleted:
    {
        // даёт warning при старте, тк компонент-наследник ещё не создан
        Functions.setNoteFlatIndex(_patternview1.patternViewer)
        Functions.setNoteFlatIndex(_patternview2.patternViewer)
    }
}
