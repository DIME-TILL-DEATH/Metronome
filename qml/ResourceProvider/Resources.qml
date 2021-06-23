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
        readonly property string wholeNoteIcon: "qrc:/qml/Resources/MusicalSymbols/whole.svg"
        readonly property string halfNoteIcon: "qrc:/qml/Resources/MusicalSymbols/half-note.svg"
        readonly property string quarterNoteIcon: "qrc:/qml/Resources/MusicalSymbols/quarter-note.svg"
        readonly property string eightNoteIcon: "qrc:/qml/Resources/MusicalSymbols/eighth-note.svg"
        readonly property string sixteenthNoteIcon: "qrc:/qml/Resources/MusicalSymbols/sixteenth-note.svg"
        readonly property string thirtysecondNoteIcon: "qrc:/qml/Resources/MusicalSymbols/thirty-second-note.svg"
    }
}
