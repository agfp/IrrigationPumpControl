#include "ACS712.h"

//-----------------------
// PINS
//-----------------------
#define YELLOW_LED     12
#define RED_LED        11
#define GREEN_LED      10
#define RELAY          8
#define RESET_BUTTON   6
#define CURRENT_SENSOR A0
#define EMPTY_ANALOG   A5

//-----------------------
// System variables
//-----------------------
#define MAX_PUMP_RUN_MINUTES        10 // Minutes
#define CLEAN_FILTER_ALERT_MINUTES  8  // Minutes
#define PUMP_CURRENT_THRESHOLD      2  // Amperes

//-----------------------
// Global variables
//-----------------------
const uint16_t MAX_RUN_TIME = MAX_PUMP_RUN_MINUTES * 60 * 1000;
const uint16_t ALERT_THRESHOLD = CLEAN_FILTER_ALERT_MINUTES * 60 * 1000;

uint32_t _lastTimestamp = 0;
bool _error = false;
bool _pumpOn = false;
bool _alertThreshold = false;

ACS712 _sensor(ACS712_05B, CURRENT_SENSOR);
