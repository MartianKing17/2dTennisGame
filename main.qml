import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import gameFunc 1.0

Window
{
    id: mainWindow
    visible: true
    width: 600
    height: 450


    property int buttonNum: 4
    property int margleft: buttonWidth/10
    property int buttonWidth: mainWindow.width/3.5
    property int buttonHeight: mainWindow.height/9
    property int margleTop: mainWindow.height/40

    function f()
    {
        var val = buttonHeight*buttonNum + margleTop*(buttonNum-1)
        val = mainWindow.height - val
        val /= 2
        val = mainWindow.height/val
        return val
    }

    Image
    {
        id: background
        anchors.fill: parent
        source: "arkanoid_background.png"
    }

    Game
    {
      id:game
    }

    Button
    {
        id:singlePlayButton
        text: qsTr("Single-Play")
        onClicked: {
            mainWindow.hide()
            if(game.startSinglePlay() === true)
            {
                mainWindow.show()
            }
        }

        width: buttonWidth
        height: buttonHeight
        anchors.top: parent.top
        anchors.topMargin: parent.height/f()
        anchors.left: parent.left
        anchors.leftMargin: margleft

        contentItem: Text {

            text: parent.text

            font: parent.font

            opacity: enabled ? 1.0 : 0.3

            color: parent.down ? "#FA8072" : "#000000"

            horizontalAlignment: Text.AlignHCenter

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

        }


        background: Rectangle {

            implicitWidth: buttonWidth

            implicitHeight: buttonHeight

            opacity: 0.5

            border.color: parent.down ? "#FA8072" : "#000000"

            border.width: 1

            radius: (buttonWidth - buttonHeight)/16
        }

    }

    Button
    {
        id:multiPlayButton
        text: "Muiti-Play"
        onClicked:
        {
            mainWindow.hide()

            if (game.startMultiPlay() === true)
            {
                mainWindow.show()
            }
        }

        width: buttonWidth
        height: buttonHeight
        anchors.top: singlePlayButton.bottom
        anchors.topMargin: margleTop
        anchors.left: parent.left
        anchors.leftMargin:  margleft

        contentItem: Text {

            text: parent.text

            font: parent.font

            opacity: enabled ? 1.0 : 0.3

            color: parent.down ? "#FA8072" : "#000000"

            horizontalAlignment: Text.AlignHCenter

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

        }


        background: Rectangle {

            implicitWidth: buttonWidth

            implicitHeight: buttonHeight

            opacity: 0.5

            border.color: parent.down ? "#FA8072" : "#000000"

            border.width: 1

            radius: (buttonWidth - buttonHeight)/16
        }

    }

    Button
    {
        id:achievementButton
        text: "Achievement"
        onClicked: gameEvent.achievementPage()

        width: buttonWidth
        height: buttonHeight
        anchors.top: multiPlayButton.bottom
        anchors.topMargin: margleTop
        anchors.left: parent.left
        anchors.leftMargin:  margleft

        contentItem: Text {

            text: parent.text

            font: parent.font

            opacity: enabled ? 1.0 : 0.3

            color: parent.down ? "#FA8072" : "#000000"

            horizontalAlignment: Text.AlignHCenter

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

        }


        background: Rectangle {

            implicitWidth: buttonWidth

            implicitHeight: buttonHeight

            opacity: 0.5

            border.color: parent.down ? "#FA8072" : "#000000"

            border.width: 1

            radius: (buttonWidth - buttonHeight)/16
        }

    }

    Button
    {
        id:settingButton
        text: "Setting"
        onClicked: gameEvent.settingMenu()

        width: buttonWidth
        height: buttonHeight
        anchors.top: achievementButton.bottom
        anchors.topMargin: margleTop
        anchors.left: parent.left
        anchors.leftMargin:  margleft

        contentItem: Text {

            text: parent.text

            font: parent.font

            opacity: enabled ? 1.0 : 0.3

            color: parent.down ? "#FA8072" : "#000000"

            horizontalAlignment: Text.AlignHCenter

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

        }


        background: Rectangle {

            implicitWidth: buttonWidth

            implicitHeight: buttonHeight

            opacity: 0.5

            border.color: parent.down ? "#FA8072" : "#000000"

            border.width: 1

            radius: (buttonWidth - buttonHeight)/16
        }

    }

    title: qsTr("Arkanoid")
}
