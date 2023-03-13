#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Regexp.h>
#include <ArduinoJson.h>

// bool SETUP_MODE;

extern bool hw_init();
extern bool wifi_init(bool s_mode);
extern bool sensors_init(bool s_mode);
extern void http_server_init();
extern void http_client_init(bool s_mode);
extern void timers_init(bool s_mode);
extern void update_fw(bool s_mode);
extern void delay_ms(unsigned long dur);
extern void wifi_check();
extern void shutdown_check();
extern void http_POST_request(String req);
extern void http_POST222_request();
extern String Sensor_Data; 
extern String JSON_Data;
extern volatile bool senssenddata_check;
// volatile bool loop_wifi = true;
extern void readvalues();
extern ESP8266WebServer WEB_SERVER;
