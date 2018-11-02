
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick 2.0
import QtQuick 2.8
import QtQuick.Window 2.2
import OpenGLUnderQML 1.0



ApplicationWindow {
    id: window
    visible: true
    width: 1400
    height: 900
    minimumWidth: 1100
    minimumHeight: 700
    title: "Model Edit"
    //property QtObject $app: AppGlobal{}
        //   menuBar: MenuBar {
        //       Menu { MenuItem {} }
        //       Menu { MenuItem {} }
        //   }    

    toolBar: ToolBar {
        id: tool_bar
        RowLayout {
            //anchors.fill: tool_bar
            ToolButton {
                text: "文件"
                onClicked:{
                        if(tool_visual.visible == false){
                            tool_visual.visible = true;
                        }else{
                            tool_visual.visible = false;
                        }
                }     
            }
            ToolButton {
                text: "帮助"
            }  
        }
    }

    Rectangle {
        id: content_visual
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            spacing: 0
            Rectangle{
                id: tool_visual
                height: 30
                width: window.width
                color: "gray"
            }
            Rectangle{
                Layout.fillHeight: true
                width: window.width
                SplitView{
                    anchors.fill: parent
                    orientation: Qt.Horizontal

                    // Rectangle{
                    //     id: viewer
                    //     Layout.fillWidth: true
                    //     Layout.minimumWidth: 800
	                // }

                    Triangle{
                           id: viewer
                        Layout.fillWidth: true
                        Layout.minimumWidth: 800
                    //   SequentialAnimation on num {
                    //         NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
                    //         NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
                    //         loops: Animation.Infinite
                    //         running: true
                    //     }
                    }

                    // QuickOSGViewer{
                    //     id: viewer
                    //     Layout.fillWidth: true
                    //     Layout.minimumWidth: 800
                    //     framerate: 100
                    //     focus: true
                    //     scene: $app.loadModelFile("cow.osg")
                    //     onPressed: {

                    //     }
                    //     onMove: {
                    //         //pline_canvas.move();
                    //     }
                    //     onReleased:{
                    //         //pline_canvas.released();
                    //     }
                    //     Canvas {
                    //         id: pline_canvas
                    //         anchors.fill: viewer
                    //         onPaint: {
                    //             var ctx = getContext("2d");
                    //             ctx.strokeStyle = "red";
                    //             ctx.beginPath();
                    //             if(viewer.selectLength() > 0){
                    //                 ctx.moveTo(viewer.selectValueX(0), viewer.selectValueY(0));
                    //                 for(var i = 0;i < viewer.selectLength(); ++i){
                    //                     ctx.lineTo(viewer.selectValueX(i), viewer.selectValueY(i));
                    //                 }
                    //                 ctx.lineTo(viewer.selectValueX(0), viewer.selectValueY(0));
                    //             }
                    //             ctx.stroke();
                    //         }   
                            
                    //         function move() {
                    //             pline_canvas.requestPaint();
                    //             pline_canvas.getContext("2d").clearRect(0, 0, pline_canvas.width, pline_canvas.height);
                    //         }    
                    //         function released(){
                    //             pline_canvas.requestPaint();
                    //             pline_canvas.getContext("2d").clearRect(0, 0, pline_canvas.width, pline_canvas.height)
                    //         }     
                    //     }
                        
                    //     Connections {
                    //         target:fill_hole_widget 
                    //         onFill_undo:{
                    //             viewer.UnDo();
                    //         }
                    //     }
                        
                    // }
                    // NormalLeftWidget{
                    //     id:normal_left_widget;
                    //     width: 300
                    //     Layout.maximumWidth: 300
                    //     Layout.minimumWidth: 200
                    // }
                    FillHoleWidget{
                        id:fill_hole_widget;
                        width: 300
                        Layout.maximumWidth: 300
                        Layout.minimumWidth: 200
                    }
                }    
            }
        }  
    }
    statusBar:StatusBar{

    }  
}
