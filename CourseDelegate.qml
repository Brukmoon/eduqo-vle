import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Rectangle {
    id: courseDelegate

    color: "white"

    signal courseSelected(var courseName);

    ProgressBar {
        id: downloadProgress

        anchors { left: parent.left; top: parent.top; bottom: parent.bottom}
        orientation: Qt.Vertical
        style: ProgressBarStyle {
            background: Rectangle {
                color: "#222222"
            }
            progress: Rectangle {
                color: "orange"
            }
        }
        value: local ? 1 : 0
        width: 12
        visible: false
    }
    Item {
        anchors { left: downloadProgress.right; right: parent.right; margins: 10 }

        Column {
            Text {
                id: courseTitle

                font.pointSize: 10
                text: model.title
            }
            Text {
                id: author

                text: "by " + model.author
                font.pointSize: 7
            }
            Text {
                id: courseCategory

                text: model.category
            }
        }
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            courseDelegate.ListView.view.currentIndex = index;
            courseSelected(title);
        }
    }
}

