#pragma once

#include "frid.h"

unsigned long Time;
void setup()
{
  hw_init();  //SETUP_MODE
  wifi_init(false);
  // http_server_init();
  // update_fw(SETUP_MODE);
  // http_client_init(SETUP_MODE);
  // timers_init(SETUP_MODE);
}

void loop()
{
  // Serial.println("in loop");
  readvalues();
  // http_POST_request(Sensor_Data);
  delay_ms(2000);
}
