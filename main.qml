import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: root

    height: 768

    menuBar: MenuBar {
        Menu {
            title: "Courses"
            visible: container.state == "courseView" ? true : false
            MenuItem {
                text: "New"
                shortcut: "Ctrl+N"
            }
            MenuItem {
                text: "Open"
                shortcut: "Ctrl+O"
            }
        }

        Menu {
            id: options
            title: "Options"
            MenuItem {
                text: "Settings";
                shortcut: "Ctrl+T"
                onTriggered: container.state="settings"
            }
            MenuSeparator { }
            MenuItem {
                text: "Profile"
                enabled: user.online ? true : false
                shortcut: "Ctrl+A"
            }
            MenuItem {
                text: user.online ? "Log out" : "Log in"
                visible: container.state=="login" ? false : true
                shortcut: "Ctrl+L"
                onTriggered: user.online ? logoutDialog.open() : container.state="login"
            }
        }
    }
    minimumWidth: 800
    minimumHeight: 600
    onLogout:  logoutDialog.open();
    visible: true
    visibility: "Maximized"
    width: 1366

    signal logout();

    Connections {
        target: user

        onLoginSuccess: {
            container.state="courseView";
        }
        onSkipLogin: {
            container.state="courseView";
        }
    }

    Item {
        id: container

        anchors.fill: parent

        SplitView {
            id: splitView

            anchors.fill: parent

            Loader {
                id: courseList

                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }
                focus: container.state=="courseView" ? true : false
                height: root.height
                Layout.minimumWidth: root.width/10
                Layout.maximumWidth: root.width/2
                width: root.width/5
            }

            Loader
            {
                id: courseView

                anchors {
                    top: parent.top
                    left: courseList.right
                    bottom: parent.bottom
                    right: parent.right
                }
                focus: container.state=="login" ? true : false
            }
        }

        state: "login"
        states: [
            State {
                name: "login"
                PropertyChanges { target: courseView; source: "LoginPage.qml" }
                PropertyChanges { target: courseList; width: Layout.minimumWidth }
            },
            State {
                name: "courseView"
                PropertyChanges { target: courseView; source: "CourseView.qml" }
                PropertyChanges { target: courseList; source: "CourseList.qml" }
                PropertyChanges { target: courseList; width: root.width/5 }
            },
            State {
                name: "settings"
                PropertyChanges { target: courseView; source: "Settings.qml" }
                PropertyChanges { target: courseList; width: Layout.minimumWidth }
            }

        ]
    }
    MessageDialog {
        id: logoutDialog

        onYes: {
            container.state = "login";
            user.logout();
        }
        standardButtons: StandardButton.Yes | StandardButton.No
        title: "Logout"
        text: "Are you sure you want to log out?"
    }
}
