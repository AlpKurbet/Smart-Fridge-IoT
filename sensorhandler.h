#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include "frid.h"

void readvalues();
long int incomingByte; 
String JSON_Data;
String Sensor_Data;

int _weightType;
int _weight;
int _unit;
int _scaleRetType;
String scale_id = "99_99" ;
String scale_ip;
String scale_mac;
String bssid; 
String rssi = " ";
float scale_fw = 0.02;
String scale_hw = "aaa";
String scale_err = " ";
String timeofdata = "2022-01-11 14:48:26";
bool start_sending_data = false;
float sending_data;
float weight_previous;
int weight_counter;
String weight_type;
String weight_unit;
String kgunit = "KG";   // these are to get data correctly, will be changed later 
String typeofw = "GS"; // these are to get data correctly, will be changed later

void jsonify_data(String data);
void replace_callback();
extern void http_POST_request(String req);
extern void delay_ms(unsigned long dur);
void blink_LED(int dur, int times, int led);
void data_controller(String data);
