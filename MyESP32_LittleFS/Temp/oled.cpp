#include <Arduino.h>

#include "oled.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


#define NUMFLAKES 10 // Number of snowflakes in the animation example

/*
#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] =
	{B00000000, B11000000,
	 B00000001, B11000000,
	 B00000001, B11000000,
	 B00000011, B11100000,
	 B11110011, B11100000,
	 B11111110, B11111000,
	 B01111110, B11111111,
	 B00110011, B10011111,
	 B00011111, B11111100,
	 B00001101, B01110000,
	 B00011011, B10100000,
	 B00111111, B11100000,
	 B00111111, B11110000,
	 B01111100, B11110000,
	 B01110000, B01110000,
	 B00000000, B00110000};
*/

void Init_Oled_Task(void)
{
	xTaskCreatePinnedToCore(Oled_Task, "OLED_Task", 15000, NULL, 1, NULL, 0);
}

void Oled_Task(void *parameters)
{
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
	{
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			; // Don't proceed, loop forever
	}

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	display.setRotation(2); // 2 = 180deg
	display.display();
	vTaskDelay(2000); // Pause for 2 seconds

	// Clear the buffer
	display.clearDisplay();

	// Draw a single pixel in white
	//display.drawPixel(10, 10, WHITE);

	// Show the display buffer on the screen. You MUST call display() after
	// drawing commands to make them visible on screen!
	//display.display();
	//vTaskDelay(2000);

	int cnt = 0;
	for (;;)
	{
		/*
		display.clearDisplay();

		for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2)
		{
			display.drawCircle(display.width() / 2, display.height() / 2, i, WHITE);
			display.display();
			vTaskDelay(1);
		}

		vTaskDelay(2000);
*/

		// *****************
		display.clearDisplay();

		display.setTextSize(2);
		display.setTextColor(WHITE);
		display.setCursor(0, 20);
		// Display static text
		display.print("Cnt: "); 
		display.println(cnt);
		display.display();

		vTaskDelay(1000);
		cnt++;
	}
}
