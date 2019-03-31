#define BLYNK_PRINT Serial

#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

BlynkTimer timer;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(60, 2, NEO_GRBW + NEO_KHZ800);

int white, red, green, blue, modus;
int b = 39;
int w = 15;
int p = 3;
int z = 1;
int statenow[61][4];
int statethen[61][4];
int now;
float spe = 0.1;

void setup()
{
  Serial.begin(230400);
  pixels.begin();
  Blynk.begin("78ba576f1d0e47489a2368cc50678032", "FRITZ!Box Scheufele", "Scheufele2016", "scheufele.ddns.net", 8080);
  timer.setInterval(30L, updateLED);
  timer.setInterval(100L, colorcalc);
  timer.setInterval(30L, transition);
}

void colorcalc() {
  if (modus == 3) {
    float fred = (float)red / 255;
    float fgreen = (float)green / 255;
    float fblue = (float)blue / 255;
    //Serial.println("calc");
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      z = abs(1 + (1) ^ ((i - p) ^ 2));
      if (z == 0) {
        z = 1;
      }
      float temp = b / z;
      statethen[i][0] = temp * fred;
      statethen[i][1] = temp * fgreen;
      statethen[i][2] = temp * fblue;
    }
  }
}

void transition() {
  //Serial.println("transitoin");
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    statenow[i][0] = statenow[i][0] + spe * ((float)statethen[i][0] - (float)statenow[i][0]);
    statenow[i][1] = statenow[i][1] + spe * ((float)statethen[i][1] - (float)statenow[i][1]);
    statenow[i][2] = statenow[i][2] + spe * ((float)statethen[i][2] - (float)statenow[i][2]);
    statenow[i][3] = statenow[i][3] + spe * ((float)statethen[i][3] - (float)statenow[i][3]);
  }
}

void updateLED() {
  //Serial.println("updateLED");
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, pixels.Color(statenow[i][0], statenow[i][1], statenow[i][2], statenow[i][3]));
    }
    pixels.show();
  }
  if (modus == 3) {
    for (int i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, pixels.Color(statenow[i][0], statenow[i][1], statenow[i][2], statenow[i][3]));
    }
    pixels.show();
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
  modus = param.asInt();
  if (modus == 1) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0));
    }
    pixels.show();
  }
}

BLYNK_WRITE(V1)
{
  red = param.asInt();
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    statethen[i][0] = red;
  }
}

BLYNK_WRITE(V2)
{
  green = param.asInt();
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    statethen[i][1] = green;
  }
}

BLYNK_WRITE(V3)
{
  blue = param.asInt();
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    statethen[i][2] = blue;
  }
}

BLYNK_WRITE(V4)
{
  white = param.asInt();
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    statethen[i][3] = white;
  }
}

BLYNK_WRITE(V5)
{
  spe = (float)param.asInt() / 100;
}

BLYNK_WRITE(V6)
{
  b = param.asInt();
}

BLYNK_WRITE(V7)
{
  p = param.asInt();
}

BLYNK_WRITE(V8)
{
  w = param.asInt();
}
