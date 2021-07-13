import QtQuick 2.10
import QtQuick.Controls 2.3

import Pages 1.0

ApplicationWindow {
    id: _rootWindow

    // for windows debuging
    width: 1080 * 0.4 // Google pixel 4 width
    height: 2280 * 0.4 // Google pixel 4 height

    visible: true
    title: qsTr("Metronome")

    StackView {
        id: _swipeView
        anchors.fill: parent

        property Component presetsPage : PresetsPage{}
        property Item patternEditorPage : PatternEditorPage{}

        initialItem: MainPage {}
    }
}
