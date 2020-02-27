#include "CSimpleButton.h"

CSimpleButton btn;

void button_callback(uint8_t gpio, button_event_t event) {
Serial.println("Button callback");
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
btn.Create(D2, button_callback,true);  //works for instance on Arduino nano with interrrupts
}

void loop() {
  // put your main code here, to run repeatedly:
btn.HandleLoop();
}
