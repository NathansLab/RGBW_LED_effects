#define BLYNK_PRINT Serial

#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

BlynkTimer timer;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(20, 2, NEO_GRBW + NEO_KHZ800);

int white, red, green, blue, modus;
int b = 39;
int w = 15;
int p = 3;
float z = 0.1;
int statenow[61][4];
int statethen[61][4];
int now;
int spe = 1;

void setup()
{
  Serial.begin(230400);
  pixels.begin();
  Blynk.begin("78ba576f1d0e47489a2368cc50678032", "FRITZ!Box Scheufele", "Scheufele2016", "scheufele.ddns.net", 8080);
  timer.setInterval(300L, updateLED);
  timer.setInterval(1000L, colorcalc);
  //timer.setInterval(500L, whiteupdate);
}

void colorcalc() {
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    Serial.println("calc");
    z = 1 + (1 + (1 / w)) ^ ((i - p) ^ 2);
    if (z == 0) {
      z++;
    }
    statenow[i][0] = b / z;
    Serial.println(b / z);
  }
}

void updateLED() {
  now = millis();
  now = (now / 10000) * spe;
  Serial.println("updateLED");
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue, white));
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
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue, white));
    }
    pixels.show();
  }
}

BLYNK_WRITE(V2)
{
  green = param.asInt();
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue, white));
    }
    pixels.show();
  }
}

BLYNK_WRITE(V3)
{
  blue = param.asInt();
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue, white));
    }
    pixels.show();
  }
}

BLYNK_WRITE(V4)
{
  white = param.asInt();
  if (modus == 2) {
    for (int i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue, white));
    }
    pixels.show();
  }
}

BLYNK_WRITE(V5)
{
  spe = param.asInt();
}

BLYNK_WRITE(V6)
{
  b = param.asInt();
}
