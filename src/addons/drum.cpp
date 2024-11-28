#include "addons/drum.h"
#include "storagemanager.h"
#include "config.pb.h"
#include "enums.pb.h"
#include "hardware/adc.h"
#include "helper.h"
#include "drivermanager.h"

bool DrumAddon::available()
{
	return Storage::getInstance().getAddonOptions().drumOptions.enabled;
}

static uint16_t readPin(Pin_t pin_adc) {
    adc_select_input(pin_adc);
    return adc_read();
}

static DrumConfig cfg;
PressedButtons pressed;

void DrumAddon::setup()
{
    const DrumOptions& drumOptions = Storage::getInstance().getAddonOptions().drumOptions;

	if(isValidPin(drumOptions.donLeftPin)) adc_gpio_init(drumOptions.donLeftPin);
	if(isValidPin(drumOptions.donRightPin)) adc_gpio_init(drumOptions.donRightPin);
	if(isValidPin(drumOptions.kaLeftPin)) adc_gpio_init(drumOptions.kaLeftPin);
	if(isValidPin(drumOptions.kaRightPin)) adc_gpio_init(drumOptions.kaRightPin);

	if(isValidPin(drumOptions.switchPin)) {
		gpio_init(drumOptions.switchPin);
		gpio_set_dir(drumOptions.switchPin, GPIO_IN);
		gpio_pull_up(drumOptions.switchPin);
	}

	cfg.donLeft.pin = drumOptions.donLeftPin;
	cfg.donLeft.thresh = drumOptions.donLeftThresh;
	cfg.donLeft.threshForce = drumOptions.donLeftThreshForce;

	cfg.donRight.pin = drumOptions.donRightPin;
	cfg.donRight.thresh = drumOptions.donRightThresh;
	cfg.donRight.threshForce = drumOptions.donRightThreshForce;

	cfg.kaLeft.pin = drumOptions.kaLeftPin;
	cfg.kaLeft.thresh = drumOptions.kaLeftThresh;
	cfg.kaLeft.threshForce = drumOptions.kaLeftThreshForce;

	cfg.kaRight.pin = drumOptions.kaRightPin;
	cfg.kaRight.thresh = drumOptions.kaRightThresh;
	cfg.kaRight.threshForce = drumOptions.kaRightThreshForce;

	cfg.switchPin = drumOptions.switchPin;
	cfg.hid2vpadFix = drumOptions.hid2vpadFix;

	pressed.a = false;
	pressed.b = false;
	pressed.left = false;
	pressed.right = false;
	pressed.l = false;
	pressed.r = false;
	pressed.plus = false;
}

void DrumAddon::preprocess()
{
}

// #define SET_GP_TO_0(mask, bit) ((mask & bit) && (mask ^= bit))

void DrumAddon::process()
{
	bool nofix = !cfg.hid2vpadFix;
	Gamepad * gamepad = Storage::getInstance().GetGamepad();

	if(isValidPin(cfg.switchPin) && !gpio_get(cfg.switchPin)) {
		if(isValidPin(cfg.donLeft.pin)) {
			uint16_t readDonLeft = readPin(cfg.donLeft.pin);
			if(readDonLeft > cfg.donLeft.threshForce) {
				if(!pressed.plus || nofix) {
					gamepad->state.buttons |= GAMEPAD_MASK_S2;
					pressed.plus = true;
				}
			} else if(readDonLeft > cfg.donLeft.thresh) {
				if(!pressed.b || nofix) {
					gamepad->state.buttons |= GAMEPAD_MASK_B1;
					pressed.b = true;
				}
			} else {
				pressed.plus = false;
				pressed.b = false;
			}
		}
		if(isValidPin(cfg.donRight.pin)) {
			uint16_t readDonRight = readPin(cfg.donRight.pin);
			if(readDonRight > cfg.donRight.thresh) {
				if(!pressed.a || nofix) {
					gamepad->state.buttons |= GAMEPAD_MASK_B2;
					pressed.a = true;
				}
			} else {
				pressed.a = false;
			}
		}

		if(isValidPin(cfg.kaLeft.pin)) {
			uint16_t readKaLeft = readPin(cfg.kaLeft.pin);
			if(readKaLeft > cfg.kaLeft.threshForce) {
				if(!pressed.l || nofix) {
					gamepad->state.buttons |= GAMEPAD_MASK_L1;
					pressed.l = true;
				}
			} else if(readKaLeft > cfg.kaLeft.thresh) {
				if(!pressed.left || nofix) {
					gamepad->state.dpad |= GAMEPAD_MASK_LEFT;
					pressed.left = true;
				}
			} else {
				pressed.left = false;
				pressed.l = false;
			}
		}
		if(isValidPin(cfg.kaRight.pin)) {
			uint16_t readKaRight = readPin(cfg.kaRight.pin);
			if(readKaRight > cfg.kaRight.threshForce) {
				if(!pressed.r || nofix) {
					gamepad->state.buttons |= GAMEPAD_MASK_R1;
					pressed.r = true;
				}
			} else if(readKaRight > cfg.kaRight.thresh) {
				if(!pressed.right || nofix) {
					gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
					pressed.right = true;
				}
			} else {
				pressed.right = false;
				pressed.r = false;
			}
		}
		return;
	}
	if(isValidPin(cfg.donLeft.pin)) {
		uint16_t readDonLeft = readPin(cfg.donLeft.pin);
		if(readDonLeft > cfg.donLeft.threshForce) {
			if(!pressed.right || nofix) {
				gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
				pressed.right = true;
			}
			if(!pressed.a || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_B2;
				pressed.a = true;
			}
		}
		else if(readDonLeft > cfg.donLeft.thresh) {
			if(!pressed.right || nofix) {
				gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
				pressed.right = true;
			}
		}
		else {
				pressed.right = false;
				pressed.a = false;
		}
	}
	if(isValidPin(cfg.donRight.pin)) {
		uint16_t readDonRight = readPin(cfg.donRight.pin);
		if(readDonRight > cfg.donRight.threshForce) {
			if(!pressed.a || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_B2;
				pressed.a = true;
			}
			if(!pressed.right || nofix) {
				gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
				pressed.right = true;
			}
		}
		else if(readDonRight > cfg.donRight.thresh) {
			if(!pressed.a || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_B2;
				pressed.a = true;
			}
		}
		else {
				pressed.a = false;
				pressed.right = false;
		}
	}

	if(isValidPin(cfg.kaLeft.pin)) {
		uint16_t readKaLeft = readPin(cfg.kaLeft.pin);
		if(readKaLeft > cfg.kaLeft.threshForce) {
			if(!pressed.l || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
				pressed.l = true;
			}
			if(!pressed.r || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_R1;
				pressed.r = true;
			}
		}
		else if(readKaLeft > cfg.kaLeft.thresh) {
			if(!pressed.l || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
				pressed.l = true;
			}
		}
		else {
				pressed.l = false;
				pressed.r = false;
		}
	}
	if(isValidPin(cfg.kaLeft.pin)) {
		uint16_t readKaRight = readPin(cfg.kaRight.pin);
		if(readKaRight > cfg.kaRight.threshForce) {
			if(!pressed.r || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_R1;
				pressed.r = true;
			}
			if(!pressed.l || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
				pressed.l = true;
			}
		}
		else if(readKaRight > cfg.kaRight.thresh) {
			if(!pressed.r || nofix) {
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
				pressed.r = true;
			}
		}
		else {
				pressed.r = false;
				pressed.l = false;
		}
	}
}
