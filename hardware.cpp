#include "hardware.h"


bool hw_init()
{

    EEPROM.begin(512);
    if(EEPROM.read(511) != EEPROM_MAGIC_NUM){
        for (int i = 0; i < 512; i++)
            EEPROM.write(i, 0);
        EEPROM.write(511, EEPROM_MAGIC_NUM);    
        EEPROM.commit();
    }
    Serial.begin(9600);
    unsigned long start = millis();
    while (millis() - start < 2000)
    {
        if (digitalRead(4) == LOW)
        {            
            // Serial.println("Setup Mode");
            delay_ms(1000);
            attachInterrupt(4, _reset_ESP, FALLING);
            return true; // setup mode
        }
        yield();
    }
    // Serial.println("Sensor Mode"); 
    attachInterrupt(4, _reset_ESP, FALLING);
    return false; // sensor mode
}

void blink_LED(int dur, int times, int led)
{
    for (int i = 0; i < times; ++i)
    {
        digitalWrite(led, HIGH);
        delay_ms(dur / 2);
        digitalWrite(led, LOW);
        delay_ms(dur / 2);
    }
}

void delay_ms(unsigned long dur)
{
    unsigned long start = millis();
    while (millis() - start < dur)
        delay(1);
}

void shutdown_check(){
    if(digitalRead(3) == LOW)
        shutdown_ESP();
}

void shutdown_ESP()
{
    ESP.deepSleepInstant(10, WAKE_NO_RFCAL);
}

void ICACHE_RAM_ATTR _reset_ESP(){
    reset_ESP(0);
}

void ICACHE_RAM_ATTR reset_ESP(int r)
{
    detachInterrupt(4);
    String reason;
    if(r == 0)
        reason = "MANUEL_RESET";
    else if(r == 1)
        reason = "WDT_TIMEOUT";
    else if(r == 2)
        reason = "CONFIG_DONE";
    else if(r == 3)
        reason = "FIRMWARE_UPDATED";
    else if(r == 4)
        reason = "HTTP_CLIENT_ERROR";

    // noInterrupts();
    for(int i = 192; i < 384; ++i)
        EEPROM.write(i, 0);
    for(int i = 0; i < reason.length(); ++i)
        EEPROM.write(192 + i, reason[i]);
    EEPROM.commit();
    

    ESP.restart();
    delay_ms(2000);
    while(1); // sw or hw WDT can reset device if stuck
}

void ICACHE_RAM_ATTR wdt_ticker_callback(){
    wdt_counter++;
    if(wdt_counter == DAY)
        reset_ESP(1);
}

