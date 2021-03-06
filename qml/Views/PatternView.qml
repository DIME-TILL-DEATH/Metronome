import QtQuick 2.15
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import Base 1.0
import Views 1.0
import StyleSettings 1.0

import "../Functions.js" as Functions

Item {
    id: _rootRectangle

    property var patternModel
    property var selectedItemIndex
    property var clickedItemIndex

    property alias patternViewer : _listView

    width: parent.width

    Column{
        id: column

        spacing: height/50
        padding: height/50

        anchors.fill: parent
        topPadding: 10

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
            height: _rootRectangle.height*0.5

            model: patternModel

            currentIndex: Metronome.activeBarIndex
            highlight: Rectangle{
                color: "transparent"
                radius: 10
                z: -10
                border{
                    width: 2
                    color: Style.imagesColorOverlayHighlighted
                }
            }

            delegate: BarView{
                height: _listView.height



//                opacity: _barArea.pressed  ? 0.5 : 1
//                MouseArea{
//                    id: _barArea

////                    z: -20
//                    anchors.fill: parent
//                    propagateComposedEvents: true
//                }
            }

            MouseArea{
                id: _listViewArea

                z: -5
                anchors.fill: parent
                propagateComposedEvents: true

                pressAndHoldInterval: Constants.pressAndHoldTime

                onPressAndHold: {
                    _menuPopUp.mainMenu.popup(mouseX, mouseY)

                    console.log(mapToGlobal(mouseX, mouseY))
                    if(selectedItemIndex === -1)
                    {
                        _menuPopUp.state = "onEmptySpace"
                        selectedItemIndex = _listView.count
                    }
                    else
                    {
                        _menuPopUp.state = "onExistingBar"
                        selectedItemIndex = _listView.indexAt(mouseX+_listView.contentX, mouseY)
                    }
                }
            }

            //==================================================
            // ???????????????? ???????????????? ?? ?????????????????? ????????/????????, ??????????????
            remove: Transition {
                ParallelAnimation {
                             NumberAnimation { property: "opacity"; to: 0; duration: Constants.animationTransitionInterval  }
                             NumberAnimation { property: "width"; to: 0; duration: Constants.animationTransitionInterval  }
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
          _swipeView.patternEditorPage.editingBarIndex = selectedItemIndex
          _swipeView.push(_swipeView.patternEditorPage)
      }

      removeItem.onTriggered: {
          Metronome.removeBar(selectedItemIndex)
      }
    }

//    Connections{
//        target: Metronome

//        function onSetTimerIntervals()
//        {
//            Functions.setNoteFlatIndex(_listView)
//        }
//    }
}

