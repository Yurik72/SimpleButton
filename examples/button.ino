#include "CSimpleButton.h"

CSimpleButton btn;

void button_callback(uint8_t gpio, button_event_t event) {
Serial.println("Button callback");
}
void setup() {
  // put your setup code here, to run once:
btn.Create(4, button_callback,true);
}

void loop() {
  // put your main code here, to run repeatedly:
btn.HandleLoop();
}
