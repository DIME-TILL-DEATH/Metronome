import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    color: "lightsteelblue"; radius: 10

    SequentialAnimation on opacity{
        loops: Animation.Infinite
        NumberAnimation{from: 1; to: 0.5; duration: 750}
        NumberAnimation{from: 0.5; to: 1; duration: 750}
        }
}
