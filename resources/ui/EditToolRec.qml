
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: edit_tool_row
    height: 10
    color: "red"
    
    Text{
        id: edit_tool_text
        anchors.top: parent.top
        anchors.left: parent.left
        text: "编辑"
    }

    RowLayout{
        id: edit_row_layout
        anchors.top: edit_row_layout.bottom
        anchors.left: parent.left
        spacing: 0
        Button{
            text: "平面裁剪"
            implicitWidth: edit_tool_row.width / 3
            implicitHeight: 30
        }
        Button{
            text: "补孔"
            implicitWidth: edit_tool_row.width / 3
            implicitHeight: 30
        }
        Button{
            text: "删除"
            implicitWidth: edit_tool_row.width / 3
            implicitHeight: 30
        }
    }
   
}
