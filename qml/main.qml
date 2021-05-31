import QtQuick 2.10
import QtQuick.Controls 2.3

import Pages 1.0

ApplicationWindow {
    id: _rootWindow

    width: 1080 * 0.4 // Google pixel 4 width
    height: 2280 * 0.4 // Google pixel 4 height
    visible: true
    title: qsTr("Metronome")

    SwipeView {
        id: _swipeView
        anchors.fill: parent

        MainPage {

        }

        PresetsPage {
        }
    }
}
