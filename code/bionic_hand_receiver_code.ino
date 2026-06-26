#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "esp_wifi.h"

const int servoPins[5] = {13, 14, 27, 26, 25};
Servo myServos[5];

typedef struct struct_message {
  int servoAngles[5];
} struct_message;

struct_message incomingData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataPtr, int len) {
  memcpy(&incomingData, incomingDataPtr, sizeof(incomingData));
  for (int i = 0; i < 5; i++) {
    myServos[i].write(incomingData.servoAngles[i]);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(0, WIFI_SECOND_CHAN_NONE);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  for (int i = 0; i < 5; i++) {
    myServos[i].setPeriodHertz(50);
    myServos[i].attach(servoPins[i], 500, 2400);
  }

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {}
