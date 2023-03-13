#pragma once

extern "C" {
  #include "user_interface.h"
  #include "gpio.h"  
  
}

#include <Arduino.h>
#include <EEPROM.h>
#include "frid.h"

#define MINUTES                     60
#define HOUR                        60*MINUTES
#define DAY                         24*HOUR


String LAST_ERROR;
String ERROR;
int32_t wdt_counter = 0;

bool hw_init();
void blink_LED(int dur, int times, int led);
void delay_ms(unsigned long dur);
void reset_ESP(int r);
void _reset_ESP();
void wdt_ticker_callback();
void shutdown_check();
void shutdown_ESP();
int EEPROM_MAGIC_NUM = 137;
