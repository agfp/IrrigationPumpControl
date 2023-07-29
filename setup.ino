void setup() {
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(RESET_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  int zero = _sensor.calibrate();
  // Serial.println(String("Zero point for this sensor = ") + zero);
}