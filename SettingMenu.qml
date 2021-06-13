import QtQuick 2.10
import QtQuick.Controls 2.10

Rectangle
{
    id: _settings
    color: "transparent"
    property string mode;
    property var setter;

    Rectangle
    {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: width * 0.1
        anchors.topMargin: height * 0.2
        width: parent.width *  0.25
        height: parent.height * 0.1
        ComboBox
        {
            anchors.fill: parent
            model: ["Fullscreen", "Window"]
            currentIndex: mode == "full" ? 0 : 1
            onCurrentIndexChanged: { setter.windowMode = currentIndex == 0 ? "full" :  "null" }
        }
    }
}