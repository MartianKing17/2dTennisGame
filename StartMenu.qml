import QtQuick 2.10
import QtQuick.Controls 2.10

Rectangle
{
    signal startClicked;
    signal settingClicked;

    property int buttonNum: 2
    property int margleft: buttonWidth / 10
    property int buttonWidth: width / 3.5
    property int buttonHeight: height / 9
    color: "transparent"

    function marginTop(parent, num) {
        return parent.height / num;
    }

    Button
    {
            id: singlePlayButton
            text: qsTr("Single Play")
            width: buttonWidth
            height: buttonHeight
            anchors.top: parent.top
            anchors.topMargin: marginTop(parent, 40)
            anchors.left: parent.left
            anchors.leftMargin: margleft

            contentItem: Text
            {

                text: parent.text

                font: parent.font

                opacity: enabled ? 1.0 : 0.3

                color: parent.down ? "#FA8072" : "#000000"

                horizontalAlignment: Text.AlignHCenter

                verticalAlignment: Text.AlignVCenter

                elide: Text.ElideRight
            }

            background: Rectangle
            {

                implicitWidth: buttonWidth

                implicitHeight: buttonHeight

                opacity: 0.5

                border.color: parent.down ? "#FA8072" : "#000000"

                border.width: 1

                radius: (buttonWidth - buttonHeight) / 16
            }

            onClicked: { startClicked(); }
        }

        Button
        {
            id: settingButton
            text: "Setting"
            width: buttonWidth
            height: buttonHeight
            anchors.top: singlePlayButton.bottom
            anchors.topMargin: marginTop(singlePlayButton, 10)
            anchors.left: parent.left
            anchors.leftMargin:  margleft

            contentItem: Text
            {

                text: parent.text

                font: parent.font

                opacity: enabled ? 1.0 : 0.3

                color: parent.down ? "#FA8072" : "#000000"

                horizontalAlignment: Text.AlignHCenter

                verticalAlignment: Text.AlignVCenter

                elide: Text.ElideRight

            }

            background: Rectangle
            {

                implicitWidth: buttonWidth

                implicitHeight: buttonHeight

                opacity: 0.5

                border.color: parent.down ? "#FA8072" : "#000000"

                border.width: 1

                radius: (buttonWidth - buttonHeight)/16
            }

            onClicked: { settingClicked(); }
        }
}