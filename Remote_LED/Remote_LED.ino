#define LED_PIN 15


void setup() {
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
}

void loop() {
  for(int i=0;i<=255; i++){
    ledcWrite(0, i);
    Serial.println(i);
    delay(100);
  }
}
