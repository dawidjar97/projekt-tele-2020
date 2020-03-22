#include "configurator.h"
#include "config.h"

void deleteFile(fs::FS &fs, const char *path = CONFIG_PATH) //to potem sie wywali do jakeigos cpp
{
    #if DEBUG
        Serial.printf("Deleting file: %s\r\n", path);
    #endif

    if (fs.remove(path))
    {
        #if DEBUG
            Serial.println("Cfg file deleted");
        #endif
    }
    else
    {
        #if DEBUG
            Serial.println("Cfg file delete failed");
        #endif
    }
}

bool isConfigurationCompleted(fs::FS &fs) 
{
    return fs.exists(CONFIG_PATH);
}

bool saveConfiguration(fs::FS &fs, const String & ssid, const String & password)
{
    if(fs.exists(CONFIG_PATH)) {
        #if DEBUG
            Serial.println("Config file alredy exists");
        #endif
        return false;
    }
        
    
    File file = fs.open(CONFIG_PATH, FILE_WRITE);
    if(!file || file.isDirectory()) {
        #if DEBUG
            Serial.println("Cannot open config file or is directory");
        #endif
        return false;
    }

    file.print(ssid); file.print('\n');
    file.print(password); file.print('\n');
    file.close();
    return true;
}

bool loadConfiguration(fs::FS &fs, String & ssid, String & password)
{
    if(!fs.exists(CONFIG_PATH)) {
        #if DEBUG
            Serial.println("Config file doesn't exist");
        #endif
        return false;
    }

    File file = fs.open(CONFIG_PATH, FILE_READ);
    if(!file || file.isDirectory()) {
        #if DEBUG
            Serial.println("Cannot open config file or is directory");
        #endif
        return false;
    }
    
    ssid = file.readStringUntil('\n');
    password = file.readStringUntil('\n');

    #if DEBUG
        Serial.print("SSID: "); Serial.println(ssid);
        Serial.print("Password: "); Serial.println(password);
    #endif

    return true;
}