#ifndef SDMANAGER_H
#define SDMANAGER_H

#include <SD.h>

class SDManager : public Base {
  public:
    /**
     * Constructor for the SDManager class.
     *
     * @param chipSelectPin The pin number for the chip select pin on the SD card module.
     */
    SDManager(int chipSelectPin) : chipSelectPin(chipSelectPin) 
    {
      println("Add pinout when operational", "todo");  
    }

    /**
     * Initializes the SD card and returns true if successful, false otherwise.
     *
     * @return true if the SD card is initialized successfully, false otherwise.
     */
    bool begin() {
      // Try to initialize the SD card with the given chip select pin.
      println("Initializing the SD card");
      if (!SD.begin(chipSelectPin)) {
        println("Unable to initialize SD Card", "error");
        return false;
      }

      println("SD Card initialized successfully!");
      return true;
    }

    /**
     * Writes the given data to a file with the specified filename on the SD card.
     *
     * @param fileName The name of the file to write the data to.
     * @param data The data to write to the file.
     * @return true if the data is written successfully, false otherwise.
     */
    bool write(const char* fileName, const char* data) {
      println("Preparing to write to file on the SD card [" + String(fileName) + "]");
      
      // Open the file for writing.
      File file = SD.open(fileName, FILE_WRITE);
      if (file) {
        // Write the data to the file and close it.
        file.println(data);
        file.close();
        println("Data written to SD Card successfully!");
        return true;
      } else {
        println("Unable to write data to SD Card", "error");
        return false;
      }
    }
    
    /**
     * Reads data from a file with the specified filename on the SD card and returns it as a string.
     *
     * @param fileName The name of the file to read the data from.
     * @return The data read from the file as a String object, or an empty string if there was an error.
     */
    String read(const char* fileName) {
      println("Preparing to read file from the SD card [" + String(fileName) + "]");
    
      // Open the file for reading.
      File file = SD.open(fileName);
      if (file) {
        String data = "";
        // Read the data from the file and store it in a string.
        while (file.available()) {
          char c = file.read();
          data += c;
        }
        file.close();
        println("Data read from SD Card successfully!");
        return data;
      } else {
        println("Unable to read data from SD Card", "error");
        return "";
      }
    }


    /**
     * Deletes a file with the specified filename from the SD card.
     *
     * @param fileName The name of the file to delete.
     * @return true if the file is deleted successfully, false otherwise.
     */
    bool remove(const char* fileName) {
      println("Preparing to delete to file from the SD card [" + String(fileName) + "]");

      // Try to remove the file from the SD card.
      if (SD.remove(fileName)) {
        println("Data deleted from SD Card successfully!");
        return true;
      } else {
        println("Unable to delete data from SD Card", "error");
        return false;
      }
    }

  private:
    int chipSelectPin;
 
    String Type() {
      return "SDManager";
    }
};

#endif
