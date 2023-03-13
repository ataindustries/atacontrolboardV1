#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "fileSystem.h"


void Init_File_System(void)
{
  if(!LittleFS.begin())
  {
    Serial.println("An Error occured while mounting LittleFS");
    return;
  }

  // To format all space in LITTLEFS
  // LITTLEFS.format()

  // Get all information of your LITTLEFS
  unsigned int totalBytes = LittleFS.totalBytes();
  unsigned int usedBytes = LittleFS.usedBytes();

  Serial.println("File sistem info.");

  Serial.print("Total bytes:      ");
  Serial.println(totalBytes);

  Serial.print("Total bytes used: ");
  Serial.println(usedBytes);

  Serial.print("Total bytes free: ");
  Serial.println(totalBytes - usedBytes);
  Serial.println();

  // Open dir folder
  File dir = LittleFS.open("/");
  // Cycle all the content

  printDirectory(dir);

  readTestFile();

}

void printDirectory(File dir, int numTabs) 
{
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void readTestFile(void)
{
  
  File file = LittleFS.open("/test.txt", "r");
  
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.println(".......................");
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }

  file.close();
}