pragma Singleton
import QtQuick 2.0

Item{
    property alias interfaceElements: _interfaceIcons
    property alias musicalSymbols: _musicalSymbols

    QtObject{
        id: _interfaceIcons
        readonly property string menuIcon: "qrc:/qml/Resources/InterfaceElements/menu.svg"
    }

    QtObject{
        id: _musicalSymbols
        readonly property string quarterNoteIcon: "qrc:/qml/Resources/MusicalSymbols/quarter-note.svg"
        readonly property string eightNoteIcon: "qrc:/qml/Resources/MusicalSymbols/eighth-note-1.svg"
    }
}
