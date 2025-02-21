import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
Column{
    ///聊天列表
    Rectangle{
        id:msgRect
        width: parent.width
        height:parent.height-inputRow.height
        color:Qt.rgba(0.94, 0.94, 0.94, 1.0)///聊天框背景颜色
        
        Column {
            anchors.fill: parent
            spacing: 10
            padding: 10

            ListView {
                id: chatListView
                width: parent.width
                property int currentSelectUserId: userManagement.friends.data(userManagement.friends.index(contactView.currentIndex, 0), 259)

                onCurrentSelectUserIdChanged: {
                    //currentSelectUserId = userManagement.friends.data(userManagement.friends.index(contactView.currentIndex, 0), 259)
                    console.log("currentSelectUserId changed to", currentSelectUserId)
                }
                
                Component.onCompleted:{
                    console.log(userManagement.friends.getChatMsgsByIndex(currentSelectUserId))
                    console.log(userManagement.friends.getChatMsgsByIndex(currentSelectUserId))
                    console.log()
                }
                height: parent.height - textInput.height - 20
                model: userManagement.friends.getChatMsgsByIndex(currentSelectUserId)
               onModelChanged:{
                    chatListView.positionViewAtEnd()
               }
                //model: chatModel

                spacing: 10
                displaced: Transition {
                    NumberAnimation { properties: "x,y"; duration: 1000 }
                }
                delegate: Row {
                    id:msgRow
                    layoutDirection:model.from===userManagement.loginId?Qt.RightToLeft:Qt.LeftToRight
                    //layoutDirection:model.isSender?Qt.RightToLeft:Qt.LeftToRight
                    rightPadding: 15
                    width: chatListView.width
                    height: Math.max(column.height,rect1.height)
                    property alias textItem: textItem
                    spacing: 10
                    Column{
                        id:column
                        spacing:3
                        Text {
                            text: model.time
                            font.pixelSize: 10
                            color: "gray"
                            horizontalAlignment: Text.AlignRight
                            anchors.horizontalCenter: avatar.horizontalCenter
                        }
                        Image {
                            id: avatar
                            antialiasing: true
                            width: 50
                            height: 50
                            source:model.from===userManagement.loginId?userManagement.loginAvatar:userManagement.friends.data(userManagement.friends.index(contactView.currentIndex,0),260)
                            //source: model.avatar
                            fillMode: Image.PreserveAspectCrop
                            clip: true
                        }
                    }


                    Rectangle {
                        id:rect1
                        anchors.verticalCenter: parent.verticalCenter
                        width: textItem.width + 15  // 添加边距
                        height: textItem.height + 15  // 添加边距
                        color: "lightgreen"
                        radius: 10
                        // border.color: "darkgreen"

                        Text {
                            id: textItem
                            font.pixelSize: 16
                            anchors.centerIn: parent
                            property int realWidth
                            width:Math.min(chatListView.width/3*2,realWidth+3)
                            horizontalAlignment:Text.AlignCenter
                            text: model.data
                            Component.onCompleted:{
                                realWidth = contentWidth
                                wrapMode=Text.Wrap
                            }


                        }
                    }

                }
            }


        }


    }
    //发送消息栏以及按钮
    Row {
        z: 10 // 设置较高的 z 值以确保覆盖在顶层
        id:inputRow
        width: parent.width
        spacing: 10

        TextField {
            id: textInput

            width: parent.width - sendButton.width - 20
            placeholderText: "Type a message..."
            onAccepted: sendMessage()
        }

        Button {
            id: sendButton
            text: "Send"
            onClicked: sendMessage()
        }
    }
    function sendMessage() {
        if (textInput.text !== "") {
            var date = new Date();
            userManagement.friends.appendMessage(userManagement.loginId, chatListView.currentSelectUserId,  date,textInput.text,);
            textInput.clear();
            chatListView.positionViewAtEnd()

        }
    }

}



