function setNoteFlatIndex(listView)
{
    var notePosition = 0;

    for(var barIndex = 0; barIndex < listView.count; barIndex++)
    {
        for(var noteInBar = 0; noteInBar < listView.itemAtIndex(barIndex).barView.count; noteInBar++)
        {
            _listView.itemAtIndex(barIndex).barView.itemAtIndex(noteInBar).flatteredIndex = notePosition
            notePosition++
        }
    }
}

function getMenuWidthByItems(menu) {
    var result = 0;
    var padding = 0;
    for (var i = 0; i < menu.count; ++i) {
        var item = menu.itemAt(i);
        result = Math.max(item.contentItem.implicitWidth, result);
        padding = Math.max(item.padding, padding);
    }
    return result + padding * 2;
}
