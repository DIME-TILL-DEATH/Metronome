import QtQuick 2.10
import QtQuick.Layouts 1.15

import MusicalTypesModule 1.0
import StyleSettings 1.0

Item {
    id: _root

    width: _listView.count * 50
    height: parent.height

    Rectangle{
        id: _barLine
        color: Style.imagesColorOverlay
        x:0; y:0
        width: 2
        height: parent.height / 2
    }
    Text{
        x: _barLine.width + 5
        color: Style.textColorMain
        font.pointSize: 10
        text: barNumber
    }

    ListView{
        id: _listView

        orientation: ListView.Horizontal
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        width: _root.width
        height: _root.height


        model: barModel

        delegate: BarDelegate{
            id: _note
            width: 50
            height: _listView.height
        }
    }
}
