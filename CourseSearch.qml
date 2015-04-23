import QtQuick 2.4
import QtQuick.Controls 1.3

FocusScope {
    TextField {
        id: searchField
        anchors.fill: parent
        focus: true
        font.pixelSize: 14
        onTextChanged: {
            var regExp = new RegExp("^" + searchField.text);
            console.log(regExp)
            listmodel.filterRegExp = regExp

        }
        placeholderText: qsTr("Search")
    }
}

