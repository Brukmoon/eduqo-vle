import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Rectangle {
    id: loginPage

    function clearCache() {
        settings.remove("user/username");
        settings.remove("user/password");
        settings.remove("user/rememberMe");
    }

    Component {
        id: redBorderStyleWrapper;

        TextFieldStyle {
            id: redBorderStyle
            background: Rectangle {
                border.color: Qt.lighter("red")
            }
        }
    }
    Connections {
        id: connections
        target: user
        onLoginFailed: errorLabel.text = qsTr("Username and password do not match.");
        onLoginSuccess: {
            if(rememberCheck.checked) {
                settings.setValue("user/username", user.username);
                settings.setValue("user/password", user.password);
                settings.setValue("user/rememberMe", true);
            }
        }
    }
    FocusScope {
        focus: true
        anchors.fill: parent

        Column {
            id: container

            anchors { fill: parent; margins: 20 }
            spacing: height/100
            Component.onCompleted: {
                container.rememberMe = settings.getValue("user/rememberMe", false)
            }

            property var defaultStyle: undefined
            property bool rememberMe: false

            Label {
                id: titleLabel

                height: parent.height/17
                text: qsTr("Welcome")
                font { pixelSize: container.height/25; family: "Helvetica" }
            }
            Label {
                text: qsTr("Please enter your login details to proceed.")
            }

            TextField {
                id: usernameField

                focus: true
                height: container.height/30
                placeholderText: qsTr("Enter username")
                readOnly: container.rememberMe
                width: container.width/5
                text: container.rememberMe ? settings.getValue("user/username", "") : ""
                Component.onCompleted: container.defaultStyle = usernameField.style;
            }
            TextField {
                id: passwordField

                echoMode: TextInput.Password
                height: container.height/30
                visible: container.rememberMe ? false : true
                placeholderText: qsTr("Enter password")
                width: container.width/5
            }
            Label {
                id: errorLabel

                visible: false
            }
            CheckBox {
                id: rememberCheck
                text: "Remember me"
                checked: container.rememberMe
                onCheckedChanged: if(usernameField.readOnly) {
                                      loginPage.clearCache();
                                      passwordField.text = ""
                                      passwordField.visible = true;
                                      usernameField.text = ""
                                      usernameField.readOnly = false
                                  }
            }

            Row {
                spacing: 10

                Button {
                    id: loginButton

                    function login(username, password)
                    {
                        errorLabel.visible = true;
                        errorLabel.text = "";
                        usernameField.style = passwordField.style = container.defaultStyle;

                        if(username !== "" && password !== "") {
                            user.username = username;
                            user.password = password;
                            user.login();
                        } else {
                            if(username === "" && password === "") {
                                usernameField.style = redBorderStyleWrapper;
                                passwordField.style = redBorderStyleWrapper;
                                errorLabel.text = qsTr("Missing username and password.")
                            }
                            else {
                                if(username === "") {
                                    usernameField.style = redBorderStyleWrapper;
                                    errorLabel.text = qsTr("Missing username.");
                                }
                                if(password === "") {
                                    passwordField.style = redBorderStyleWrapper;
                                    errorLabel.text = qsTr("Missing password.")
                                }
                            }
                        }
                    }

                    height: container.height/30
                    text: qsTr("Login")
                    width: container.width/10-5
                    onClicked: {
                        login(usernameField.text, settings.getValue("user/password", passwordField.text))
                    }

                }
                Button {
                    id: cancelButton
                    width: container.width/10-5
                    height: container.height/30
                    text: qsTr("Skip")
                    onClicked: user.skipLogin();
                }
            }
        }
    }
}
