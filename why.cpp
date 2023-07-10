 
#include <Arduino.h>

 
#include "PinDefinitionsAndMore.h" 

#define RECORD_GAP_MICROS 15000  
 
#define IR_RECEIVE_PIN   2  
#define IR_SEND_PIN      3


#include <IRremote.hpp>

const uint16_t toggleOnData[115] = {3000,8850, 450,1550, 400,600, 400,550, 450,550, 400,600, 400,600, 400,550, 450,550, 400,600, 400,1550, 450,550, 400,600, 400,550, 450,550, 400,1600, 400,1550, 400,600, 400,1550, 400,1600, 400,1550, 400,1550, 450,1550, 400,1550, 450,1550, 400,1550, 450,550, 400,600, 400,550, 450,1550, 400,1550, 450,1550, 400,550, 450,1550, 400,1550, 450,550, 400,600, 400,1550, 450,550, 400,600, 400,550, 450,1550, 400,600, 400,550, 450,550, 400,1550, 450,550, 450,550, 400,600, 400,550, 450,550, 400,600, 400,600, 400,1550, 400,1550, 450,1550, 400,1550, 450};  // Protocol=PulseDistance Raw-Data=0xF01113 56 bits LSB first
const uint16_t toggleOffData[231] = {3030,8920, 480,1520, 480,520, 430,520, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,1470, 480,520, 480,520, 430,1520, 480,1470, 480,520, 480,1520, 430,1520, 480,1520, 430,1520, 480,1470, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,470, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,470, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,470, 480,520, 480,1520, 430,520, 480,1520, 480,520, 430,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,2420, 3030,8920, 530,1470, 480,520, 480,520, 430,520, 480,520, 480,520, 480,520, 430,520, 480,520, 480,1470, 480,520, 480,520, 480,1470, 480,520, 480,520, 480,470, 480,1520, 480,1470, 480,1520, 480,1470, 480,520, 480,1470, 480,520, 480,1520, 430,1520, 480,520, 480,470, 480,520, 480,1520, 430,1520, 480,1470, 480,520, 480,1520, 430,1520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,470, 480,1520, 480,520, 430,520, 480,520, 480,1470, 480,520, 480,520, 480,520, 430,520, 480,520, 480,520, 480,520, 430,520, 480,520, 480,1470, 480,1520, 480};  // Protocol=UNKNOWN Hash=0xB040A30 116 bits (incl. gap and start) received


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(3, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin
#endif

    Serial.println(F("Ready to send IR signals at pin "  STR(IR_SEND_PIN)));
}

void sendState(bool enable) {
    if (enable) {
      IrSender.sendRaw(toggleOnData, sizeof(toggleOnData) / sizeof(toggleOnData[0]), 38); 
    } else {
      IrSender.sendRaw(toggleOffData, sizeof(toggleOffData) / sizeof(toggleOffData[0]), 38); 
    }
}
 
void loop() {
    sendState(true);
    delay(1000); 
    sendState(false);
    delay(1000); 
}
