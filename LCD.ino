#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
// https://wokwi.com/projects/321525495180034642

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

// set the WiFi AP credentials to connect to
const char* ssid = "IoT_Test";
const char* ap_pass = "goodlife"; 

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
  lcd.setCursor(15, 1);
  lcd.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}


void setup(){
  Serial.begin(115200);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // create the heart character at location 0 (max 8 allowed)
  lcd.createChar(0, bus);
  lcd.createChar(1, clockico);

  // WiFi setup
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("WiFi ");

  Serial.println();
  WiFi.begin(ssid, ap_pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  delay(2500);
  lcd.clear();

}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // write custom character 0 to lcd
  lcd.write(0);
  lcd.setCursor(18, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.print("Destination:");
  lcd.setCursor(0, 1);
  lcd.print("126 Birmingham    04");
  lcd.setCursor(0, 3);
  lcd.print(WiFi.localIP());
}




















