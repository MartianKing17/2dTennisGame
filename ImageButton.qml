import QtQuick 2.10
import QtQuick.Controls 2.10
import QtGraphicalEffects 1.10

Image
{
    id: _img
    signal clicked;
    property bool isAreaEnable: true
    property int radiusValue;
    layer.enabled: true
    layer.effect: OpacityMask
    {
            maskSource: Item
            {
                width: _img.width
                height: _img.height
                Rectangle
                {
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    radius: width / radiusValue
                }
            }
    }

    MouseArea
    {
        visible: parent.isAreaEnable
        anchors.fill: parent
        onClicked: { parent.clicked(); }
    }
}