#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED_PIN 15
#define LED 22
#define batteryPin 34

String message = "";
char incomingChar;

int sensorValue = 0;
float calibration = 0.2;
int bat_percentage;

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis2 = 0;
const long interval2 = 500;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP_bl"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
  pinMode(LED, OUTPUT);
}

void loop() {
  blink();
  batteryCheck();
}



void led_control(){
  for(int i=0;i<=255; i++)
  {
    ledcWrite(0, i);
    Serial.println(i);
    delay(100);
  }
}

void blink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if (ledState == LOW){
      ledState = HIGH;  
    }else{
      ledState = LOW;  
    }
    digitalWrite(LED, ledState);
  }  
}

void batteryCheck(){
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2){
    previousMillis2 = currentMillis2;
    sensorValue = analogRead(batteryPin);
    Serial.print("sensor : ");
    Serial.println(sensorValue);
  
    float voltage = (((sensorValue * 3.3) / 4095) * 2 + calibration);
  
    Serial.print("VOLT : ");
    Serial.print(voltage);
    Serial.println("V"); 

    
    bat_percentage = (float)map((int)(voltage * 1000), 2500, 4200, 0, 100);
  
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
}
