import QtQuick 2.10
import QtQuick.Controls 2.3
//import QtQuick.Extras 1.4
import QtQuick.Layouts 1.15

import Base 1.0

import Views 1.0
import StyleSettings 1.0
import ResourceProvider 1.0

Page {
    id: _page

    background: Rectangle{
        id: _rootRectangle
        z: -100
        gradient: Style.buttonGradient
    }

    header: Rectangle {
        id: _headerRectangle

        height: parent.height / 15
        radius: 5
        border { color: "white"; width: 1}

        gradient: Gradient{
            GradientStop{ position: 0.0; color: "skyblue"}
            GradientStop{ position: 1.0; color: "royalblue"}
        }

        ToolButton{
            anchors.left: parent.left
            width: parent.width / 10; height: parent.height

            icon {
                source: Resources.interfaceElements.menuIcon
                height: parent.height * 0.4
                width: parent.height * 0.4
            }

            onClicked: {
                _swipeView.pop()
            }
        }

        Text {
            id: _presetName

            anchors.centerIn: _headerRectangle
            text: "Pattern editor page"

            font.pixelSize: Qt.application.font.pixelSize * 2
        }
    }
    //-----------------------------------------------------------
    property int noteWidth: 50
    property int selectedNote: 0
    property var bar : (PatternEditor !== null) ? PatternEditor.createBar() : 0
    property int editingBarIndex: 0

    Component.onCompleted: {
        for(var noteIndex=0; noteIndex < bar.notesCount(); noteIndex++)
        {
            _model.append({"note": bar.noteQMLAt(noteIndex)})
        }
    }

    Column{
        anchors.fill: parent

        topPadding: parent.height/40
        spacing: parent.height/40

        BarView {
            id: _newBarView

            width: _page.width*0.8; height: noteWidth*2
            anchors.horizontalCenter: parent.horizontalCenter

            barLabel: "new"

            focus: true

            barView.model: ListModel { id: _model }
            barView.highlight: HighlightRectangle{}

            onNoteDelegateClicked: { barView.currentIndex = noteIndex }
        }

        Tumbler{
            id: _tumbler

            anchors.horizontalCenter: parent.horizontalCenter

            height: _page.background.height/3; width: _page.width*0.8
            padding: _backgroundRectangle.border.width*3

            visibleItemCount: 3
            wrap: false

            background: Rectangle{
                id: _backgroundRectangle

                color: "transparent"
                border { width: 3; color: Style.borderColorPressed }
                radius: parent.width/20
            }

            model: mainPattern
            delegate: BarView{
                property int margin : _backgroundRectangle.border.width*2

                barView.highlight: HighlightRectangle {visible: (index === _tumbler.currentIndex) ? true : false}

                barView {focus: true; highlightFollowsCurrentItem: true}
                opacity: 1.0 - Math.abs(Tumbler.displacement) / (_tumbler.visibleItemCount / 2)

                onNoteDelegateClicked: {
                    _tumbler.currentIndex = index
                    barView.currentIndex = noteIndex
                }
            }
        }

        NoteButtonView{
            anchors.horizontalCenter: parent.horizontalCenter

            onNoteButtonInGridClicked:
            {
                console.log(Metronome.eventVolumes["Click"])

                var prevSelection =_newBarView.barView.currentIndex
                bar.addNote(prevSelection+1, PatternEditor.noteByName(noteType))
                // переделать создание модели в QML для нот
                // на property хранящее массив нот в такте,
                // или функцию возвращающую этот массив
                // или на роль
                _model.clear()
                for(var noteIndex=0; noteIndex < bar.notesCount(); noteIndex++)
                {
                    _model.append({"note": bar.noteQMLAt(noteIndex)})
                }
                _newBarView.barView.currentIndex = prevSelection+1
            }
        }

        Button{
            id: _exitButton

            anchors.horizontalCenter: parent.horizontalCenter

            text: "exit"

            onClicked: {
                Metronome.addBar(editingBarIndex, 0, bar)
                _swipeView.pop()
            }
        }
        }
}
