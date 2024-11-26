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

void DrumAddon::setup()
{
    const DrumOptions& drumOptions = Storage::getInstance().getAddonOptions().drumOptions;

	if(isValidPin(drumOptions.donLeftPin)) adc_gpio_init(drumOptions.donLeftPin);
	if(isValidPin(drumOptions.donRightPin)) adc_gpio_init(drumOptions.donRightPin);
	if(isValidPin(drumOptions.kaLeftPin)) adc_gpio_init(drumOptions.kaLeftPin);
	if(isValidPin(drumOptions.kaRightPin)) adc_gpio_init(drumOptions.kaRightPin);

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
}

void DrumAddon::preprocess()
{
}

void DrumAddon::process()
{
	Gamepad * gamepad = Storage::getInstance().GetGamepad();

	if(isValidPin(cfg.donLeft.pin)) {
		uint16_t readDonLeft = readPin(cfg.donLeft.pin);
		if(readDonLeft > cfg.donLeft.thresh)
				gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
		if(readDonLeft > cfg.donLeft.threshForce)
				gamepad->state.buttons |= GAMEPAD_MASK_B2;
	}
	if(isValidPin(cfg.donRight.pin)) {
		uint16_t readDonRight = readPin(cfg.donRight.pin);
		if(readDonRight > cfg.donRight.thresh)
				gamepad->state.buttons |= GAMEPAD_MASK_B2;
		if(readDonRight > cfg.donRight.threshForce)
				gamepad->state.dpad |= GAMEPAD_MASK_RIGHT;
	}

	if(isValidPin(cfg.kaLeft.pin)) {
		uint16_t readKaLeft = readPin(cfg.kaLeft.pin);
		if(readKaLeft > cfg.kaLeft.thresh)
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
		if(readKaLeft > cfg.kaLeft.threshForce)
				gamepad->state.buttons |= GAMEPAD_MASK_R1;
	}
	if(isValidPin(cfg.kaRight.pin)) {
		uint16_t readKaRight = readPin(cfg.kaRight.pin);
		if(readKaRight > cfg.kaRight.thresh)
				gamepad->state.buttons |= GAMEPAD_MASK_R1;
		if(readKaRight > cfg.kaRight.threshForce)
				gamepad->state.buttons |= GAMEPAD_MASK_L1;
	}
}
