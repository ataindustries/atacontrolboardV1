#include "NeoBusLEDStrip.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include <NeoPixelBus.h>

#define STRIP1_DATA_PIN     27
#define STRIP1_DATA_SIZE    10

#define STRIP2_DATA_PIN     26
#define STRIP2_DATA_SIZE    10

#define colorSaturation 64

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor blueBright(0,0, 128);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

#define STRIP1_ENABLED 
#define STRIP2_ENABLED


#ifdef STRIP1_ENABLED
//NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip1(10, STRIP1_DATA_PIN);
//NeoPixelBus<NeoRgbFeature, NeoEsp32Rmt0800KbpsMethod> strip1(10, STRIP1_DATA_PIN);
NeoPixelBus<NeoRgbFeature, NeoEsp32I2s0800KbpsMethod> strip1(10, STRIP1_DATA_PIN);
//NeoPixelBus<NeoRgbFeature, NeoEsp32Rmt0800KbpsMethod> strip1(10, STRIP1_DATA_PIN);
#endif

#ifdef STRIP2_ENABLED
//NeoPixelBus<NeoRgbFeature, NeoEsp32Rmt0800KbpsMethod> strip2(10, STRIP2_DATA_PIN);
NeoPixelBus<NeoRgbFeature, NeoEsp32I2s1800KbpsMethod> strip2(10, STRIP2_DATA_PIN);
//NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip2(10, STRIP2_DATA_PIN);
#endif

void Init_Strip1_Control_Task(void)
{
    xTaskCreatePinnedToCore(Strip1_Control_Task, "Strip1_Control_Task", 20000, NULL, 1, NULL, 0);
    //vTaskSuspend(Strip1_Task_Handler);
}

void Init_Strip2_Control_Task(void)
{
  xTaskCreatePinnedToCore(Strip2_Control_Task, "Strip2_Control_Task", 20000, NULL, 1, NULL, 1);
}

void Strip1_Control_Task(void *parameters)
{
  #ifdef STRIP1_ENABLED
  strip1.Begin();
  strip1.Show();
  #endif
  Serial.println("Strip1 Initialized...");

  for(;;){
    #ifdef STRIP1_ENABLED
    for(int x = 0; x < STRIP1_DATA_SIZE; x++){
      strip1.SetPixelColor(x, blue);
    }
    strip1.Show();
    #endif
    vTaskDelay(500 / portTICK_PERIOD_MS);

    #ifdef STRIP1_ENABLED
    for(int x = 0; x < STRIP1_DATA_SIZE; x++){
      strip1.SetPixelColor(x, blueBright);
    }
    strip1.Show();
    #endif
    vTaskDelay(500 / portTICK_PERIOD_MS);

    //Serial.println("Strip1 tick..");
  }

  #ifndef STRIP1_ENABLED

  #endif
}

void Strip2_Control_Task(void *parameters)
{
  #ifdef STRIP2_ENABLED
  strip2.Begin();
  strip2.Show();
  Serial.println("Strip2 Initialized...");
  #endif

  for(;;){
    #ifdef STRIP2_ENABLED
    for(int x = 0; x < STRIP2_DATA_SIZE; x++){
      strip2.SetPixelColor(x, red);
    }
    strip2.Show();
    #endif

    vTaskDelay(800 / portTICK_PERIOD_MS);

    #ifdef STRIP2_ENABLED
    for(int x = 0; x < STRIP2_DATA_SIZE; x++){
      strip2.SetPixelColor(x, white);
    }
    strip2.Show();
    #endif

    vTaskDelay(800 / portTICK_PERIOD_MS);
    //Serial.println("Strip1 tick..");
  }
}