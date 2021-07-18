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

function listProperty(item)
{
    for (var p in item)
    console.log(p + ": " + item[p]);
}
