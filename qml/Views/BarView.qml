import QtQuick 2.10
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import StyleSettings 1.0

Item {
    id: _root

    property alias barView: _barView
    property int noteWidth: 50

    width: _barView.count * noteWidth

    Text{
        x: 5
        color: Style.textColorMain
        font.pointSize: 10
        text: barNumber
    }

    // как вариант:
    // определять что делегат последний и только тогда её показывать
    // по нажатию автоматически вызывать диалог Add (или Add+Paste)
//        RoundButton{
//            x: parent.width+40
    //        y: parent.height/2
//            z: -10
//        }

    ListView{
        id: _barView

        orientation: ListView.Horizontal
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        width: _root.width
        height: _root.height


        model: barModel
//        model: _model

        delegate: NoteView{
            id: _note
            width: noteWidth
            height: _barView.height
        }

        header: Rectangle{
            id: _barLineStart
            color: Style.imagesColorOverlay
            width: 2
            height: parent.height / 2
        }
        footer: Rectangle{
            id: _barLineStop
            color: Style.imagesColorOverlay
            width: 2
            height: parent.height / 2
        }
    }

    ListModel{
        id: _model
    }

    Component.onCompleted: {
        var noteIndex
        for(noteIndex=0; noteIndex < bar.notePatternSize(); noteIndex++)
        {
            _model.append({"note": bar.noteQMLAt(noteIndex)})
        }
    }
}
