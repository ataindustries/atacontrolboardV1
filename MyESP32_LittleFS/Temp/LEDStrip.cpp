#include "FastLED.h"
//#include "LEDStrip.h"

//Strip1
#define LED1_NUM_LEDS        10
#define LED1_LED_TYPE        WS2811
#define LED1_COLOR_ORDER     GRB
#define LED1_DATA_PIN        27
//#define LED1_CLK_PIN       4
#define LED1_VOLTS           12
#define LED1_MAX_MA          200

//Strip 2
#define LED2_NUM_LEDS        10
#define LED2_LED_TYPE        WS2811
#define LED2_COLOR_ORDER     GRB
#define LED2_DATA_PIN        26
//#define LED2_CLK_PIN       4
#define LED2_VOLTS           12
#define LED2_MAX_MA          200

CRGB gBackgroundColor = CRGB::Black; 

CRGB led1[LED1_NUM_LEDS];
CRGB led2[LED2_NUM_LEDS];

CLEDController *Strip1;
CLEDController *Strip2;

void Init_Strip1_Control_Task(void)
{
  //xTaskCreate(Strip1_Control_Task, "Strip1_Control_Task", 20000, NULL, 1, NULL);
  xTaskCreatePinnedToCore(Strip1_Control_Task, "Strip1_Control_Task", 20000, NULL, 1, NULL, 0);

}

void Init_Strip2_Control_Task(void)
{
  xTaskCreatePinnedToCore(Strip2_Control_Task, "Strip2_Control_Task", 20000, NULL, 1, NULL, 0);
}


void Strip1_Control_Task(void *parameters)
{
  Strip1 = &FastLED.addLeds<LED1_LED_TYPE, LED1_DATA_PIN>(led1, LED1_NUM_LEDS);
  Strip1->setCorrection(TypicalSMD5050);

  Serial.println("Strip1 Initialized...");

  for(;;){
    fill_solid(led1, LED1_NUM_LEDS, CRGB::Red);
    Strip1->showLeds(64);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    fill_solid(led1, LED1_NUM_LEDS, CRGB::Black);
    Strip1->showLeds(64);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //Serial.println("Strip1 tick..");
  }
}

void Strip2_Control_Task(void *parameters)
{
  Strip2 = &FastLED.addLeds<LED2_LED_TYPE, LED2_DATA_PIN>(led2, LED2_NUM_LEDS);
  Strip2->setCorrection(TypicalSMD5050);  

  Serial.println("Strip2 Initialized...");

  for(;;){
    fill_solid(led2, LED2_NUM_LEDS, CRGB::Blue);
    Strip2->showLeds(64);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    fill_solid(led2, LED2_NUM_LEDS, CRGB::Black);
    Strip2->showLeds(64);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //Serial.println("Strip2 tick..");
  }
}


