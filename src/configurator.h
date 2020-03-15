#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"


void deleteFile(fs::FS &fs, const char * path);
void configurationLoad(fs::FS &fs, const char * path,String &ssid, String &pass);
