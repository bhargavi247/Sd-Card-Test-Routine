
#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"
SdFat SD;

#define SD_CS_PIN 4
#define buttonPin 1
#define ledPin 36
File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  int sensorVal = digitalRead(buttonPin);
  pinMode(ledPin,OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

    myFile = SD.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if(sensorVal==LOW){
      digitalWrite(ledPin, HIGH);
      writeSD();
      sensorVal=HIGH;
    }
    else if(sensorVal==HIGH){
      digitalWrite(ledPin, LOW);
    }
  }  

void loop() {
  // nothing happens after setup
}

void writeSD(){
  unsigned long startMillis;
  unsigned long currentMillis;
  const unsigned long period = 10000;
  startMillis=millis();
  if (myFile) {
      Serial.print("Writing to test.txt...");

      while(true){
        myFile.println("A");
        currentMillis=millis();
        if(currentMillis-startMillis>period){
          break;
        }
        }
      myFile.close();
      Serial.println("done.");
      }
    // close the file:
    else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
