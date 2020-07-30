/* 

* Arduino weather station with ST7735 color TFT display (128x160 pixel) and 

*   BME280 barometric pressure, temperature & humidity sensor. 

* This is a free software with NO WARRANTY. 

* https://simple-circuit.com/ 

*/ 

  

#include <Adafruit_GFX.h>      // include Adafruit graphics library 

#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library 

#include <Adafruit_BME280.h>   // include Adafruit BME280 sensor library 

#include <SPI.h> 

  

#define TFT_CS     10 

#define TFT_RST    -1  // you can also connect this to the Arduino reset 

                      // in which case, set this #define pin to -1! 

#define TFT_DC     8 

  

// Color Definitions 

#define RED 0xF800 

  

// initialize ST7735 TFT library 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); 

  

// define device I2C address: 0x76 or 0x77 (0x77 is library default address) 

#define BME280_I2C_ADDRESS  0x77 

  

Adafruit_BME280  bme280;  // initialize Adafruit BME280 library 

  

void setup(void) 

{ 

  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab 

  tft.fillScreen(ST7735_BLACK);  // fill screen with black color 

  tft.drawFastHLine(0, 30,  tft.width(), ST7735_WHITE);   // draw horizontal white line at position (0, 30) 

  

  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  // set text color to white and black background 

  tft.setTextSize(1);                 // text size = 1 

  tft.setCursor(4, 4);               // move cursor to position (4, 0) pixel 

  tft.print("BERGIN'S AWESOME"); 

  tft.setCursor(19, 15);              // move cursor to position (19, 15) pixel 

  tft.print("WEATHER JAWN"); 

  

  // initialize the BME280 sensor 

  if( bme280.begin(BME280_I2C_ADDRESS) == 0 ) 

  {  // connection error or device address wrong! 

    tft.setTextColor(ST7735_RED, ST7735_BLACK);   // set text color to red and black background 

    tft.setTextSize(2);         // text size = 2 

    tft.setCursor(5, 76);       // move cursor to position (5, 76) pixel 

    tft.print("Connection"); 

    tft.setCursor(35, 100);     // move cursor to position (35, 100) pixel 

    tft.print("Error"); 

    while(1);  // stay here 

  } 

  

  // tft.drawFastHLine(0, 76,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 76) 

  // tft.drawFastHLine(0, 122,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 122) 

  tft.setTextColor(ST7735_RED, ST7735_BLACK);     // set text color to red and black background 

  //tft.setCursor(25, 39);              // move cursor to position (25, 39) pixel 

  tft.setCursor(25, 35); 

  tft.print("TEMPERATURE ="); 

  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // set text color to cyan and black background 

  //tft.setCursor(34, 85);              // move cursor to position (34, 85) pixel 

  tft.setCursor(34, 67); 

  tft.print("HUMIDITY ="); 

  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);  // set text color to green and black background 

// tft.setCursor(34, 131);              // move cursor to position (34, 131) pixel 

  tft.setCursor(34, 99); 

  tft.print("PRESSURE ="); 

  tft.setTextSize(2);                 // text size = 2 

  

} 

  

// main loop 

void loop() 

{ 

  char _buffer[8]; 

  // read temperature, humidity and pressure from the BME280 sensor 

  

  float temp_c = bme280.readTemperature();    // get temperature in °C 

  float temp = ((temp_c * 1.8) + 32);       //convert C to F 

  float humi = bme280.readHumidity();       // get humidity in rH% 

  float pres = bme280.readPressure();       // get pressure in Pa 

  

  // print temperature (in °F) 

  if(temp < 0)    // if temperature < 0 

    sprintf( _buffer, "-%02u.%02u", (int)abs(temp), (int)(abs(temp) * 100) % 100 ); 

  else            // temperature >= 0 

    sprintf( _buffer, " %02u.%02u", (int)temp, (int)(temp * 100) % 100 ); 

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);  // set text color to yellow and black background 

  //tft.setCursor(11, 54); 

  tft.setCursor(11, 45); 

  tft.print(_buffer); 

//  tft.drawCircle(89, 56, 2, ST7735_YELLOW);  // print degree symbol ( ° ) 

//  tft.setCursor(95, 54); 

tft.drawCircle(89, 47, 2, ST7735_YELLOW);  // print degree symbol ( ° ) 

  tft.setCursor(95, 45); 

  tft.print("F"); 

  

  // 2: print humidity 

  sprintf( _buffer, "%02u.%02u %%", (int)humi, (int)(humi * 100) % 100 ); 

  tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);  // set text color to magenta and black background 

  //tft.setCursor(23, 100); 

  tft.setCursor(23, 77); 

  tft.print(_buffer); 

  

  // 3: print pressure (in hPa) 

  sprintf( _buffer, "%04u.%02u", (int)(pres/100), (int)((uint32_t)pres % 100) ); 

  tft.setTextColor(0xFD00, ST7735_BLACK);  // set text color to orange and black background 

//  tft.setCursor(3, 146); 

  tft.setCursor(3, 109); 

  tft.print(_buffer); 

  tft.setCursor(91, 109); 

  tft.print("hPa"); 

  

  delay(1000);    // wait a second 

  

} 
