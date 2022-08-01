#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <QtMath>

struct MissionItem {
    enum class ItemType : int
    {
        HOME = 0,
        SIMPLE_POINT,
        TAKEOFF,
        RTL,
        LAND,
        JUMP,
        DELAY,
        DISTANCE,
        SPEED,
        SET_SERVO,
        ROI,
        CAMERA,
        GIMBAL,
        TRIGGER,
        PARACHUTE
    };
    enum class Frame : int
    {
        RELATIVE,
        RELIEF,
        ABSOLUTE,
        INVALID
    };

    double param_1 = qQNaN();
    double param_2 = qQNaN();
    double param_3 = qQNaN();
    double param_4 = qQNaN();
    double param_x = qQNaN();
    double param_y = qQNaN();
    double param_z = qQNaN();
    Frame frame = Frame::INVALID;
    ItemType type = ItemType::SIMPLE_POINT;
};


#endif // MISSIONITEM_H
