import QtQuick 2.0

Rectangle {
    id: root

    radius: width/5
    border.width: width/20

    property string note : "Eight"



    NoteImage{
        id: _noteImage

        height: root.height*0.7
        width: root.width*0.7

        overlay.color: "red"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        noteType: note
    }

    signal noteButtonClicked(noteType: string)
    MouseArea{
        id: _mouseArea
        anchors.fill: root
        onClicked: {
            root.noteButtonClicked(note)
        }
    }
}
