#include <GxEPD.h>
#include <GxGDEM029T94/GxGDEM029T94.h>   
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>  
#include <SPI.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <SD.h>

#define CS1   5   
#define DC1   22  
#define RSET1 21  
#define BUSY1 4  

#define CS2   15  
#define DC2   2   
#define RSET2 0  
#define BUSY2 16  

#define MOSI 23 
#define SCLK 18  


GxIO_Class io1(SPI, CS1, DC1, RSET1);
GxEPD_Class display1(io1, RSET1, BUSY1);

GxIO_Class io2(SPI, CS2, DC2, RSET2);
GxEPD_Class display2(io2, RSET2, BUSY2);

const char TextBsp[] = "Irgendein Text";

int cnt;

void setup() {
  Serial.begin(9600);
  
  SPI.begin(SCLK, MISO, MOSI);
  
  display1.init();
  display2.init();
}

void loop() {
  display1.setRotation(1);
  display1.fillScreen(GxEPD_WHITE);
  display1.setTextColor(GxEPD_BLACK);
  display1.setFont(&FreeMonoBold9pt7b);
  display1.setCursor(10, 30);
  display1.println("sheppard semiconductor systems");
  display1.setFont(&FreeMonoBold12pt7b);
  display1.printf("Screen 1 %d", cnt);
  display1.update();

  display2.setRotation(1);
  display2.fillScreen(GxEPD_WHITE);
  display2.setTextColor(GxEPD_BLACK);
  display2.setFont(&FreeMonoBold9pt7b);
  display2.setCursor(10, 30);
  display2.println("sheppard semiconductor systems");
  display2.setFont(&FreeMonoBold12pt7b);
  display2.printf("Screen2 %d", cnt);
  display2.update();

  cnt++;
  delay(10000);
}
