#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"

void deleteFile(fs::FS &fs, const char *path);
bool isConfigurationCompleted(fs::FS &fs);
bool saveConfiguration(fs::FS &fs, const String & ssid, const String & password);
bool loadConfiguration(fs::FS &fs, String & ssid, String & password);