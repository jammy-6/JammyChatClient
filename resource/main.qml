import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts
ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 600
    title: "Jammy聊天客户端"
    minimumWidth: 1000
    minimumHeight:600
    //Material.theme: Material.Dark

    Row {
        width: root.width
        height: root.height

        Rectangle {
            id: leftBar
            width: 60
            height: parent.height
            color: "grey"

            Column{

                anchors.fill: parent
                spacing:10

                topPadding:30

                ToolButton{
					id:msgBtn
                    width:parent.width
					checkable:true
					checked:true
                    autoExclusive:true
                    topPadding:2
                    bottomPadding:2
                    contentItem:Column{
                        spacing: 2
                        Image {
                                source: "qrc:/ChatWindow/message.png"
                                anchors.horizontalCenter: parent.horizontalCenter
								smooth:true
								antialiasing: true
                                height:32
                                
                                fillMode: Image.PreserveAspectFit
                        }
                        Text{
                                width:parent.width
                                height:contentHeight 
                                Component.onCompleted: {
									console.log("contentHeight: ",contentHeight)
                                    console.log("height: ",height)
								}
                                anchors.horizontalCenter: parent.horizontalCenter
                                text:"消息"
                                font.bold:msgBtn.checked
                                horizontalAlignment:Text.AlignHCenter
                        }
                    }
					background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
						color: msgBtn.checked ? "lightblue" : "lightgray"
					}
                }
                ToolButton{
                    id:friend
                    width:parent.width
					checkable:true
                    checked:false
                    autoExclusive:true
                    topPadding:2
                    bottomPadding:2
                    contentItem:Column{
                        spacing:2
                        Image {
                                source: "qrc:/ChatWindow/friend.png"
                                smooth:true
								antialiasing: true
                                anchors.horizontalCenter: parent.horizontalCenter
                                height:32
                                
                                fillMode: Image.PreserveAspectFit
                        }
                        Text{
                                width:parent.width
                                height:contentHeight 
                                Component.onCompleted: {
									console.log("contentHeight: ",contentHeight)
                                    console.log("height: ",height)
								}
                                anchors.horizontalCenter: parent.horizontalCenter
                                text:"好友"
                                font.bold:friend.checked
                                horizontalAlignment:Text.AlignHCenter
                        }
                    }
					background: Rectangle {
						implicitWidth: 100 ;implicitHeight: 40
                        color: friend.checked ? "lightblue" : "lightgray"
					}

                }

            }


        }
        StackLayout{
            id: mainView 
            currentIndex: msgBtn.checked ? 0 : 1
            Row{
                   FriendList{
                        id:contactView
                        width: 240
                        height: parent.height
                    }

                    ChatList{
                        width: root.width-leftBar.width-contactView.width
                        height:root.height
                    }
            }
            Row{
                    
                   FriendOrderList{
                        id:friendOrderView
                        width: 240
                        height: root.height
                    }
                    Rectangle{
                        color:Qt.rgba(0.94, 0.94, 0.94, 1.0)
						width: root.width-leftBar.width-friendOrderView.width
                        height:root.height
                    }
            }
        }

    }
    Connections{
        target: friendListModel
        function onModelChanged() {
            // 当接收到 mySignal 信号时，执行以下操作
            friendOrderView.friendArray=friendOrderView.convertToList();
        }
    }
}
