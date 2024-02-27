//////////////////////////////////////////////////
//              BLM SHOT COUNTER                //
//      This project uses an arduino, SD Card
//    Extender, and an AdaFruit Electret Microphone.
//    It also uses the Xbee Antenna
//////////////////////////////////////////////////

// Using SD and SPI for the SD card Extender
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

SoftwareSerial xbeeSerial(0, 1);

// Initializing Card metadata;
Sd2Card card;
SdVolume volume;
SdFile root;
File myFile;

// Declare constant variables
const int chipSelect = 10;
const int micpin = A1;

int mic;  // Analog Read variable

// mic will be powered with a 3.3v output.
// Center will be at 1.56v, which will be read
// with the value of 1.65/5*1023 = 337
const int baseline = 337;

int amplitude;    // Difference between mic reading and baseline
const int max_amplitude = 156;

void handleCommand(String c) {            // Handles the command to performs the necessary task

      if (c == "T") {                     // Test signal
      Serial.println("T received");


    } else if (c == "S") {                // Test packet verification
      Serial.println("S received");


    } else if (c == "WRITE") {          // Write 'Testing 1, 2, 3' into SD card through pin 10
//      Serial.println("Something was Written into SD card");       ////// DEBUGGING PROMPT   //////
      myFile = SD.open("test.txt", FILE_WRITE);

      if (myFile) {               // Verifying the file was open correctly
        Serial.println("Writing to test.txt....");
        myFile.println("Testing 1, 2, 3");
        myFile.close();
      } else {
        Serial.println("Error opening file.\n");
      } 



    } else if (c == "READ") {         // Opens the file that is stored on the SD card and prints the contents on to the serial stream.
      
      Serial.println("Reading from SD card");           ////// DEBUGGING PROMPT   //////
      myFile = SD.open("test.txt", FILE_READ);

      if (myFile) {                   // File Verification
        Serial.println("test.txt: ");                   ////// DEBUGGING PROMPT   //////
          while (myFile.available()) {   // Iterate through the file
              Serial.write(myFile.read());    // Print contents to Serial
          }
        myFile.close();               // Close file
          } else {
    Serial.println("error opening file");
  }
    } else if (c == "DELETE") {
      Serial.println("Deleting SD files");              ////// DEBUGGING PROMPT   //////
      SD.remove("test.txt");
      if (!SD.exists("test.txt")) {
        Serial.println("Delete Successful");            ////// DEBUGGING PROMPT   //////
      } else {
        Serial.println("Delete failed");                ////// DEBUGGING PROMPT   //////
      }
    } else {                        // Packet was not expected
      Serial.println("Something was received");
    }
}


//////////////////////////////////////////////
/////           Start > setup            /////
//////////////////////////////////////////////
void setup() {
  // 9600 Baud Rate | System startup prompt
  Serial.begin(9600);
  Serial.println("System up");

  Serial.println("Initializing SD card...");
  // Setting CS = 10
  pinMode(chipSelect, OUTPUT);

  // Init pin 10 for SD storage
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed.");
    while(1);
  }
  Serial.println("Init Done");
}

//////////////////////////////////////////////
/////           Start > loop             /////
//////////////////////////////////////////////
void loop() {
  mic = analogRead(micpin);
  amplitude = abs(mic-baseline);

  if (amplitude > 280) {               // "Software Filter" //

    Serial.print(amplitude);
    Serial.println(" -> BANG");
    delay(500);                       // de-Bouncing

  }

  // Wait for Signal (Expecting: T - test, S - verify, READ - Read SDCard contents, WRITE - Write 'Testing 1, 2, 3' to SDCard)
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');    // Can Read multi-chars to make String commands
    command.trim();
    handleCommand(command);       // Will perform the expected handles

  }
}
