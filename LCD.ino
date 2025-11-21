#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
// https://wokwi.com/projects/321525495180034642

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

// set the WiFi AP credentials to connect to
const char* ssid = "IoT_Test";
const char* ap_pass = "goodlife"; 

WiFiUDP ntpUDP;
// setup NTP: NTP via UDP, NTP pool, offset(s), update interval(ms)
NTPClient timeClient(ntpUDP);
//NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

// Custom characters
byte bus[8] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B11111,
  B10101,
  B11111,
  B01010
};

byte clockico[8] = {
  B00000,
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000
};

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  lcd.setCursor(19, 0);
  lcd.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void displayTime() {
    int hour = timeClient.getHours();
    int minutes = timeClient.getMinutes();

    lcd.setCursor(0, 0);
    lcd.println(timeClient.getFormattedTime());

    lcd.setCursor(0, 2);
    lcd.print(hour);
    lcd.print(":");
    lcd.print(minutes);
}

void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();  // turn on LCD backlight
  // create the bus character at location 0 (max 8 allowed)
  lcd.createChar(0, bus);
  lcd.createChar(1, clockico);
  // WiFi setup
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");

  Serial.println();
  WiFi.begin(ssid, ap_pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    spinner();
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  lcd.setCursor(0, 1);
  lcd.print("Fetching time");
  timeClient.begin();
  timeClient.update();
  lcd.setCursor(0, 2);
  lcd.print("Done!");
  lcd.clear();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // write custom character 0 to lcd
  // lcd.write(0);
  // lcd.setCursor(18, 0);
  // lcd.write(1);
  // lcd.setCursor(4, 0);
  // lcd.print("Destination:");
  // lcd.setCursor(0, 1);
  // lcd.print("126 Birmingham    04");
  // lcd.setCursor(0, 3);
  // lcd.print(WiFi.localIP());
  displayTime();
  delay(250);
}




















