import QtQuick 2.4
import QtQuick.Controls 1.3
import QtWebKit 3.0

TabView {
    id: tabView

    tabsVisible: count<2 ? false : true

    Tab {
        title: "Main page"
        WebView {
            id: webView

            anchors.fill: parent
            focus: true
            url: "file:/Deployment/courses/Test/index.html"

            BusyIndicator {
                anchors.centerIn: parent
                visible: webView.loading
            }
        }

    }
}

