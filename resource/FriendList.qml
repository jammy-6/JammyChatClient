import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
ScrollView {


    ListView {
        id: friendListView
        
        model: friendListModel

        delegate: Item {
            width: friendListView.width
            height: 80

            Rectangle {
                width: parent.width
                height: parent.height
                color: friendListView.currentIndex === index ? "#c8c6c5" : "transparent"
                //color: index % 2 == 0 ? "#f0f0f0" : "#ffffff"
                clip: true
                Row {

                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    x:10

                    Image {

                        source: model.avatar
                        width: 50
                        height: 50
                        antialiasing: true
                        fillMode: Image.PreserveAspectCrop
                        smooth:true
                        clip: true

                    }

                    Column {
                        width: friendListView.width - 70
                        spacing: 5

                        Row {
                            spacing: 100
                            Text {
                                text: model.name
                                font.pixelSize: 20
                                color: "#333333"
                            }

                            Text {
                                text: model.time
                                font.pixelSize: 14
                                color: "#999999"
                                width: parent.parent.width - (parent.children[0].implicitWidth + parent.spacing)
                                horizontalAlignment: Text.AlignRight
                                anchors.verticalCenter: parent.verticalCenter
                                rightPadding: 20
                                font.family: "等线"
                            }
                        }

                        Row {
                            spacing: 10
                            Text {
                                text: model.status
                                font.pixelSize: 14
                                color: model.status === "在线" ? "#00aa00" : "#aa0000"
                            }

                            Item {
                                width: friendListView.width - 200
                            }

                            Text {
                                text: model.lastMessage
                                width: parent.parent.width - (parent.children[0].implicitWidth + parent.spacing)
                                horizontalAlignment: Text.AlignRight
                                font.pixelSize: 14
                                color: "#666666"
                                font.family: "楷体"
                                rightPadding: 20
                            }
                        }
                    }
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: { friendListView.currentIndex = index }
                }
            }
        }

        Keys.onSpacePressed: {
            friendListView.positionViewAtEnd();
        }

    }
    ScrollBar.horizontal.interactive: false
    ScrollBar.vertical.interactive: true
}
