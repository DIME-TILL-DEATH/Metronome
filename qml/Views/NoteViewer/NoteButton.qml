import QtQuick 2.0

Rectangle {
    id: root

    property string note : "Eight"

    signal noteButtonClicked(noteType: string)

    radius: width/5
    border.width: width/20

    NoteImage{
        id: _noteImage

        height: root.height*0.7; width: root.width*0.7

        overlay.color: "red"

        anchors{ horizontalCenter: parent.horizontalCenter
                 verticalCenter: parent.verticalCenter
        }

        noteType: note
    }

    MouseArea{
        id: _mouseArea

        anchors.fill: root
        onClicked: {
            root.noteButtonClicked(note)
        }
    }
}
