#ifndef SDMANAGER_H
#define SDMANAGER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"

/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      G  ND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */

class SDManager : public Base {
public:
  SDManager()
  {
    
  }
  
  bool initialize()
  {
    println("Initializing SD card");
    
    if(!SD.begin()){
        println("Card Mount Failed", "error");
        return false;
    }
    
    uint8_t cardType = SD.cardType();
    
    if(cardType == CARD_NONE){
        println("No SD card attached", "error");
        return false;
    }

    println("SD Card Type: ");
    if(cardType == CARD_MMC){
        print("MMC");
    } else if(cardType == CARD_SD){
        print("SDSC");
    } else if(cardType == CARD_SDHC){
        print("SDHC");
    } else {
        print("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    println("SD Card Size: " + String(cardSize) + "MB");

    return true;
  }

  void runExampleOperations()
  {
    println("Running example operations");

    // Create a test file inside the test directory
    writeFile(SD, "/hello_world.txt", "Hello world!");
    // Read the entire contents of the created & appended file
    readFile(SD, "/hello_world.txt");
    // Delete the file
    deleteFile(SD, "/hello_world.txt");
    
    uint64_t totalSpace = SD.totalBytes() / (1024 * 1024);
    uint64_t usedSpace = SD.usedBytes() / (1024 * 1024);
    
    println("Total space: " + String(totalSpace) + "MB");
    println("Used space: " + String(usedSpace) + "MB");
  }

  void readFile(fs::FS &fs, const char * path) {
    println("Reading file: " + String(path));

    File file = fs.open(path);
    println("\tOpening file for reading");
    if (!file) {
      println("\tOpening FAILED", "warning");
      return;
    }

    println("\tData in file: ");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  }

  void writeFile(fs::FS &fs, const char * path, const char * message) {
    println("Writing file: " + String(path));

    File file = fs.open(path, FILE_WRITE);
    
    println("\tOpening file for writing");
    if (!file) {
      println("\tOpening FAILED", "warning");
      return;
    }
    if (file.print(message)) {
      println("\tWrite OK");
    } else {
      println("\tWrite FAILED", "warning");
    }
    file.close();
  }

  void deleteFile(fs::FS &fs, const char * path){
      println("Deleting file: " + String(path));
      if(fs.remove(path)){
          println("\tDelete OK");
      } else {
          println("\tDelete FAILED", "warning");
      }
  }

  private:
    String Type() {
      return "SDManager";
    }
};

#endif
