#include "ACS712.h"

//-----------------------
// PINS
//-----------------------
#define YELLOW_LED_PIN     12
#define RED_LED_PIN        11
#define GREEN_LED_PIN      10
#define RELAY_PIN          8
#define RESET_BUTTON_PIN   6
#define CURRENT_SENSOR_PIN A0
#define EMPTY_ANALOG_PIN   A5

//-----------------------
// System variables
//-----------------------
#define PUMP_RUN_TIME          14  // Minutes
#define CLEAN_FILTER_ALERT     11  // Minutes
#define PUMP_CURRENT_THRESHOLD 1.5 // Amperes

//-----------------------
// Global variables
//-----------------------
const uint32_t MAX_RUN_TIME = PUMP_RUN_TIME * 60UL * 1000UL;
const uint32_t ALERT_THRESHOLD = CLEAN_FILTER_ALERT * 60UL * 1000UL;

uint32_t lastTimestamp = 0;
bool alert = false;
bool halt = false;
bool pumpOn = false;

ACS712 sensor(ACS712_05B, CURRENT_SENSOR_PIN);
