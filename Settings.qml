import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Rectangle {
    id: root

    function saveSettings() {
        settings.setValue("courses/sourceDir", courseDirectoryField.text);
        //settings.setValue("database/hostname", databaseHostname.text);
        //settings.setValue("database/username", databaseUsername.text);
    }

    Item {
        id: container

        anchors { fill: parent; margins: 20 }

        Column {
            spacing: 10
            Label {
                text: qsTr("Here you can see and modify application settings.")
            }
            GroupBox {
                id: groupBox

                title: "Courses"

                Column {
                    spacing: 5
                    /*Row {
                        Label {
                            id: type

                            text: "Type: "
                            width: 75
                        }

                        ComboBox {
                            id: databaseType

                            width: root.width/5
                            height: root.height/30
                            model: [ "MSSqlServer", "MySqlServer", "PostgreSQL", "Oracle", "Sybase", "SQLite", "Interbase", "DB2" ]
                            Component.onCompleted: currentIndex = find(settings.getValue("database/type"))
                        }
                    }*/


                    Row {
                        Label {
                            id: courseDirectoryLabel

                            text: "Directory: "
                            width: 75
                        }
                        TextField {
                            id: courseDirectoryField

                            height: root.height/30
                            placeholderText: "Source directory"
                            width: root.width/5-20

                            Component.onCompleted: text = settings.getValue("courses/sourceDir", "")
                        }
                        Button {
                            height: root.height/30
                            onClicked: fileDialog.visible = true
                            text: "..."
                            width: 20
                        }

                        FileDialog {
                            id: fileDialog

                            selectFolder: true
                            title: "Select folder"
                            onAccepted: {
                                var folder = fileDialog.folder.toString();
                                folder = folder.replace(/^(file:\/{3})/,"");
                                courseDirectoryField.text = decodeURIComponent(folder);
                            }
                        }
                    }
                    Row {
                        Label {
                            id: usernameLabel

                            text: "Username: "
                            width: 75
                        }
                        TextField {
                            id: databaseUsername

                            height: root.height/30
                            placeholderText: "Username to the database"
                            width: root.width/5
                        }
                    }
                    Row {
                        Label {
                            id: passwordLabel

                            text: "Password: "
                            width: 75
                        }
                        TextField {
                            id: databasePassword

                            height: root.height/30
                            echoMode: TextInput.Password
                            placeholderText: "Password to the database"
                            width: root.width/5
                        }
                    }

                }
            }

            Button {
                id: save
                text: "Save"
                onClicked: saveSettings();
            }
        }
    }

}

