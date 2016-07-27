import QtQuick 1.0

Item {
    id: root
    property real value : 0

    width: 363; height: 278

    Image { source: "round.png" }

    Image {
        x: 181.5 - 104
        y: 139 - 32
        source: "arrow.png"
        smooth: true
        transform: Rotation {
            origin.x: 104; origin.y: 32
            angle: root.value * 249 / 2000 - 1.8

            Behavior on angle {
                SmoothedAnimation {
                    velocity: 256
                }
            }
        }
    }
}
