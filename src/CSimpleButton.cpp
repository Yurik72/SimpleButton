
#include "CSimpleButton.h"
#include "debug.h"

void IRAM_ATTR isr() {
	Serial.println("isr");
}

CSimpleButton::CSimpleButton() 
#if defined(ESP32) || defined(ESP8266)
:_timer(nullptr) 
#endif
{

	pressed_value = false;
	long_press_time = LONG_PRESS_TIME;
	debounce_time = DEBOUNCE_TIME;
  #if defined(ESP32) || defined(ESP8266)  
	messsage_queue = NULL;
  #endif
	//_timer = NULL;
}
void CSimpleButton::Create(uint8_t gpio, button_callback_fn cb, bool press_val, bool useloop) {
 #if defined(ESP32) || defined(ESP8266) 
	uint32_t now = xTaskGetTickCountFromISR();
#else
  uint32_t now =millis();
#endif
	pressed_value = press_val;
 #if defined(ESP32) || defined(ESP8266) 
	isUseLoop = useloop;
 #else
 isUseLoop=true;
 #endif
	last_event_time = now;
	last_press_time = now;
	callback = cb;
	gpio_num= gpio;

	INFO("Creating button on gpio %d", gpio);
	pinMode(gpio, INPUT_PULLUP);

  #if defined(ESP32) || defined(ESP8266) 
	attachInterruptArg(gpio_num, CSimpleButton::interruptInternal,(void*)this, CHANGE);
 #else 

	attachInterrupt_ex(digitalPinToInterrupt(gpio_num), CSimpleButton::interruptInternal,(void*)this,  CHANGE);
#endif
 #if defined(ESP32) || defined(ESP8266) 
	messsage_queue = xQueueCreate(BTN_QUEUE_SIZE, sizeof(button_queue_item_t));
	xSemaphore= xSemaphoreCreateBinary();
 #endif
}
void  CSimpleButton::Interrupt() {
	DEBUG("Button interrupt %d", gpio_num);
	button_queue_item_t cmd;
#if defined(ESP32) || defined(ESP8266)  
	while (xQueueReceive(messsage_queue, &cmd, 0)) {
#else
  while (m_queue.Dequeue(&cmd)) {
#endif
		uint32_t now = cmd.time;
		if ((now - last_event_time)*portTICK_PERIOD_MS < debounce_time) {
			// debounce time, ignore events
			continue;
		}
		last_event_time = now;
		if (cmd.ispress == pressed_value) {
			// Record when the button is pressed down.
			last_press_time = now;
		}
		else {
			// The button is released. Handle the use cases.
			if ((now - last_press_time) * portTICK_PERIOD_MS > long_press_time) {
				callback(gpio_num, button_event_long_press);
			}
			else {
				callback(gpio_num, button_event_single_press);
			}
		}
	}
	if (isUseLoop)
		return;
	DEBUG("Button ending interrupt %d", gpio_num);
  #if defined(ESP32) || defined(ESP8266)  
	xSemaphoreTake(xSemaphore, portMAX_DELAY);
	if (_timer) {
		esp_timer_stop(_timer);
		esp_timer_delete(_timer);
		_timer = NULL;
		INFO("Destroy timer");
	}
	xSemaphoreGive(xSemaphore);
 #endif
}
void CSimpleButton::HandleLoop() {
	Interrupt();
}
void  IRAM_ATTR CSimpleButton::interruptInternal_noarg() {
	DEBUG("interruptInternal_noarg");
	return;
	
}
void   CSimpleButton::interruptInternal_noISR(void* arg) {

	CSimpleButton*p = static_cast<CSimpleButton*>(arg);
	p->Interrupt();
}
void  IRAM_ATTR CSimpleButton::interruptInternal(void* arg) {
	CSimpleButton*p = static_cast<CSimpleButton*>(arg);

	button_queue_item_t cmd;
	cmd.ispress = digitalRead(p->gpio_num);
 #if defined(ESP32) || defined(ESP8266)  
	cmd.time = xTaskGetTickCountFromISR();
  #else
  cmd.time=millis();
  #endif
  #if defined(ESP32) || defined(ESP8266)  
	xQueueSendToBack(p->messsage_queue, &cmd, 1);
 #else
 p->m_queue.Add(cmd);
 #endif
	if (p->isUseLoop)
		return;
     #if defined(ESP32) || defined(ESP8266) 
	esp_timer_create_args_t _timerConfig;
	_timerConfig.arg = arg;
	_timerConfig.callback = CSimpleButton::interruptInternal_noISR;
	_timerConfig.dispatch_method = ESP_TIMER_TASK;
	_timerConfig.name = "T";

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	/* un-block the interrupt processing task now */
	xSemaphoreTakeFromISR(p->xSemaphore, &xHigherPriorityTaskWoken);
	if (p->_timer) {
		xSemaphoreGiveFromISR(p->xSemaphore, &xHigherPriorityTaskWoken);
		return;
	}
	if (p->_timer) {
		esp_timer_stop(p->_timer);
		esp_timer_delete(p->_timer);
		p->_timer = NULL;
	}
	
	esp_timer_create(&_timerConfig, &p->_timer);
	esp_timer_start_once(p->_timer,   10*1000ULL);
	xSemaphoreGiveFromISR(p->xSemaphore, &xHigherPriorityTaskWoken);
  #endif
}
