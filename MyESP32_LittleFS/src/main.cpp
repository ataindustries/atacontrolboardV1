#include <Arduino.h>
#include <LittleFS.h>
#include "fileSystem.h"

const int BoardLED1 = 2;
const int BoardLED2 = 18;
int buzzerPin = 25;

void setup() {
  Serial.begin(115200); 

  pinMode(BoardLED1, OUTPUT);
  pinMode(BoardLED2, OUTPUT);

  Init_File_System();
}

void printSystemInfo(void){
  Serial.print("CPU Model: "); Serial.println(ESP.getChipModel());
  Serial.print("CPU Flash Size: "); Serial.println(ESP.getFlashChipSize());
}

void printTaskInfo(void){
  //uxTaskGetSystemState()
}

void loop() {

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}