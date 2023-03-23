#ifndef SDMANAGER_H
#define SDMANAGER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"

/*
   Connect the SD card to the following pins:

   SD Card | ESP32
      D2       -
      D3       SS
      CMD      MOSI
      VSS      G  ND
      VDD      3.3V
      CLK      SCK
      VSS      GND
      D0       MISO
      D1       -
*/

class SDManager : public Base {
  public:
    SDManager()
    {

    }

    bool initialize()
    {
      println("Initializing SD card");

      if (!SD.begin()) {
        println("Card Mount Failed", "error");
        return false;
      }

      uint8_t cardType = SD.cardType();

      if (cardType == CARD_NONE) {
        println("No SD card attached", "error");
        return false;
      }

      println("SD Card Type: ");
      if (cardType == CARD_MMC) {
        print("MMC");
      } else if (cardType == CARD_SD) {
        print("SDSC");
      } else if (cardType == CARD_SDHC) {
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
      print("\n\n");
      println("Running example operations");
      // Create a test directory
      createFolder("/example-folder");
      // Create a test file inside the test folder
      createFile("/example-folder/hello_world.txt", "Hello world!");
      // Read the entire contents of the created & appended file
      readFile("/example-folder/hello_world.txt");
      // Show what is in the flolders:
      getFolderContents("/");
      getFolderContents("/example-folder");
      // Delete the file
      deleteFile("/example-folder/hello_world.txt");
      // Delete the folder
      deleteFolder("/example-folder");
      // Show that everything has been cleaned up
      getFolderContents("/");

      uint64_t totalSpace = SD.totalBytes() / (1024 * 1024);
      uint64_t usedSpace = SD.usedBytes() / (1024 * 1024);

      println("Total space: " + String(totalSpace) + "MB");
      println("Used space: " + String(usedSpace) + "MB");

      println("Completed example operations\n\n");
    }

    bool fileExists(const char *path) {
      bool fileAlreadyExists = SD.exists(path);

      if (fileAlreadyExists)
      {
        println("\t File [" +  String(path) + "] exists");
      }
      else
      {
        println("\t File [" +  String(path) + "] does not exist", "warning");
      }

      return fileAlreadyExists;
    }

    String readFile(const char * path) {
      println("Reading file: " + String(path));

      bool exists = fileExists(path);

      if (exists)
      {
        File file = SD.open(path);
        println("\t Opening file for reading");
        if (!file) {
          println("\t Opening FAILED", "warning");
          return "";
        }

        println("\t Data in file: ");
        String fileContents = "";
        while (file.available()) {
          Serial.write(file.read());
        }
        file.close();
      }
    }

    void createFile(const char * path, const char * message)
    {
      println("Creating file: " + String(path));
      println("If no file exists yet, it will be created");

      bool exists = fileExists(path);

      if (exists == false)
      {
        File file = SD.open(path, FILE_WRITE);

        println("\t Opening file for writing");
        if (!file) {
          println("\t Opening FAILED", "warning");
          return;
        }
        if (file.print(message)) {
          println("\t Write OK");
        } else {
          println("\t Write FAILED", "warning");
        }
        file.close();
      }
    }

    void updateFile(const char * path, const char * message)
    {
      println("Updating file: " + String(path));
      println("If the file exists, its contents will be replaced");

      fileExists(path);


    }

    void deleteFile(const char * path) {
      println("Deleting file: " + String(path));

      bool exists = fileExists(path);

      if (exists)
      {
        if (SD.remove(path)) {
          println("\t Delete OK");
        } else {
          println("\t Delete FAILED", "warning");
        }
      }
    }


    void createFolder(const char * path) {
      println("Creating folder: " + String(path));
      bool exists = fileExists(path);

      if (exists == false)
      {
        if (SD.mkdir(path)) {
          println("\t Create OK");
        } else {
          println("\t Create FAILED", "warning");
        }
      }
    }

    void deleteFolder(const char * path) {
      println("Deleting folder: " + String(path));

      bool exists = fileExists(path);

      if (exists)
      {
        if (SD.rmdir(path)) {
          println("\t Delete OK");
        } else {
          println("\t Delete FAILED", "warning");
        }
      }
    }

    void getFolderContents(const char * dirname) {
      println("Listing directory: " + String(dirname));

      bool exists = fileExists(dirname);

      if (exists)
      {
        File root = SD.open(dirname);
        if (!root) {
          println("\t Opening folder FAILED", "warning");
          return;
        }
        if (!root.isDirectory()) {
          println("\t The thing you are trying to open is not a directory", "warning");
          return;
        }

        File file = root.openNextFile();
        while (file) {
          if (file.isDirectory()) {
            println("\t " + String(dirname) + "/" + String(file.name()));
          } else {
            println("\t " + String(dirname) + "/" + String(file.name()));
            print(" [" + String(file.size()) + "bytes]");
          }
          file = root.openNextFile();
        }
      }
    }

  private:
    String Type() {
      return "SDManager";
    }
};

#endif
