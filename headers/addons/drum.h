#ifndef DRUM_H
#define DRUM_H

#include "gpaddon.h"
#include "GamepadEnums.h"
#include "BoardConfig.h"
#include "enums.pb.h"

#define ADC_MAX ((1 << 12) - 1) // 4095
#define ADC_PIN_OFFSET 26

#ifndef DRUM_ENABLED
#define DRUM_ENABLED 0
#endif
#ifndef DON_LEFT_PIN
#define DON_LEFT_PIN -1
#endif
#ifndef DON_RIGHT_PIN
#define DON_RIGHT_PIN -1
#endif
#ifndef KA_LEFT_PIN
#define KA_LEFT_PIN -1
#endif
#ifndef KA_RIGHT_PIN
#define KA_RIGHT_PIN -1
#endif

#ifndef DON_LEFT_THRESH
#define DON_LEFT_THRESH 30
#endif
#ifndef DON_RIGHT_THRESH
#define DON_RIGHT_THRESH 30
#endif
#ifndef KA_LEFT_THRESH
#define KA_LEFT_THRESH 10
#endif
#ifndef KA_RIGHT_THRESH
#define KA_RIGHT_THRESH 10
#endif

#ifndef DON_LEFT_THRESH_FORCE
#define DON_LEFT_THRESH_FORCE 2000
#endif
#ifndef DON_RIGHT_THRESH_FORCE
#define DON_RIGHT_THRESH_FORCE 2000
#endif
#ifndef KA_LEFT_THRESH_FORCE
#define KA_LEFT_THRESH_FORCE 1000
#endif
#ifndef KA_RIGHT_THRESH_FORCE
#define KA_RIGHT_THRESH_FORCE 1000
#endif

#ifndef SWITCH_PIN
#define SWITCH_PIN -1
#endif

#ifndef HID2VPAD_FIX
#define HID2VPAD_FIX 0
#endif

// IO Module Name
#define AddonName "Taiko no Tatsujin drum"

typedef struct {
		int32_t pin;
		int32_t thresh;
		int32_t threshForce;
} DrumArea;
typedef struct {
		DrumArea donLeft;
		DrumArea donRight;
		DrumArea kaLeft;
		DrumArea kaRight;

		int32_t switchPin;
		bool hid2vpadFix;
} DrumConfig;

typedef struct {
	bool a;
	bool b;
	bool right;
	bool left;
	bool l;
	bool r;
	bool plus;
} PressedButtons;

class DrumAddon : public GPAddon
{
public:
    virtual void bootProcess() {}
    virtual bool available();
    virtual void setup();
    virtual void preprocess();
    virtual void process();
    virtual std::string name() { return AddonName; }

private:

};

#endif
