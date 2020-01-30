
#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"
SdFat SD;

#define SD_CS_PIN 5
#define buttonPin 6
#define ledPin 10
File myFile;
const unsigned long period = 10000;
unsigned long startMillis;
int buttonState=0; 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input:
  attachInterrupt(digitalPinToInterrupt(buttonPin),procedure,CHANGE);
  while (!Serial) {}

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed!");
    return; // This return statement terminates the program.
  }
  Serial.println("initialization done.");
  startMillis = millis();
  procedure();
}


void loop() {
  //Nothing here
}

void writeSD() {
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    digitalWrite(ledPin,HIGH);
    while (millis() - startMillis < period) {
      myFile.println("X");
    }
    myFile.close();
    Serial.println("done.");
  }
  // close the file:
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    delay(200); // switch debounce in case SD doesn't open
  }
}

void procedure(){
  buttonState = digitalRead(buttonPin); // read the state of the pushbutton value:
  if(buttonState==LOW){ // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    digitalWrite(ledPin,LOW);// If the pushbutton is not pressed, the led will remain turned off and the loop() will be callled again till we push the pushbutton.
    procedure();                  
  }
  else if(buttonState==HIGH){ // When we press the button, it will wrtie into the SD card for 10 seconds, and the LED is turned on
     writeSD();
     digitalWrite(ledPin,LOW);// After writing, the LED is turned off
  }
}
