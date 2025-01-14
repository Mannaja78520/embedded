#include <Arduino.h>
#include <Wire.h>  // Include Arduino Wire library for I2C communication
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include "RTClib.h"
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

void setup()
{
    lcd.begin();
    lcd.backlight();
}

void loop()
{
    // Display Hello, World! with the cursor
    lcd.print("     Hello, World!"); // Display the message
    lcd.setCursor(5, 1); // Move the cursor to the second row, after the message
    lcd.blink(); // Start blinking the cursor

    delay(2000); // Keep the cursor blinking for 2 seconds

    lcd.clear(); // Clear the display

    //Autoscroll
    lcd.print("     Hello, World!"); // You can make spaces using well... spaces
    lcd.setCursor(5, 1); // Or setting the cursor in the desired position.
    delay(500);
    lcd.setCursor(5, 0);
    lcd.setCursor(10, 1);
    lcd.autoscroll();

    for (int i = 0; i < 10; i++)
    {
        lcd.print(i);
        delay(200);
    }

    lcd.noAutoscroll();
    lcd.clear();

    // Scroll left and right
    lcd.setCursor(10, 0);
   
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollDisplayLeft();
        delay(200);
    }
    lcd.clear();
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollDisplayRight();
        delay(200);
    }
    lcd.clear();

    //Cursor
    lcd.setCursor(0, 0);
    lcd.cursor();
    delay(3000);
    lcd.clear();

    //Cursor blink
    lcd.setCursor(0, 0);
    lcd.blink();
    delay(3000);
    lcd.clear();

    //Blink without cursor
    lcd.setCursor(0, 0);
    lcd.noCursor();
    delay(3000);
    lcd.noBlink();
    lcd.clear();
}
