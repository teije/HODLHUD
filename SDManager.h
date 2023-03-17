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
    
    // List the existing directory ("/" is the root directory)
    listDir(SD, "/", 0);
    // Create a test directory
    createDir(SD, "/test_directory");
    // Create a test file inside the test directory
    writeFile(SD, "/test_directory/hello_world.txt", "Hello ");
    // Append some text to an existing file
    appendFile(SD, "/test_directory/hello_world.txt", " World!");
    // Read the entire contents of the created & appended file
    readFile(SD, "/test_directory/hello_world.txt");
    // Rename the created test file
    renameFile(SD, "/test_directory/hello_world.txt", "/test_directory/goodbye_world.txt");
    // Read file once more to ensure the rename succeeded
    readFile(SD, "/test_directory/hello_world.txt");
    // Delete the file
    deleteFile(SD, "/test_directory/hello_world.txt");
    // List the existing directory ("/" is the root directory and 1 also includes a level deeper)
    listDir(SD, "/", 1);
    // Delete the directory
    removeDir(SD, "/test_directory");
    
    //testFileIO(SD, "/test.txt");
    
    uint64_t totalSpace = SD.totalBytes() / (1024 * 1024);
    uint64_t usedSpace = SD.usedBytes() / (1024 * 1024);
    
    println("Total space: " + String(totalSpace) + "MB");
    println("Used space: " + String(usedSpace) + "MB");
  }

  /*
  bool confirmDeletion() {
    String confirmInput = "yes";
    println("WARNING: This will delete all files and directories on the SD card. Type '" + confirmInput + "' to continue:");
    
    while (true) {
      if (Serial.available() > 0) {
        
        String userInput = Serial.readStringUntil('\n');
        
        println("User input: " + userInput);
        if (userInput.equals(confirmInput)) {
          return true;
        } else {
          return false;
        }
      }
    }
  }
  */
  
  bool confirmDeletion() {
    int confirmInput = 1;
    println("WARNING: This will delete all files and directories on the SD card. Type " + String(confirmInput) + " to continue:");
    
    while (true) {
      if (Serial.available() > 0) {
        
        int userInput = Serial.parseInt();
        
        println("User input: " + String(userInput));
        if (userInput == confirmInput) {
          return true;
        } else {
          return false;
        }
      }
    }
  }

  
  void deleteAllInDir(const char * dirname){
    File root = SD.open(dirname);
    if(!root){
        return;
    }
    if(!root.isDirectory()){
        return;
    }
    bool hasConfirmedDelete = confirmDeletion();
    if (hasConfirmedDelete == false) {
      println("Deletion aborted.");
      return;
    } 
    else
    {
      println("Delete confirmed on directory: " + String(dirname));
    }
  
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            deleteAllInDir(file.name());
            SD.rmdir(file.name());
        } else {
            SD.remove(file.name());
        }
        file = root.openNextFile();
    }
  
    println("All files and directories deleted.");
  }

  void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
    println("Listing directory: " + String(dirname));

    File root = fs.open(dirname);
    println("\tOpening directory for listing");
    if (!root) {
      println("\tOpening FAILED", "warning");
      return;
    }
    if (!root.isDirectory()) {
      println("Not a directory: " + String(dirname), "warning");
      return;
    }

    File file = root.openNextFile();
    while (file) {
      if (file.isDirectory()) {
        println("\tDIRECTORY : " + String(file.name()));
        
        if (levels) {
          listDir(fs, file.path(), levels - 1);
        }
      } else {
        println("\tFILE: " + String(file.name()) + " => SIZE: " + String(file.size()));
      }
      file = root.openNextFile();
    }
  }

  void createDir(fs::FS &fs, const char * path) {
    println("Creating directory: " + String(path));
    if (fs.mkdir(path)) {
      println("\tOK");
    } else {
      println("\tCreating FAILED", "warning");
    }
  }

  void removeDir(fs::FS &fs, const char * path) {
    println("Removing directory: " + String(path));
    if (fs.rmdir(path)) {
      println("Removing OK");
    } else {
      println("\tRemoving FAILED", "warning");
    }
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

  void appendFile(fs::FS &fs, const char * path, const char * message) {
    println("Appending to file: " + String(path));

    File file = fs.open(path, FILE_APPEND);
    println("\tOpening file for appending");
    if (!file) {
      println("\tOpening FAILED", "warning");
      return;
    }
    if (file.print(message)) {
      println("\tAppend OK");
    } else {
      println("\tAppend FAILED", "warning");
    }
    file.close();
  }
  
  void renameFile(fs::FS &fs, const char * oldPath, const char * newPath){
      println("Renaming file "+ String(oldPath) +" to " + String(newPath));
      if (fs.rename(oldPath, newPath)) {
          println("\tRename OK");
      } else {
          println("\tRename FAILED", "warning");
      }
  }
  
  void deleteFile(fs::FS &fs, const char * path){
      println("Deleting file: " + String(path));
      if(fs.remove(path)){
          println("\tDelete OK");
      } else {
          println("\tDelete FAILED", "warning");
      }
  }
  
  void testFileIO(fs::FS &fs, const char * path){
      File file = fs.open(path);
      static uint8_t buf[512];
      size_t len = 0;
      uint32_t start = millis();
      uint32_t end = start;
      if(file){
          len = file.size();
          size_t flen = len;
          start = millis();
          while(len){
              size_t toRead = len;
              if(toRead > 512){
                  toRead = 512;
              }
              file.read(buf, toRead);
              len -= toRead;
          }
          end = millis() - start;          
          println(String(flen) + " bytes read for " + String(end) + "ms");
          file.close();
      } else {
          println("Failed to open file for reading", "warning");
      }
  
  
      file = fs.open(path, FILE_WRITE);
      if(!file){
          println("Failed to open file for writing", "warning");
          return;
      }
  
      size_t i;
      start = millis();
      for(i=0; i<2048; i++){
          file.write(buf, 512);
      }
      end = millis() - start;
      println(String(2048 * 512) + " bytes read for " + String(end) + "ms");

      file.close();
  }

  private:
    int chipSelectPin;
 
    String Type() {
      return "SDManager";
    }
};

#endif
