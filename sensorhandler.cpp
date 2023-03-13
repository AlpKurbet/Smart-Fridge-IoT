
#include "sensorhandler.h"

void readvalues()
{
 
  if (Serial.available())
  {
    String data;
    while (Serial.available())
    {
      data += (char)Serial.read();
      // Serial.println(" The first println:");
      // Serial.println(data);
      
    }
    if(data.length() > 0){
        data_controller(data);
        blink_LED(1000, 3, 5);
        // delay_ms(1000);
        // Serial.println("Data Controlled ");
        // Serial.println(data);
    }
    if(start_sending_data){

       String Scale_Data = "\n{\"RequestName\":\"WEIGHT_DATA\",\"RequestHeader\":\n{\"UserName\":\"aaa\",\"Password\":\"aaa\"},\"RequestBody\":{";
        Scale_Data  += "\"scale_ID\":\"" + String(scale_id) + "\","; 
        Scale_Data  += "\"scale_IP\":\"" + String(scale_ip) + "\","; 
        Scale_Data  += "\"scale_MAC\":\"" + String(scale_mac) + "\","; 
        Scale_Data  += "\"scale_BSSID\":\"" + String(scale_mac) + "\","; 
        Scale_Data  += "\"scale_RSSI\":\"" + String(rssi) + "\","; 
        Scale_Data  += "\"scale_fwVer\":\"" + String(scale_fw) + "\","; 
        Scale_Data  += "\"scale_hwVer\":\"" + String(scale_hw) + "\","; 
        Scale_Data  += "\"scale_Err\":\"" + String(scale_err) + "\","; 
        Scale_Data  += "\"weight_unit\":\"" + String(kgunit) + "\","; 
        Scale_Data  += "\"weight_type\":\"" + String(typeofw) + "\","; 
        Scale_Data  += "\"weight\":\"" + String(sending_data) + "\","; 
       Scale_Data  += "\"datetime\":\"" + String(timeofdata) + "\",";   
       Scale_Data  += "\"scaleRetType\":\"" + String("Ask") + "\"}"; 
       Scale_Data  += "}";
      //  Serial.println(" Sending This:");
      //  Serial.println(Scale_Data);
      http_POST_request(Scale_Data);
    }
  }
}


void data_controller(String data){

  String string_weight_current = data.substring(9,13);
  float weight_current = string_weight_current.toFloat();
  // Serial.println("THE CURRENT WEIGHT");
  // Serial.println(weight_current);
  if (weight_current == weight_previous){
    // Serial.println(weight_counter);
    if(weight_counter <5){
      weight_counter++;

    }
    else if(weight_counter == 5){
        start_sending_data = true;
        // Serial.println("I got 5 identical data, sending");
        sending_data = weight_current; 
        weight_type = data.substring(3,5);
        weight_unit = data.substring(14,16);
        weight_counter = 0;
    }
    // else {
         
    //   }
  }
  else 
  {
    weight_counter = 0;
    weight_previous = weight_current;
  }
}