import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import Game 1.0

Window
{
    id: _window
    visible: true
    width: 800
    height: 640
    title: qsTr("Arkanoid")

    Game
    {
        id: _game
        property int maximumLevel: getLevel();
        onMaxLevelChanged:
        {
            maximumLevel = _game.getLevel();
            _msg.text = "You win! Level " + _game.level + " was enable!";
            _msg.visible = true;
        }
    }

    Image
    {
        id: background
        anchors.fill: parent
        source: "picture/arkanoid_background.png"
    }

    Message
    {
        id: _msg
        z: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: parent.height / 4
        anchors.leftMargin: parent.width / 4
        width: parent.width / 2
        height: parent.height / 2
        visible: false
        radius: 32
        onCloseClick: { _msg.visible = false; }
        onNextClick:
        {
            _picker.level = _picker.level + 1;
            _msg.visible = false;
            _picker.clicked();
        }
    }

    SettingMenu
    {
        id: _setting
        visible: false
        anchors.left: parent.left
        anchors.top: _bar.bottom
        width: parent.width
        height: parent.height
        setter: _game
        mode: _game.getWindowMode()
    }

    ControlBar
    {
        id: _bar
        visible: _setting.visible || _picker.visible
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: parent.height * 0.1
        onClicked:
        {
            if (_setting.visible) {
                _menu.visible = true;
                _setting.visible = false;
            }

            if (_picker.visible) {
                _picker.visible = false;
                _menu.visible = true;
            }
        }
    }

    StartMenu
    {
        id: _menu
        visible: true
        anchors.fill: parent

        onStartClicked:
        {
            _picker.visible = true;
            _menu.visible = false;
        }

        onSettingClicked:
        {
            _setting.visible = true;
            _menu.visible = false;
        }
    }

    LevelMenu
    {
        id: _picker
        visible: false
        anchors.top: _bar.bottom
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        model: 32
        maxLevel: _game.maximumLevel

        onClicked:
        {
           _game.level = _picker.level;
           _window.hide();

           if (_game.startSinglePlay() == 0) {
               _window.show();
           } else {
               _window.close();
           }
       }
    }

    onClosing: { _game.writeData(); }
}
