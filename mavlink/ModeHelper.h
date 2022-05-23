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
            return px4_mode.data;
        }
        }
    }

};

#endif // MODEHELPER_H
