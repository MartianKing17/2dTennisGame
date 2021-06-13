import QtQuick 2.10
import QtQuick.Controls 2.10

Rectangle
{
    id: _popUp
    property string text;
    visible: false
    color: "transparent"

    function show()
    {
        _popUp.visible = true;
        _timer.start();
    }

    function hide()
    {
        _popUp.visible = false;
    }

    Timer
    {
        id: _timer
        interval: 2500
        onTriggered: { parent.hide(); }
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#AAAAAA"
        opacity: 0.8
        radius: width / 16
    }

    Text
    {
        anchors.centerIn: parent
        text: _popUp.text
    }
}
