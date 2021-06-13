import QtQuick 2.10

Rectangle
{
    id: _bar
    color: "transparent"
    signal clicked;

    Rectangle
    {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "#AAAAAA"
        opacity: 0.8
    }

    ImageButton
    {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: height * 0.3
        width: parent.width * 0.15
        height: parent.height * 0.6
        source: "picture/Arrow.png"
        radiusValue: 16
        onClicked: { parent.clicked(); }
    }
}