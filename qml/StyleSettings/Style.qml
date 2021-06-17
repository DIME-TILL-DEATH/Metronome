pragma Singleton
import QtQuick 2.0

QtObject {

    readonly property color textColorMain:      "dodgerblue"
    readonly property color textColorPressed:   "lightblue"

    readonly property color borderColorDefault: "white"
    readonly property color borderColorPressed: "darkgrey"

    readonly property color btnGradientTop: "grey"
    readonly property color btnGradientBtm: "black"

    readonly property color imagesColorOverlay: "dodgerblue"
    readonly property color imagesColorOverlayHighlighted: "lightskyblue"
    readonly property color imagesColorOverlayPlaying: "lightsteelblue"

    readonly property Gradient buttonGradient: Gradient{
        GradientStop{ position: 0.0; color: "grey"}
        GradientStop{ position: 1.0; color: "black"}
    }

    readonly property real defaultOpacity: 1
    readonly property real pressedOpacity: 0.87

    readonly property int defaultOffset: 15
}
