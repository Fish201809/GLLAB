
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    color: "red"
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Button{
            implicitWidth: parent.width
            implicitHeight: 30;
            text: "é€‰æ‹©"
            onClicked:{
                if(select_area.visible == false){
                    select_area.visible = true;
                }else{
                    select_area.visible = false;
                }
            }
        }
        Rectangle{
            id: select_area
            implicitWidth: root.width
            height: select_tool_rec.height + select_function_rec.height + select_pattern_rec.height
            ColumnLayout{
                anchors.fill: parent
                spacing: 0
                SelectToolRec{
                    id: select_tool_rec
                    width: root.width
                }
                SelectFunctionRec{
                    id: select_function_rec
                    anchors.top: select_tool_rec.bottom
                    width:  root.width
                }
                SelectPatternRec{
                    id: select_pattern_rec
                    width:  root.width
                    Layout.fillHeight: true
                }
            }
        }
       
        Button{
            implicitWidth: parent.width
            implicitHeight: 30;
            text: "ç¼–è¾‘"
            onClicked:{
                if(edit_tool_rec.visible == false){
                    edit_tool_rec.visible = true;
                }else{
                    edit_tool_rec.visible = false;
                }
            }
        }
        EditToolRec{
            id: edit_tool_rec
            implicitWidth: parent.width
            implicitHeight:30
            color: "pink"
        }
        Rectangle{
            implicitWidth: parent.width
            Layout.fillHeight: true
            color: "gray"
        }
    }
}
