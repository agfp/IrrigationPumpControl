void loop() {
  setGeneralStatus();

  if (readResetButton()) {
    reset();
    return;
  }
  if (_error) {
    _pumpOn = false;
    return;
  }
  secondLoop();
}

void secondLoop() {
  if (readInput()) {
    _pumpOn = true;
    if (checkAlertInterval()) {
      _alertThreshold = true;
    }
    if (checkErrorInterval()) {
      _error = true;
    }
    return;
  } else {
    _pumpOn = false;
    _lastTimestamp = millis();
  }
}

void reset() {
  _lastTimestamp = millis();
  _error = false;
  _pumpOn = false;
  _alertThreshold = false;
}

bool readInput() {
  float currentReading = _sensor.getCurrentAC(60);
  // Serial.println(String("I = ") + currentReading + " A");
  return currentReading > PUMP_CURRENT_THRESHOLD;
}

bool checkAlertInterval() {
  return millis() > _lastTimestamp + ALERT_THRESHOLD;
}

bool checkErrorInterval() {
  if (millis() > _lastTimestamp + MAX_RUN_TIME) {
    _lastTimestamp = millis();
    return true;
  }
  return false;
}

void setGeneralStatus() {
  digitalWrite(RED_LED, _error ? HIGH : LOW);
  digitalWrite(RELAY, _error ? HIGH : LOW);
  digitalWrite(YELLOW_LED, _alertThreshold ? HIGH : LOW);
  digitalWrite(GREEN_LED, _pumpOn ? HIGH : LOW);
}

bool readResetButton() {
  return digitalRead(RESET_BUTTON) == 0;
}
