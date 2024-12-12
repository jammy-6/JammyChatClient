import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

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



                Button{
					id:msgBtn
                    width:parent.width
					checkable:true
					checked:true
                    autoExclusive:true
                    contentItem:Column{
                        anchors.fill:parent
                        Image {
                                source: "file:///D:/repo/123123123/消息.png"
                                x:(parent.width-width)/2
                                y:(parent.height-height)/2
								smooth:true
								antialiasing: true
                                height:32
                                width:32
                                fillMode: Image.PreserveAspectFit
                        }
                    }
					background: Rectangle {
						implicitWidth: 100 ;implicitHeight: 40
						color: msgBtn.checked ? "lightblue" : "lightgray"
					}

                }
                Button{
                    id:friend
                    width:parent.width
					checkable:true
                    checked:false
                    autoExclusive:true
                    contentItem:Column{
                        anchors.fill:parent
                        Image {
                                source: "file:///D:/repo/123123123/好友.png"
                                smooth:true
								antialiasing: true
                                x:(parent.width-width)/2
                                y:(parent.height-height)/2
                                height:32
                                width:32
                                fillMode: Image.PreserveAspectFit
                        }
                    }
					background: Rectangle {
						implicitWidth: 100 ;implicitHeight: 40
                        color: friend.checked ? "lightblue" : "lightgray"
					}

                }

            }


        }

        FriendList{
            id:contactView
            width: 240
            height: parent.height
        }

        ChatList{

            width: parent.width-leftBar.width-contactView.width
            height:parent.height

        }
    }
}
