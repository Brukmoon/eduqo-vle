import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ListView {
    id: courseNav

    boundsBehavior: Flickable.StopAtBounds
    header: CourseSearch {
        focus: true
        height: 40
        width: courseNav.width
    }
    delegate: CourseDelegate {
        height: courseNav.height/15
        width: courseNav.width
    }
    highlight: Rectangle {
        border.width: 1
        color: "transparent"
        z: 10
    }
    highlightFollowsCurrentItem: true
    highlightResizeVelocity: -1
    model: listmodel
    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 1000 }
    }
    remove: Transition {
        ParallelAnimation {
            NumberAnimation { property: "x"; to: courseNav.width; duration: 1000 }
            NumberAnimation { property: "y"; to: courseNav.height/2; duration: 1000 }
            NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
        }
    }
    add: Transition {
        NumberAnimation { properties: "x, y"; from: 0; duration: 750 }
    }

    spacing: 2
}
