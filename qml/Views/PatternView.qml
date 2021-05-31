import QtQuick 2.15
import QtQuick.Controls 2.3

// Имя зарегистрированого в C++ модуля
import Pattern 1.0

Item {
    id: _rootRectangle

    width: parent.width
    height: parent.height*0.3

    MouseArea{
        id: _delegateArea
        anchors.fill: _rootRectangle
    }


    Column{
        id: column
        spacing: 5
        anchors.fill: parent

        clip: true

        Label{
            id: _mainLabel
            height: parent * 0.2
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter

            font.pixelSize: _rootRectangle.height*0.1
            text: "Label1"
        }

        Label{
            id: _auxLabel
            height: parent * 0.1
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter

            font.pixelSize: _rootRectangle.height*0.05
            text: "Label2"
        }

        ListView{
            id: _listView
            orientation: ListView.Horizontal
            width: parent.width
            height: parent.height

            model: MusicalPatternModel{}

            delegate: PatternDelegate{
                width: 50
                height: parent.height
            }
        }
    }
}
