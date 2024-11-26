#include <GxEPD.h>
#include <GxGDEM029T94/GxGDEM029T94.h>   
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>  
#include <SPI.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <SD.h>  // Include the SD library

#define CS1   5   // Chip select for display 1
#define DC1   22  // Data/Command for display 1
#define RSET1 21  // Reset for display 1
#define BUSY1 4   // Busy for display 1

#define CS2   15  // Chip select for display 2
#define DC2   2   // Data/Command for display 2
#define RSET2 0   // Reset for display 2
#define BUSY2 16  // Busy for display 2

#define MOSI 23  // Data in
#define SCLK 18  // Clock
#define CS_PIN 33 // Chip select for SD card

GxIO_Class io1(SPI, CS1, DC1, RSET1);
GxEPD_Class display1(io1, RSET1, BUSY1);

GxIO_Class io2(SPI, CS2, DC2, RSET2);
GxEPD_Class display2(io2, RSET2, BUSY2);

const char TextBsp[] = "Irgendein Text";

int cnt; // counter zum Testen des Beispiels mit alter GxEPD library

File root; // Declare the root variable

void printDirectory(File dir, int numTabs);

void setup() {
  Serial.begin(115200);
 // Initialize displays
  SPI.begin(SCLK, MISO, MOSI);
  display1.init();
  display2.init();

  display1.setRotation(1);
  display1.fillScreen(GxEPD_WHITE);
  display1.setTextColor(GxEPD_BLACK);
  display1.setFont(&FreeMonoBold9pt7b);
  display1.setCursor(10, 30);
  display1.print("Initializing SD card... ");
  display1.update();


  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }

  Serial.println("initialization done.");

  Serial.println("Files in the card:");
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("");

  // Example of reading file from the card:
  File textFile = SD.open("/wokwi.txt");
  if (textFile) {
    Serial.print("wokwi.txt: ");
    while (textFile.available()) {
      Serial.write(textFile.read());
    }
    textFile.close();
  } else {
    Serial.println("error opening wokwi.txt!");
  }

}

void loop() {
  delay(100);
  display1.setRotation(1);
  display1.fillScreen(GxEPD_WHITE);
  display1.setTextColor(GxEPD_BLACK);
  display1.setFont(&FreeMonoBold9pt7b);
  display1.setCursor(10, 30);
  display1.println("sheppard semiconductor systems");
  display1.setFont(&FreeMonoBold12pt7b);
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
  
  void printDirectory(File dir, int numTabs);
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
       display1.setRotation(1);
        display1.fillScreen(GxEPD_WHITE);
        display1.setTextColor(GxEPD_BLACK);
        display1.setFont(&FreeMonoBold9pt7b);
        display1.setCursor(10, 30);
        display1.print('\t');
          display1.update();

    }
     display1.setRotation(1);
  display1.fillScreen(GxEPD_WHITE);
  display1.setTextColor(GxEPD_BLACK);
  display1.setFont(&FreeMonoBold9pt7b);
  display1.setCursor(10, 30);
    display1.print(entry.name());
      display1.update();

    if (entry.isDirectory()) {
       display1.setRotation(1);
  display1.fillScreen(GxEPD_WHITE);
  display1.setTextColor(GxEPD_BLACK);
  display1.setFont(&FreeMonoBold9pt7b);
  display1.setCursor(10, 30);
      display1.println("/");
  display1.update();

      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      display1.print("\t\t");
      display1.println(entry.size(), DEC);
        display1.update();

    }
    entry.close();
  }
}
