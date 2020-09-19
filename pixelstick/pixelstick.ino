// Library includes
#include <SoftwareSerial.h>
#include <FastLED.h>

// Our headers
#include "palettes.h"

// Defining constants
#define RX_PIN 2
#define TX_PIN 3
#define CONTROL_PIN 4
#define LED_COUNT 30
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

// Global objects
SoftwareSerial bluetooth(RX_PIN, TX_PIN); // Serial connection with bluetooth module
CRGB strip[LED_COUNT];

// Global variables
String data, color;  // Incoming data and hexcode of single color
char mode;  // Light mode
uint8_t data_size, brightness;  // Common variables
uint8_t palette, palette_index, increase_rate, speed, effect;  // Gradient variables

// Structures
struct rgb
{
  byte red;
  byte green;
  byte blue;
};

// Function declarations
rgb hex_to_rgb(String hex);
void single_color(String hex, uint8_t brightness);
void gradient(uint8_t start_index, uint8_t palette_index, uint8_t brightness);

/* ------------------------------------------------------------ */

// Setup
void setup()
{
  delay(1000);
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, CONTROL_PIN, COLOR_ORDER>(strip, LED_COUNT).setCorrection(TypicalLEDStrip);

  increase_rate = 255 / LED_COUNT;
}

// loop
void loop()
{
  if(Serial.available())
  {
    data = Serial.readString();
    mode = data[0];
    data_size = (uint8_t) data.length();
    effect = 0;  // Reset effect

    if(mode == '0' && data_size == 1)  // Turn off
    {
      brightness = 0;
      FastLED.setBrightness(brightness);
      FastLED.show();
    }

    else if(mode == '1' && data_size == 8)  // Single color
    {
      color = data.substring(1, 7);
      brightness = (uint8_t) map(data.substring(7).toInt(), 0, 9, 30, 255);

      single_color(color, brightness);
    }

    else if(mode == '2' && data_size == 5)  // Gradient
    {
      palette_index = 0;
      palette = (uint8_t) data.substring(1, 2).toInt();
      brightness = (uint8_t) map(data.substring(2, 3).toInt(), 0, 9, 75, 255);
      effect = (uint8_t) data.substring(3, 4).toInt();
      speed = (uint8_t) map(data.substring(4).toInt(), 0, 9, 95, 5);

      gradient(palette_index, palette, brightness);
    }
  }

  if(effect == 1)
  {
    gradient(++palette_index, palette, brightness);
    FastLED.delay(speed);
  }
}

/* ------------------------------------------------------------ */

// Function definitons
rgb string_to_rgb(String hex)
{
  rgb color;

  long number = (long) strtol(&hex[0], NULL, 16);
  byte red = number >> 16;
  byte green = number >> 8 & 0xFF;
  byte blue = number & 0xFF;

  color.red = red;
  color.green = green;
  color.blue = blue;

  return color;
}

void single_color(String hex, uint8_t brightness)
{
  rgb color = string_to_rgb(hex);

  for(int i = 0; i < LED_COUNT; i++)
  {
    strip[i].r = color.red;
    strip[i].g = color.green;
    strip[i].b = color.blue;
  }

  FastLED.setBrightness(brightness);
  FastLED.show();
}

void gradient(uint8_t start_index, uint8_t palette_index, uint8_t brightness)
{
  for(int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = ColorFromPalette(palettes[palette_index], start_index , brightness, LINEARBLEND);
    start_index += increase_rate;
  }

  FastLED.setBrightness(brightness);
  FastLED.show();
}
