import QtQuick 2.10
import QtQuick.Controls 2.10

Rectangle
{
    id: _layer
    property var model;
    property int level;
    property int maxLevel;
    signal clicked;
    signal backClicked;
    color: "transparent"

    LevelWarningPopup
    {
        id: _popUp
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.width * 0.1
        anchors.leftMargin: parent.height * 0.4
        width: parent.width * 0.5
        height: parent.height * 0.1
        z: 1
        text: "You must pass the next level"
    }

    GridView
    {
        id: _view
        property bool enableArea: true
        anchors.fill: parent
        model: _layer.model
        cellWidth: parent.width / 4
        cellHeight: parent.height / 4

        delegate: Rectangle {
            color: "transparent"
            width: _view.cellWidth - 4
            height: _view.cellHeight - 4
            ImageButton
            {
                id: _img
                property int index : model.index + 1
                property bool isLevelAvailable: index <= _layer.maxLevel
                anchors.left: parent.left
                anchors.leftMargin: width / 6
                width: parent.width * 0.75
                height: parent.height * 0.75
                radiusValue: 8
                source: "picture/level_" + index + ".png"

                Timer
                {
                    id: _timer
                    interval: 2500
                    onTriggered: { _view.enableArea = true; }
                }

                ImageButton
                {
                    visible: !_img.isLevelAvailable
                    width: parent.width
                    height: parent.height
                    radiusValue: parent.radiusValue
                    source: "qrc:/picture/lock.png"
                    onClicked: { _timer.start(); _view.enableArea = false; _popUp.show(); }
                }

                onClicked:
                {
                    if(_img.isLevelAvailable && _view.enableArea) {
                        _layer.level = _img.index;
                        _layer.clicked();
                    }
                }
            }

            Text
            {
                anchors.top: _img.bottom
                anchors.topMargin: (parent.height - _img.height) / 4
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Level " + (model.index + 1)
            }

        }
    }
}