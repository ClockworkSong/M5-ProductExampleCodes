#include <M5Stack.h>
#include <mcp_can.h>
#include "m5_logo.h"

/**
 * variable for loop
 */

byte data_on[8] = {};
byte data_off[8] = {};
byte data_cw[8] = {0x47, 0x8C, 0xA0, 0x00};
byte data_acw[8] = {0xc7, 0x8C, 0xA0, 0x00};

/**
 * variable for CAN
 */
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

#define CAN0_INT 15                              // Set INT to pin 2
MCP_CAN CAN0(12);     // Set CS to pin 10

void init_can();
void test_can();


void setup() {
  M5.begin();
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);

  M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
  delay(500);
  M5.Lcd.setTextColor(BLACK);
  // M5.Lcd.setTextSize(1);

    init_can();
    Serial.println("Test CAN...");
}

void loop() {
  if(M5.BtnA.wasPressed())
  {
    M5.Lcd.clear();
    M5.Lcd.printf("CAN Test B!\n");
    M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
    init_can();
  }
  test_can();
  M5.update();
}

void init_can(){
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
  M5.Lcd.printf("CAN Test B!\n");

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
//  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  if(CAN0.begin(MCP_EXT, CAN_125KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

void test_can(){
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x80781, 1, 0, data_on);//motor on
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
    M5.Lcd.printf("Message Sent Successfully!\n");
  } else {
    Serial.println("Error Sending Message...");
    M5.Lcd.printf("Error Sending Message...\n");
  }
  delay(200);   // send data per 200ms

  sndStat = CAN0.sendMsgBuf(0x80785, 1, 4, data_cw);//motor cw
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
    M5.Lcd.printf("Message Sent Successfully!\n");
  } else {
    Serial.println("Error Sending Message...");
    M5.Lcd.printf("Error Sending Message...\n");
  }
  delay(3000);   // send data per 3000ms

 sndStat = CAN0.sendMsgBuf(0x80184, 1, 0, data_off);//motor off
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
    M5.Lcd.printf("Message Sent Successfully!\n");
  } else {
    Serial.println("Error Sending Message...");
    M5.Lcd.printf("Error Sending Message...\n");
  }
  delay(200);   // send data per 200ms

  sndStat = CAN0.sendMsgBuf(0x80785, 1, 4, data_acw);//motor cw
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
    M5.Lcd.printf("Message Sent Successfully!\n");
  } else {
    Serial.println("Error Sending Message...");
    M5.Lcd.printf("Error Sending Message...\n");
  }
  delay(3000);   // send data per 3000ms
  
  sndStat = CAN0.sendMsgBuf(0x80184, 1, 0, data_off);//motor off
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
    M5.Lcd.printf("Message Sent Successfully!\n");
  } else {
    Serial.println("Error Sending Message...");
    M5.Lcd.printf("Error Sending Message...\n");
  }
  delay(200);   // send data per 200ms

}
