#ifndef MODEHELPER_H
#define MODEHELPER_H
#include <stdint.h>
extern "C"
{
#include "all/mavlink.h"
#include "all/all.h"
}

struct ModeHelper {
    enum PX4_CUSTOM_MAIN_MODE {
        PX4_CUSTOM_MAIN_MODE_MANUAL = 1,
        PX4_CUSTOM_MAIN_MODE_ALTCTL,
        PX4_CUSTOM_MAIN_MODE_POSCTL,
        PX4_CUSTOM_MAIN_MODE_AUTO,
        PX4_CUSTOM_MAIN_MODE_ACRO,
        PX4_CUSTOM_MAIN_MODE_OFFBOARD,
        PX4_CUSTOM_MAIN_MODE_STABILIZED,
        PX4_CUSTOM_MAIN_MODE_RATTITUDE
    };

    enum PX4_CUSTOM_SUB_MODE_AUTO {
        PX4_CUSTOM_SUB_MODE_AUTO_READY = 1,
        PX4_CUSTOM_SUB_MODE_AUTO_TAKEOFF,
        PX4_CUSTOM_SUB_MODE_AUTO_LOITER,
        PX4_CUSTOM_SUB_MODE_AUTO_MISSION,
        PX4_CUSTOM_SUB_MODE_AUTO_RTL,
        PX4_CUSTOM_SUB_MODE_AUTO_LAND,
        PX4_CUSTOM_SUB_MODE_AUTO_RTGS,
        PX4_CUSTOM_SUB_MODE_AUTO_FOLLOW_TARGET
    };
    union px4_custom_mode {
        struct {
            uint16_t reserved;
            uint8_t main_mode;
            uint8_t sub_mode;
        };
        uint32_t data;
        float data_float;
    };

    enum APMode {
        ARDUPILOT_COPTER,
        ARDUPILOT_PLANE,
        ARDUPILOT_VTOL,
        PIXHAWK,
        UNDEFIEND
    };

    static uint8_t getBaseMode(APMode type)
    {
        uint8_t base = 0;
        switch (type) {
        case ModeHelper::APMode::ARDUPILOT_COPTER:
        case ModeHelper::APMode::ARDUPILOT_PLANE:
        case ModeHelper::APMode::ARDUPILOT_VTOL: {

            base = base | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED |
                   MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_AUTO_ENABLED | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
            break;
        }
        case ModeHelper::APMode::PIXHAWK:
        default: {

            base = base | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED |
                   MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_AUTO_ENABLED | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
            break;
        }
        }
        return base;
    }

    static uint32_t getModeARMable(APMode type)
    {
        switch (type) {
        case APMode::ARDUPILOT_COPTER:
            return COPTER_MODE_ALT_HOLD;
        case APMode::ARDUPILOT_PLANE:
            return PLANE_MODE_STABILIZE;
        case APMode::ARDUPILOT_VTOL:
            return PLANE_MODE_QHOVER;
        case APMode::PIXHAWK:
        default: {
            union px4_custom_mode px4_mode;
            px4_mode.data = 0;
            px4_mode.main_mode = PX4_CUSTOM_MAIN_MODE_ALTCTL;
            px4_mode.sub_mode = 0;
            return px4_mode.data;
        }
        }
    }
    static uint32_t getModeLand(APMode type)
    {
        switch (type) {
        case APMode::ARDUPILOT_COPTER:
            return COPTER_MODE_LAND;
        case APMode::ARDUPILOT_PLANE:
            return PLANE_MODE_GUIDED;
        case APMode::ARDUPILOT_VTOL:
            return PLANE_MODE_QLAND;
        case APMode::PIXHAWK:
        default: {
            union px4_custom_mode px4_mode;
            px4_mode.data = 0;
            px4_mode.main_mode = PX4_CUSTOM_MAIN_MODE_AUTO;
            px4_mode.sub_mode = PX4_CUSTOM_SUB_MODE_AUTO_LAND;
            return px4_mode.data;
        }
        }
    }
    static uint32_t getModeAuto(APMode type)
    {
        switch (type) {
        case APMode::ARDUPILOT_COPTER:
            return COPTER_MODE_AUTO;
        case APMode::ARDUPILOT_PLANE:
            return PLANE_MODE_AUTO;
        case APMode::ARDUPILOT_VTOL:
            return PLANE_MODE_AUTO;
        case APMode::PIXHAWK:
        default: {
            union px4_custom_mode px4_mode;
            px4_mode.data = 0;
            px4_mode.main_mode = PX4_CUSTOM_MAIN_MODE_AUTO;
            px4_mode.sub_mode = PX4_CUSTOM_SUB_MODE_AUTO_MISSION;
            return px4_mode.data;
        }
        }
    }
    static uint32_t getModeRTL(APMode type)
    {
        switch (type) {
        case APMode::ARDUPILOT_COPTER:
            return COPTER_MODE_RTL;
        case APMode::ARDUPILOT_PLANE:
            return PLANE_MODE_RTL;
        case APMode::ARDUPILOT_VTOL:
            return PLANE_MODE_RTL;
        case APMode::PIXHAWK:
        default: {
            union px4_custom_mode px4_mode;
            px4_mode.data = 0;
            px4_mode.main_mode = PX4_CUSTOM_MAIN_MODE_AUTO;
            px4_mode.sub_mode = PX4_CUSTOM_SUB_MODE_AUTO_RTL;
            return px4_mode.data;
        }
        }
    }
    static uint32_t getModeGuided(APMode type)
    {
        switch (type) {
        case APMode::ARDUPILOT_COPTER:
            return COPTER_MODE_GUIDED;
        case APMode::ARDUPILOT_PLANE:
            return PLANE_MODE_GUIDED;
        case APMode::ARDUPILOT_VTOL:
            return PLANE_MODE_GUIDED;
        case APMode::PIXHAWK:
        default: {
            union px4_custom_mode px4_mode;
            px4_mode.data = 0;
            px4_mode.main_mode = PX4_CUSTOM_MAIN_MODE_OFFBOARD;
            px4_mode.sub_mode = 0;
            return px4_mode.data;
        }
        }
    }
};

#endif // MODEHELPER_H
