import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
ScrollView {
        Component.onCompleted:{
            ScrollBar.horizontal.interactive=false
            ScrollBar.vertical.interactive=true
        }
        spacing:0
        Component{
            id:buttonComponent
            Button{
                width: viewWidth
                height: 50
                contentItem:Row{
                    spacing:2
                    Image {
                            id:image
                            source: "qrc:/ChatWindow/newFriend.png"
                            smooth:true
							antialiasing: true
                            anchors.verticalCenter: parent.verticalCenter
                            height:32
                                
                            fillMode: Image.PreserveAspectFit
                    }
                    Text{
                            width:parent.width-image.width
                            height:contentHeight 
                            Component.onCompleted: {
								console.log("contentHeight: ",contentHeight)
                                console.log("height: ",height)
							}
                            anchors.verticalCenter: parent.verticalCenter
                            text:"新的好友"
                            horizontalAlignment:Text.AlignHCenter
                    }
                }
                onClicked:{
                     friendOrderListView.currentIndex=0;
                }
            }
        }
        Component{
            id:friendComponent

            Item {
                width: viewWidth
                height: 50
                
                Rectangle {

                    width: parent.width
                    height: parent.height
                    color: modelCurrentIndex === modelIndex ? "#c8c6c5" : "transparent"
                    //color: index % 2 == 0 ? "#f0f0f0" : "#ffffff"
                    clip: true

                    Row {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        leftPadding:10
                        Image {
                            source: modeAvatar
                            width: 40
                            height: 40
                            antialiasing: true
                            fillMode: Image.PreserveAspectCrop
                            smooth:true
                            clip: true
                            Component.onCompleted:{
                                console.log(source)
                            }

                        }
                        Text {
                            text: modeName
                            font.pixelSize: 12
                            color: "#333333"
						    anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: { friendOrderListView.currentIndex = modelIndex }
                    }
                }
            }
        }
        //friendListModel是C++中的QAbstractListModel，然后注册进全局context
        //下面在js中给它每一个元素手动添加一个type属性
        property var friendArray: convertToList()

        function convertToList()  {
            let newModel = Qt.createQmlObject('import QtQuick 2.15; import QtQuick.Controls 2.15; ListModel {}',
                                              this, "dynamicSnippet");
            let count = friendListModel.rowCount();
            newModel.append({"type":"button","avatar": "avatar","name":"name"});
            for (let i = 0; i < count; i++) {
                let index = friendListModel.index(i, 0);
                let avatar = friendListModel.data(index,261);
                let name = friendListModel.data(index,257);
                console.log(avatar)
                newModel.append({"type":"item","avatar": avatar,"name":name});
            }
            console.log(newModel)
            return newModel;
        }

        ListView {
            id: friendOrderListView
            model: friendArray
            width:parent.width
            height:parent.height
            delegate: Loader{
                property int viewWidth:friendOrderListView.width
                property string modeAvatar:avatar
                property string modeName:name
                property int modelCurrentIndex:friendOrderListView.currentIndex
                property int modelIndex:index
                sourceComponent:{
                    if(type=="button") return buttonComponent
                    else return friendComponent
                }

            }
            
            Keys.onSpacePressed: {
                friendOrderListView.positionViewAtEnd();
            }
        }
        ScrollBar.horizontal.interactive:false
        ScrollBar.vertical.interactive:true

}
