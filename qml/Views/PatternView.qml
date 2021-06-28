import QtQuick 2.15
import QtQuick.Controls 2.3
import Views 1.0

import StyleSettings 1.0

import "../Functions.js" as Functions

Item {
    id: _rootRectangle

    property var patternModel
    property var selectedItemIndex

    width: parent.width
    height: parent.height*0.3

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
            flickableDirection: Flickable.AutoFlickIfNeeded
            boundsBehavior: Flickable.StopAtBounds

            width: _rootRectangle.width
            height: _rootRectangle.height

            model: patternModel

            delegate: BarView{
                height: _listView.height

                opacity: _barArea.pressed ? 0.5 : 1
                MouseArea{
                    id: _barArea
                    z: 10
                    anchors.fill: parent
                    propagateComposedEvents: true
                    // Два почти одинаковых MouseArea это убого,
                    // но весь функционал по выделению и перетаскиванию работает
                    // пока только так
                    pressAndHoldInterval: Constants.pressAndHoldTime
                    onPressAndHold: {
                        _menuPopUp.mainMenu.popup(mapToItem(_rootRectangle, mouseX, mouseY))
                        selectedItemIndex = index
                        _menuPopUp.state = (selectedItemIndex === -1) ? "onEmptySpace" : "onExistingBar"
                    }
                }
            }

            MouseArea{
                id: _emptySpace
                z: -10
                anchors.fill: parent
                propagateComposedEvents: true

                pressAndHoldInterval: Constants.pressAndHoldTime
                onPressAndHold: {
                    _menuPopUp.mainMenu.popup( mouseX, mouseY)
//                    var itemCoords = mapToItem(_listView, mouseX, mouseY)
//                    console.log(itemCoords)
//                    selectedItemIndex = _listView.indexAt(itemCoords)
//                    console.log(selectedItemIndex)
//                    _menuPopUp.state = (selectedItemIndex === -1) ? "onEmptySpace" : "onExistingBar"
                    if(selectedItemIndex === -1)
                    {
                        _menuPopUp.state = "onEmptySpace"
                        selectedItemIndex = _listView.count
                    }
                    else
                    {
                        _menuPopUp.state = "onExistingBar"
                    }
                }
            }

            //==================================================
            // выделить анимации в отдельный блок/файл, обощить
            remove: Transition {
                ParallelAnimation {
                             NumberAnimation { property: "opacity"; to: 0; duration: 250 }
                             NumberAnimation { property: "width"; to: 0; duration: 250 }
                         }

            }
            removeDisplaced: Transition {
                     NumberAnimation { properties: "x"; duration: Constants.animationTransitionInterval }
            }
            add: Transition {
                ParallelAnimation {
                             NumberAnimation { property: "opacity"; to: 1; duration: Constants.animationTransitionInterval }
//                             NumberAnimation { property: "width"; from: 0; to: width; duration: 250 }
                         }

            }
            addDisplaced: Transition {
                     NumberAnimation { properties: "x"; duration: Constants.animationTransitionInterval }
            }
        }
    }

    PopupEditBarMenu{
      id: _menuPopUp

      addItem.onTriggered: {

          Metronome.addBar(selectedItemIndex)
      }

      removeItem.onTriggered: {
          Metronome.removeBar(selectedItemIndex)
      }
    }

    Component.onCompleted:
    {
        // даёт warning при старте, тк компонент-наследник ещё не создан
        Functions.setNoteFlatIndex(_listView)
    }

    Connections{
        target: Metronome
        function onSetTimerIntervals()
        {
            Functions.setNoteFlatIndex(_listView)

        }
    }
}

