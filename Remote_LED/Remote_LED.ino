#define LED_PIN 15
#define LED 34


void setup() {
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println("HIGH");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LOW");
  delay(1000);
}

void led_control(){
  for(int i=0;i<=255; i++)
  {
    ledcWrite(0, i);
    Serial.println(i);
    delay(100);
  }
}
