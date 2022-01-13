#include <Math.h>
#define LED_PIN 15
#define LED 22
#define batteryPin 34

int sensorValue = 0;
float calibration = 0.2;
int bat_percentage;

void setup() {
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  sensorValue = analogRead(batteryPin);
  Serial.print("sensor : ");
  Serial.println(sensorValue);
  
  float voltage = (((sensorValue * 3.3) / 4095) * 2 + calibration);
  
  Serial.print("VOLT : ");
  Serial.print(voltage);
  Serial.println("V"); 

  Serial.println(voltage * 10);
  bat_percentage = (float)map((int)(voltage * 100), 280, 420, 0, 100);
  
  if (bat_percentage >= 100){
    bat_percentage = 100;  
  }
  if (bat_percentage <= 0){
    bat_percentage = 1;
  }
  Serial.print("percentage : ");
  Serial.print(bat_percentage);
  Serial.println("%");
}

void led_control(){
  for(int i=0;i<=255; i++)
  {
    ledcWrite(0, i);
    Serial.println(i);
    delay(100);
  }
}
