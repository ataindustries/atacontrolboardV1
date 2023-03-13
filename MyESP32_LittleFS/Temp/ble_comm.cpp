#include "ble_comm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Arduino.h>
//#include <ArduinoJson>
//#include <SPIFFS.h>


#include "BluetoothSerial.h"

void BTcallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);

BluetoothSerial SerialBT;

void Init_BLE_Task(void)
{
    xTaskCreatePinnedToCore(BLE_Task, "BLE_TASK", 10000, NULL, 1, NULL, 0);
}

void OnSerialBTData(BluetoothSerialDataCb cb){

}

void Initialize_BLE_Serial()
{
    SerialBT.setTimeout(250);
    SerialBT.register_callback(BTcallback);

    if(!SerialBT.begin("ATA-COMM")){
        Serial.println("An error occurred initializing Bluetooth");
    }else{
        Serial.println("Bluetooth initialized");
    }

    vTaskDelay(500);
}


void BLE_Task (void * parameters)
{
    char RxBuff[64];
    int bytesRead;

    Initialize_BLE_Serial();

	for(;;){
        if (Serial.available()) {
            SerialBT.write(Serial.read());
        }
        if (SerialBT.available()) {
            bytesRead = SerialBT.readBytesUntil('\n', RxBuff, sizeof(RxBuff));
            Serial.write(RxBuff, bytesRead);
            SerialBT.print("Got it....");
        }
        vTaskDelay(20);
	}
}

void BTcallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
  }
}



