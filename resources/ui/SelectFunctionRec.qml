
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    implicitHeight: select_tool_text.height + row_layout.height
    Text{
        id:select_tool_text
        anchors.top: parent.top
        anchors.left: parent.left
        text: "选择功能"
    }
    RowLayout{
        id:row_layout
        anchors.top: select_tool_text.bottom
        anchors.left: parent.left
        spacing: 0
        Button{
            text: "全选"
            implicitWidth: root.width / 3
            implicitHeight: 30
        }
        Button{
            text: "全不选"
            implicitWidth: root.width / 3
            implicitHeight: 30
           
        }
        Button{
            text: "反选"
            implicitWidth: root.width / 3
            implicitHeight: 30
            
        }
    }
}
