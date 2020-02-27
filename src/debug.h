#pragma once

#define HUE_DEBUG

 #if defined(ESP32) || defined(ESP8266)
#define INFO(message, ...) Serial.printf(">>> Hue: " message "\n", ##__VA_ARGS__)
#define ERROR(message, ...) Serial.printf("!!! Hue: " message "\n", ##__VA_ARGS__)
#else
#define INFO(message, ...) Serial.print(">>> mp3: " message "\n");
#define ERROR(message, ...) Serial.print("!!! mp3: " message "\n");
#endif
#ifdef HUE_DEBUG
 #if defined(ESP32) || defined(ESP8266)
#define DEBUG(message, ...) Serial.printf_P(PSTR(">>> %s: " message "\n"), __func__, ##__VA_ARGS__)
#else
#define DEBUG(message, ...) Serial.print("!!!Error mp3: " message "\n");
#endif
#else

#define DEBUG(message, ...)

#endif
