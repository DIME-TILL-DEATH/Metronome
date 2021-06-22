import QtQuick 2.15
import QtQuick.Controls 2.12

Menu{
  id: _menu
  closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

  width: {
      var result = 0;
      var padding = 0;
      for (var i = 0; i < count; ++i) {
          var item = itemAt(i);
          result = Math.max(item.contentItem.implicitWidth, result);
          padding = Math.max(item.padding, padding);
      }
      return result + padding * 2;
  }

  Menu {
      title:  "Add"
      width: parent.width
          MenuItem {
              text:  "before"
          }
          MenuItem {
              text:  "after"
          }
  }
  MenuItem {
      text:  "Copy"
  }
  Menu {
      title:  "Paste"
      width: parent.width
          MenuItem {
              text:  "before"
          }
          MenuItem {
              text:  "after"
          }
  }
  MenuItem {
      text:  "Edit"
  }
  MenuItem {
      text:  "Remove"
  }

  enter: Transition {
          ParallelAnimation {
              NumberAnimation { property: "height"; from: 0; to: _menu.height; duration: 200 }
          }
      }
}
