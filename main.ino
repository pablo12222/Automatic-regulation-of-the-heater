#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

RTC_DS1307 rtc;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int ledPin1 = 13;
const int ledPin2 = 12; 
const int oneWireBus = 4; 
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

const int tempControlPin = 5; // Definiowanie pinu kontrolującego temperaturę

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(115200);

#ifndef ESP32
  while (!Serial);
#endif

  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT);
  pinMode(tempControlPin, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) delay(10);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  sensors.begin();


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    if (temperatureC == DEVICE_DISCONNECTED_RAW) {
      Serial.println("Błąd odczytu temperatury!");
    }
else{
// Odczyt aktualnej daty i czasu
    DateTime now = rtc.now();
    int month = now.month();  
// Logika sterowania grzejnikiem w sezonie grzewczym
    bool isHeatingSeason = (month >= 10) || (month <= 4); // Październik do Kwietnia

  if (isHeatingSeason) {
     // Ustawienie pinu na wysoki poziom, jeśli temperatura jest poniżej 19 stopni
    // i na niski poziom, jeśli temperatura przekracza 24 stopnie
    if (temperatureC < 19.5) {
      digitalWrite(tempControlPin, HIGH);
      digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, HIGH);  
    } else if (temperatureC > 25) {
      digitalWrite(tempControlPin, LOW);
      digitalWrite(ledPin1,HIGH); 
      digitalWrite(ledPin2, LOW); 
    }
  }
}
    DateTime now = rtc.now();

    display.clearDisplay();
    display.setCursor(0,0);

    display.print(daysOfTheWeek[now.dayOfTheWeek()]);
    display.print(", ");
    display.print(now.day(), DEC);
    display.print('/');
    display.print(now.month(), DEC);
    display.print('/');
    display.print(now.year(), DEC);
    display.print(" \n\n");
    display.print(now.hour(), DEC);
    display.print(':');
    display.print(now.minute(), DEC);
    display.print(':');
    display.println(now.second(), DEC);

    display.setCursor(0, 30);
    if (temperatureC != DEVICE_DISCONNECTED_RAW) {
      display.print("Temp: ");
      display.print(temperatureC);
      display.println(" C");
    } else {
      display.println("Błąd czujnika!");
    }

    display.display();
  }
}
