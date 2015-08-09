import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Item {
    id: item1
    width: 640
    height: 480

    property alias preview: preview
    property alias debug_layer: debug_layer

    RowLayout {
        width: 350
        height: 30

        Button {
            id: button1
            text: qsTr("Press Me 1")
        }

        Button {
            id: button2
            text: qsTr("Press Me 2")
        }
    }

    ScrollView {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 87
        anchors.fill: parent
        Image {
            id: preview
            fillMode: Image.Pad
            source: ""
            Item {
                Image {
                    id: debug_layer
                    fillMode: Image.Pad
                    source: ""
                    visible: false
                }
                GreyMaskThreshold {
                    id: debug_gray2a
                    anchors.fill: debug_layer
                    src: debug_layer
                }
            }
        }
    }

    Item {
        id: debug_ctrls
        SpinBox {
            id: thr_spin
            x: 224
            y: 54
            value: 256
            maximumValue: 256
            onValueChanged: debug_gray2a.thr = value / maximumValue
        }

        Label {
            id: thr_label
            x: 296
            y: 54
            text: qsTr("min_match * 256")
        }

        Slider {
            id: thr_slider
            x: 8
            y: 54
            value: thr_spin.value
            maximumValue: thr_spin.maximumValue
            onValueChanged: thr_spin.value = value;
        }
    }

    CheckBox {
        id: damage
        x: 355
        y: 15
        text: qsTr("Show damage")
    }
}