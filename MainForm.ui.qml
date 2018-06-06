import QtQuick 2.6

Rectangle {
    property alias mouseArea: mouseArea

    anchors.fill: parent
    property alias listView: listView

    Column {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        Row {
            width: parent.width
            height: 30
            Text {
                id: filterLable
                width: 40
                text: "Filter: "
                anchors {
                    verticalCenter: parent.verticalCenter
                }
            }

            TextInput {
                id: filter
                width: parent.width - 100
                anchors {
                    verticalCenter: parent.verticalCenter
                    margins: 2
                    //                    left: filterLable.right
                }

                onTextChanged: {
                    listView.filterChanged(text)
                }
            }
        }

        Rectangle {
            width: parent.width
            height: parent.height - 30
            ListView {
                id: listView
                flickableDirection: Flickable.AutoFlickDirection
                anchors {
                    fill: parent
                }

                width: parent.width
                focus: true
                clip: true
                keyNavigationWraps: true

                highlight: Rectangle {
                    anchors {
                    }

                    width: parent.width
                    height: 30
                    color: "lightsteelblue"
                    radius: 5
                    opacity: 0.5
                    z: 3
                    y: listView.currentItem.y
                    Behavior on y {
                        SpringAnimation {
                            spring: 3
                            damping: 0.2
                        }
                    }
                }

                onCurrentItemChanged: console.log(
                                          listView.currentItem.myData.name + ' selected')

                highlightFollowsCurrentItem: false

                signal filterChanged(string filter)

                headerPositioning: ListView.OverlayHeader
                header: Row {
                    spacing: 0
                    z: 2
                    Repeater {
                        id: repeater
                        model: ["Sid", "Password"]
                        Rectangle {
                            width: 160
                            height: 30
                            color: "#3a4055"
                            border {
                                color: "grey"
                            }

                            Text {
                                id: title
                                text: modelData
                                color: "#ffffff"
                                font.bold: true
                                font.pixelSize: 20
                                anchors {
                                    horizontalCenter: parent.horizontalCenter
                                    verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                }

                delegate: Item {
                    property bool shown: true
                    property variant myData: item

                    visible: shown
                    height: shown ? 30 : 0

                    Connections {
                        target: listView
                        onFilterChanged: shown = item.name.toLowerCase(
                                             ).indexOf(
                                             filter.toLowerCase()) > -1
                    }

                    Row {
                        id: row1
                        spacing: 0

                        Rectangle {
                            border.color: "grey"
                            width: 160
                            height: 30
                            Text {
                                color: "#000000"
                                text: item.name

                                elide: Text.ElideRight
                                styleColor: "#f69606"
                                anchors.verticalCenter: parent.verticalCenter
                                font.bold: true
                                font.pixelSize: 14
                                anchors.margins: 5
                                anchors.left: parent.left

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        listView.currentIndex = index
                                        console.log(listView.currentIndex)
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: 160
                            height: 30
                            border.color: "grey"
                            TextInput {
                                text: item.password

                                anchors.verticalCenter: parent.verticalCenter
                                anchors.margins: 5
                                anchors.left: parent.left
                                selectByMouse: true
                                MouseArea {
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                }
                            }
                        }
                    }
                }
                model: listModel
                //            model: ListModel {
                //                ListElement {
                //                    name: "Grey"
                //                    colorCode: "grey"
                //                    password: "password1"
                //                }
                //            }
            }
        }
    }
}
