#include "DHTesp.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "icons.h"

// DHT Setup
const int DHT_PIN = 15;
DHTesp dhtSensor;

// OLED Setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, Aaqib!");
  // DHT Setup
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Starting Weather Monitoring System ...");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  // Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  // Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  // Serial.println("---");
  // delay(2000); // Wait for a new reading from the sensor (DHT22 has ~0.5Hz sample rate)

  String extra_space = "";
  if (data.temperature >=0 && data.temperature < 10.0)
  {
    extra_space = " ";
  }
  const String temp = extra_space + String(data.temperature, 1) + "C";
  const String humid = String(data.humidity, 1) + "%";

  display.clearDisplay();

  display.drawBitmap(0, 2, TemperatureIcon, 24, 24, WHITE);
  // display.drawBitmap(0, 26, HumidityIcon, 24, 24, WHITE);
  display.drawBitmap(0, 40, HumidityIcon, 24, 24, WHITE);
  
  display.setCursor(38,2);
  display.println(temp);
  // display.setCursor(0,35);
  display.setCursor(38,40);
  display.println(humid);

  display.display();
  delay(2000); 
  
}
