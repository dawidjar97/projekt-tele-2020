#include "configurator.h"

void deleteFile(fs::FS &fs, const char * path)//to potem sie wywali do jakeigos cpp
{
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path))
    {
        Serial.println("Cfg file deleted");
    } else 
    {
        Serial.println("Cfg file delete failed");
    }
}

void configurationLoad(fs::FS &fs, const char * path,String &ssid, String &passwd)
{
    
    File file = fs.open(path);
    if(!file || file.isDirectory()) //Write cfg file
    {
        Serial.println("Failed to open file for reading");
        Serial.println("Making new cfg file");
        file = fs.open(path, FILE_WRITE);
        if(!file)
        {
            Serial.println("Failed to open file for writing");
        }
        else
        {
          if(file.println(ssid))
          {
              file.println(passwd);
              Serial.println("File written");
          }
          else 
          {
              Serial.println("Write failed");
          }
        }
    }
    else  //Read cfg file
    {
        char sign;
        ssid="";
        passwd="";

        Serial.println("Read from file:");

        while(file.available() && sign!='\n') /* SSID */
        {
            sign=file.read();
            //Serial.write(sign);
            if(sign!='\n')
                ssid+=sign;
        }
        do /* Password */
        {
            sign=file.read();
            //Serial.write(sign);
            if(sign!='\n')
                passwd+=sign;
        } while (file.available() && sign!='\n');
    }
    Serial.println("SSID: "+ssid);
    Serial.println("PASS: "+passwd);
}