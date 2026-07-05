
/* Programmable A500 Super Selector 
 * by tommy.sz
 * tomek.szafranski@me.com
 * Jun 2026                      
 */

#include "EEPROM.h"

// using ATtiny45/85, internal 8MHz clock

#define PIN_RESET         1  // input - Ctrl-A-A reset from GARY
#define PIN_BOOTSEL       0  // output - boot selector/led
#define PIN_KICKSEL       3  // output - kickstart selector/led
#define PIN_BUZZER        2  // output - buzzer
#define PIN_KSMODE        4  // input - jumper for kickstart selection mode: INTERNAL or EXTERNAL
                             // INTERNAL - kickstart selection is managed directly by setting EPROM A18 line (allows 2 kickstarts)
                             // EXTERNAL - reset signal is passed to external kickstart selector (with 3sec shift)

#define KICKSEL_MODE_EXTERNAL        0
#define KICKSEL_MODE_INTERNAL        1
#define EPPROM_ADDR_BOOTSEL_STATE    0
#define EPPROM_ADDR_KICKSEL_STATE    1
#define NONE                       255

uint8_t boot_selector_state;       // 0 is DF0, 1 is DF1
uint8_t kickstart_selector_state;  // 0 is first (A18=0), 1 is second (A18=1) kickstart
uint8_t kickstart_selector_mode;   // 0 is EXTERNAL (closed), 1 is INTERNAL (open)

void setup() 
{
    pinMode(PIN_RESET, INPUT);
    pinMode(PIN_BOOTSEL, OUTPUT);
    pinMode(PIN_KICKSEL, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);    
    pinMode(PIN_KSMODE, INPUT_PULLUP);
    
    boot_selector_state = EEPROM.read(EPPROM_ADDR_BOOTSEL_STATE);
    if (boot_selector_state > 1) { 
       boot_selector_state = 0; 
       EEPROM.write(EPPROM_ADDR_BOOTSEL_STATE, boot_selector_state); 
    }
    
    kickstart_selector_state = EEPROM.read(EPPROM_ADDR_KICKSEL_STATE);
    if (kickstart_selector_state > 1) { 
       kickstart_selector_state = 0; 
       EEPROM.write(EPPROM_ADDR_KICKSEL_STATE, kickstart_selector_state); 
    }

    kickstart_selector_mode = digitalRead(PIN_KSMODE);

    digitalWrite(PIN_BOOTSEL, boot_selector_state);  
    digitalWrite(PIN_KICKSEL, (kickstart_selector_mode == KICKSEL_MODE_INTERNAL)? kickstart_selector_state : HIGH);
    buzzer_signal_selection(boot_selector_state, false);
}

void loop() 
{
    uint16_t count_10ms;
    
    while (true) {
        if (digitalRead(PIN_RESET) == LOW) {

            // RESET is pressed, watch time and wait until is released
            
            count_10ms = 0;
            while (digitalRead(PIN_RESET) == LOW) {
                
                // tick after 3 and 6 secs
                if (count_10ms == 300) {
                    buzzer_tick();
                    if (kickstart_selector_mode == KICKSEL_MODE_EXTERNAL) 
                        digitalWrite(PIN_KICKSEL, LOW);
                }
                else 
                if (count_10ms == 600) {
                    buzzer_tick();
                    // here we know that kickstart selector will probably be toggle, so we set new state right away
                    // it doesn't matter for system as it's still in reset but will be already set when reset signal is released
                    // this seems to be crucial for switching to kickstart 3.1
                    kickstart_selector_state = !kickstart_selector_state;
                    digitalWrite(PIN_KICKSEL, kickstart_selector_state);  
                    EEPROM.write(EPPROM_ADDR_KICKSEL_STATE, kickstart_selector_state);
                }
                else
                if (count_10ms == 900) {
                    buzzer_tick();
                    // time is up, kickstart change will not happen, reverse it 
                    kickstart_selector_state = !kickstart_selector_state;
                    digitalWrite(PIN_KICKSEL, kickstart_selector_state);  
                    EEPROM.write(EPPROM_ADDR_KICKSEL_STATE, kickstart_selector_state);
                }
                else            
                    delay(10);
                    
                count_10ms++;
            }
            
            // RESET is released, act on it, depending on time elapsed
            
            if (count_10ms > 300 && count_10ms <= 600) {
                if (kickstart_selector_mode == KICKSEL_MODE_EXTERNAL)
                    digitalWrite(PIN_KICKSEL, HIGH);
                boot_selector_state = !boot_selector_state;
                digitalWrite(PIN_BOOTSEL, boot_selector_state);  
                EEPROM.write(EPPROM_ADDR_BOOTSEL_STATE, boot_selector_state);
                buzzer_signal_selection(boot_selector_state, false);
            }
            
            if (count_10ms > 600 && count_10ms <= 900 && kickstart_selector_mode == KICKSEL_MODE_INTERNAL) {
                buzzer_signal_selection(kickstart_selector_state, true);
            }
            
            if (count_10ms > 600 && kickstart_selector_mode == KICKSEL_MODE_EXTERNAL) {
                digitalWrite(PIN_KICKSEL, HIGH);
                buzzer_signal_selection(NONE, true);
            }
        }
    }
}

void buzzer_tick()
{
    digitalWrite(PIN_BUZZER, HIGH);
    delay(10);
    digitalWrite(PIN_BUZZER, LOW);  
}

void buzzer_signal_selection(uint8_t state, boolean first_long_beep)
{    
    // first long beep is used to signal new state of kicktart selector
    if (first_long_beep) {
        digitalWrite(PIN_BUZZER, HIGH);
        delay(300);
        digitalWrite(PIN_BUZZER, LOW);
        delay(300);
    }
    for(int i=0; state!=NONE && i<state+1; i++) {
       digitalWrite(PIN_BUZZER, HIGH);
       delay(100);
       digitalWrite(PIN_BUZZER, LOW);
       delay(100);
    }
}
