#include <esp_now.h>
#include <WiFi.h>
#include "esp_wifi.h"

uint8_t broadcastAddress[] = {0x80, 0xF3, 0xDA, 0x41, 0x44, 0x08};
const int potPins[5] = {32, 36, 35, 34, 33};

typedef struct struct_message {
  int servoAngles[5];
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
}

int readAvg(int pin) {
  long sum = 0;
  for (int i = 0; i < 16; i++) sum += analogRead(pin);
  return sum / 16;
}

int prevAngles[5] = {90, 90, 90, 90, 90};

int smooth(int prev, int next) {
  return (prev * 0.7) + (next * 0.3);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(0, WIFI_SECOND_CHAN_NONE);
  analogSetAttenuation(ADC_11db);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  int newAngles[5];
  newAngles[0] = map(readAvg(potPins[0]), 0, 759, 0, 180);      // pin 32
  newAngles[1] = map(readAvg(potPins[1]), 0, 523, 0, 180);      // pin 36
  newAngles[2] = map(readAvg(potPins[2]), 17, 833, 0, 180);     // pin 35
  newAngles[3] = map(readAvg(potPins[3]), 0, 1000, 0, 180);     // pin 34
  newAngles[4] = map(readAvg(potPins[4]), 300, 1000, 0, 180);   // pin 33

  for (int i = 0; i < 5; i++) {
    newAngles[i] = constrain(newAngles[i], 0, 180);
    myData.servoAngles[i] = smooth(prevAngles[i], newAngles[i]);
    prevAngles[i] = myData.servoAngles[i];
  }

  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(20);
}
