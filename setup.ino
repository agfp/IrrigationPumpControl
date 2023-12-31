void setup() {
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  int zero = sensor.calibrate();
  Serial << "Zero point for this sensor = " << zero << endl;
  // Relay starts turned off by default
  digitalWrite(RELAY_PIN, HIGH);
  loadState();
  runLedTest();
}

void runLedTest() {
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(2000);
}
