import QtQuick 2.10
import QtQuick.Controls 2.10

Rectangle
{
    property string text: "Text"
    property var radius;
    signal closeClick;
    signal nextClick;
    color: "transparent"

    Rectangle
    {
        anchors.fill: parent
        opacity: 0.95
        color: "grey"
        radius: parent.radius
    }

    Text
    {
        id: _txt
        width: parent.width
        height: parent.height / 2
        text: parent.text
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: width * 0.45
        anchors.topMargin: height * 0.2
    }

    Button
    {
        id: _exit
        anchors.left: parent.left
        anchors.leftMargin: width / 4
        anchors.top: _txt.bottom
        width: parent.width / 3
        height: parent.height / 6
        text: "Close"
        onClicked: { closeClick(); }
    }

    Button
    {
        id: _next
        anchors.left: _exit.right
        anchors.leftMargin: width / 2
        anchors.top: _txt.bottom
        width: parent.width / 3
        height: parent.height / 6
        text: "Next"
        onClicked: { nextClick(); }
    }
}
