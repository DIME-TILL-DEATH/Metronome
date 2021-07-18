import QtQuick 2.10
import QtQuick.Controls 2.3

import Base 1.0
import StyleSettings 1.0

Item{
    id: _faders

    width: parent.width
    height: parent.height - _patternview1.height -
            _patternview2.height - _metronomeButtonsView.height -
            _headerRectangle.height

    Row{
        anchors.fill: parent

        spacing: width/50
        padding: width/50

        Component.onCompleted: {
            for(var name in Metronome.eventVolumes)
            {
                _fadersList.append({"name" : name, "volume": Metronome.eventVolumes[name]})
            }
        }

        ListModel{
            id: _fadersList
        }

        Repeater{

            model: _fadersList

            delegate: Fader{
                onFaderMove:{
                    var newVolumes = Metronome.eventVolumes
                    newVolumes[name] = volume
                    Metronome.eventVolumes = newVolumes
                }
            }
        }
    }
}
