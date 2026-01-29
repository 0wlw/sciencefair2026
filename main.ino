#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensor_pin = A0;
const int GLED_pin = 3;
const int BLED_pin = 2;

int delaytime = 100;
int startdelay = 3000;

float value;

float bac = 0;
float bdc = 1024;
float gac = 0;
float gdc = 1024;

float bRatio;
float gRatio;
float R;
float coeff = 10.91078876;
float intercept = 86.26779908;

void setup() {
  Serial.begin(9600);
  //display.setTextSize(3); 
  //display.setTextColor(SSD1306_WHITE);
  //display.setCursor(10, 0);
  //display.println("hello");
  //display.display();
  delay(startdelay);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    digitalWrite(BLED_pin, HIGH);
    delay(delaytime);
    value = analogRead(sensor_pin);
    digitalWrite(BLED_pin, LOW);
    if (value > bac && i > 1) {
      bac = value;
    }
    if (value < bdc) {
      bdc = value;
    }

    Serial.print(millis() - startdelay);
    Serial.print(",");
    Serial.print("B,");
    Serial.print(value);
    Serial.print(",");
    Serial.print(bac);
    Serial.print(",");
    Serial.println(bdc);
    ///

    digitalWrite(GLED_pin, HIGH);
    delay(delaytime);
    value = analogRead(sensor_pin);
    digitalWrite(GLED_pin, LOW);
    if (value > gac) {
      gac = value;
    }
    if (value < gdc) {
      gdc = value;
    }
    
    Serial.print(millis() - startdelay);
    Serial.print(",");
    Serial.print("G,");
    Serial.print(value);
    Serial.print(",");
    Serial.print(gac);
    Serial.print(",");
    Serial.println(gdc);
  }
  bRatio = bac / bdc;
  gRatio = gac / gdc;
  R = bRatio / gRatio;
  Serial.print("#######################################     ");
  Serial.print(bRatio, 10);
  Serial.print(",");
  Serial.print(gRatio, 10);
  Serial.print(",");
  Serial.println(R, 10);
  Serial.println(R * coeff + intercept);
  delay(10000);
}

void oledprint(int number) {
  display.clearDisplay();

  display.setTextSize(3); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(number);
  display.display();      
}
