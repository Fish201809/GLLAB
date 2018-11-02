
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: fill_hole_widget
    signal fill_back()
    signal fill_undo()
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            anchors.left: parent.left
            anchors.right: parent.right
            color: "green"
            height: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                Button{
                    text: "取消"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height
                    onClicked:{
                        fill_hole_widget.fill_back();
                    }
                }
                Button{
                    text: "确定"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height
                    onClicked:{
                      //fill_hole_widget.fill_back();
                    }
                }
                Button{
                    text: "撤销"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height
                    onClicked:{
                        fill_hole_widget.fill_undo();
                    }
                }
            }
        }
        Text{
            text: "补洞方式"
        }
        Rectangle{
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                RadioButton{
                    text:"曲率"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height / 3
                }
                RadioButton{
                    text:"补线"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height / 3
                }
                RadioButton{
                    text:"平面"
                    implicitWidth: parent.width / 3
                    implicitHeight: parent.height / 3
                }
            }     
        }
        Rectangle{
            color: "gray"
            width: parent.width
            Layout.fillHeight: true
        }
    }
}
