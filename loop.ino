void loop() {
  writeOutputs();

  if (isResetButtonPressed()) {
    reset();
    saveState();
    return;
  }
  if (halt) {
    pumpOn = false;
    return;
  }
  if (isPumpRunning()) {
    pumpOn = true;
    if (checkIfAlertIsNeeded()) {
      alert = true;
    }
    if (checkIfHaltIsNeeded()) {
      halt = true;
      saveState();
    }
    return;
  }
  if (alert) {
    halt = true;
    saveState();
  }
  pumpOn = false;
  lastTimestamp = millis();
}

void writeOutputs() {
  // Set LEDs:
  digitalWrite(YELLOW_LED_PIN, alert ? HIGH : LOW);
  digitalWrite(RED_LED_PIN, halt ? HIGH : LOW);
  digitalWrite(GREEN_LED_PIN, pumpOn ? HIGH : LOW);
  // Relay is on when LOW:
  digitalWrite(RELAY_PIN, halt ? HIGH : LOW);
}

bool isResetButtonPressed() {
  return digitalRead(RESET_BUTTON_PIN) == 0;
}

void reset() {
  lastTimestamp = millis();
  halt = false;
  pumpOn = false;
  alert = false;
}

bool isPumpRunning() {
  float currentReading = sensor.getCurrentAC(60);
  // Serial.println(String("I = ") + currentReading + " A");
  return currentReading > PUMP_CURRENT_THRESHOLD;
}

bool checkIfAlertIsNeeded() {
  return millis() > lastTimestamp + ALERT_THRESHOLD;
}

bool checkIfHaltIsNeeded() {
  return millis() > lastTimestamp + MAX_RUN_TIME;
}
