import QtQuick 2.15
import QtQuick.Controls 2.12

import "../../Functions.js" as Functions


Item{
    property alias mainMenu:    _menu
    property alias addItem:     _itemAdd
    property alias copyItem:    _itemCopy
    property alias pasteItem:   _itemPaste
    property alias removeItem:  _itemRemove
    Menu{
      id: _menu
      closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape


      width: Functions.getMenuWidthByItems(_menu)

      MenuItem {
          id: _itemAdd
          text:  "Add"
      }
      MenuItem {
          id: _itemCopy
          text:  "Copy"
      }
      MenuItem {
          id: _itemPaste
          text:  "Paste"
      }
      MenuItem {
          id: _itemEdit
          text:  "Edit"
      }
      MenuItem {
          id: _itemRemove
          text:  "Remove"
      }

      //-------------------------------------------------------------------------------------------
      enter: Transition {
              ParallelAnimation {
                  NumberAnimation { property: "height"; from: 0; to: _menu.height; duration: 200 }
              }
      }
    }

    states:[
      State {
          name: "onExistingBar"
          PropertyChanges {target: _itemCopy; enabled: true}
          PropertyChanges {target: _itemRemove; enabled: true}
      },
      State {
          name: "onEmptySpace"
          PropertyChanges {target: _itemCopy; enabled: false}
          PropertyChanges {target: _itemRemove; enabled: false}

      }
    ]
}

