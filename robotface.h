#ifndef robotface_h
#define robotface_h

#include "Arduino.h"
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

class RobotEyes {
  private:
      U8G2_SH1106_128X64_NONAME_F_HW_I2C& display;
      const uint8_t TCA9548A_ADDR = 0x70;
      const uint8_t LEFT_EYE_CHANNEL = 7;
      const uint8_t RIGHT_EYE_CHANNEL = 6;
  
      void selectChannel(uint8_t channel) {
          Wire.beginTransmission(TCA9548A_ADDR);
          Wire.write(1 << channel);
          Wire.endTransmission();
      }
  
      void drawEyes(void (RobotEyes::*leftEyeFunc)(), void (RobotEyes::*rightEyeFunc)()) {
          selectChannel(LEFT_EYE_CHANNEL);
          (this->*leftEyeFunc)();
          
          selectChannel(RIGHT_EYE_CHANNEL);
          (this->*rightEyeFunc)();
      }
  
      // Prywatne metody rysowania dla pojedynczych oczu
      void drawCloseEye() {
          display.clearBuffer();
          display.drawRBox(29, 20, 70, 24, 6);
          display.sendBuffer();
      }
  
      void drawNormalEye() {
          display.clearBuffer();
          display.drawRBox(29, 2, 70, 60, 9);
          display.sendBuffer();
      }
  
      void drawSadLeftEye() {
          display.clearBuffer();
          display.drawRBox(29, 2, 70, 54, 9);
          display.setDrawColor(0);
          display.drawTriangle(1, 1, 100, 1, 1, 35);
          display.setDrawColor(1);
          display.sendBuffer();
      }
  
      void drawSadRightEye() {
          display.clearBuffer();
          display.drawRBox(29, 2, 70, 54, 9);
          display.setDrawColor(0);
          display.drawTriangle(1, 1, 100, 1, 100, 24);
          display.setDrawColor(1);
          display.sendBuffer();
      }

      void drawUpsetEye() {
        display.clearBuffer();
        display.drawRBox(29, 2, 70, 60, 9);
        display.setDrawColor(0);
        display.drawDisc(64, -66, 100, U8G2_DRAW_ALL);
        display.setDrawColor(1);
        display.sendBuffer();
      }
      
      void drawHappyEye() {
        display.clearBuffer();
        display.drawRBox(29, 10, 70, 55, 13);
        display.setDrawColor(0);
        display.drawDisc(64, 75, 50, U8G2_DRAW_ALL);
        display.setDrawColor(1);
        display.sendBuffer();
      }
      
      void drawAngryLeftEye() {
        display.clearBuffer();
        display.drawRBox(29, 2, 70, 60, 9);
        display.setDrawColor(0);
        display.drawTriangle(1, 1, 100, 1, 100, 24);
        display.setDrawColor(1);
        display.sendBuffer();
      }
      
      void drawAngryRightEye() {
        display.clearBuffer();
        display.drawRBox(29, 2, 70, 60, 9);
        display.setDrawColor(0);
        display.drawTriangle(1, 1, 100, 1, 1, 35);
        display.setDrawColor(1);
        display.sendBuffer();
      }
      
      void drawNameLeftEye() {
        display.clearBuffer();
        display.setFontMode(1);
        display.setBitmapMode(1);
        display.setFont(u8g2_font_timR24_tr);
        display.drawStr(20, 44, "OTTO");
        display.sendBuffer();
      }
      
      void drawwNameRightEye() {
        display.clearBuffer();
        display.setFontMode(1);
        display.setBitmapMode(1);
        display.setFont(u8g2_font_timR24_tr);
        display.drawStr(16, 44, "NINJA");
        display.sendBuffer();
      }
      
      void drawSuspiciousLeftEye() {
        display.clearBuffer();
        display.drawRBox(29, 12, 70, 30, 9);
        display.setDrawColor(0);
        display.drawTriangle(26, 12, 104, 12, 104, 22);
        display.setDrawColor(1);
        display.sendBuffer();
      }
      
      void drawSuspiciousRightEye() {
        display.clearBuffer();
        display.drawRBox(29, 22, 70, 20, 9);
        display.setDrawColor(0);
        display.drawTriangle(29, 22, 104, 22, 29, 32);
        display.setDrawColor(1);
        display.sendBuffer();
      }

      void drawDownEye() {
        //close();
        //delay(120);
        display.clearBuffer();
        display.drawRBox(39, 34, 50, 21, 9);
        display.sendBuffer();
      }
      
      void drawRightEye() {
        //close();
        //delay(120);
        display.clearBuffer();
        display.drawRBox(2, 2, 70, 60, 9);
        display.sendBuffer();
      }
      
      void drawLeftEye() {
        //close();
        //delay(120);
        display.clearBuffer();
        display.drawRBox(55, 2, 70, 60, 9);
        display.sendBuffer();
      }
      
      void drawUpEye() {
        //close();
        //delay(120);
        display.clearBuffer();
        display.drawRBox(39, 3, 50, 25, 9);
        display.sendBuffer();
      }

      void drawHeart() {
        display.clearBuffer();
        display.drawDisc(50, 22, 15, U8G2_DRAW_ALL);  // Lewa górna część serca
        display.drawDisc(78, 22, 15, U8G2_DRAW_ALL);  // Prawa górna część serca
        display.drawTriangle(35, 25, 93, 25, 64, 55); // Dolna część serca
        display.sendBuffer();
      }
      
      void drawError() {
        display.clearBuffer();
        for (int i = -2; i <= 2; i++) {  
            display.drawLine(29 + i, 60, 99 + i, 2);  
            display.drawLine(29 + i, 2, 99 + i, 60);
        }
        display.sendBuffer();
      }      
  public:
      RobotEyes(U8G2_SH1106_128X64_NONAME_F_HW_I2C& u8g2) : display(u8g2) {}
  
      void begin() {
          selectChannel(LEFT_EYE_CHANNEL);
          display.begin();
          selectChannel(RIGHT_EYE_CHANNEL);
          display.begin();
      }
  
      void close() {
          drawEyes(&RobotEyes::drawCloseEye, &RobotEyes::drawCloseEye);
      }
  
      void normal() {
          drawEyes(&RobotEyes::drawNormalEye, &RobotEyes::drawNormalEye);
      }
  
      void sad() {
          drawEyes(&RobotEyes::drawSadLeftEye, &RobotEyes::drawSadRightEye);
      }
      
      void angry() {
          drawEyes(&RobotEyes::drawAngryLeftEye, &RobotEyes::drawAngryRightEye);
      }

      void upset() {
          drawEyes(&RobotEyes::drawUpsetEye, &RobotEyes::drawUpsetEye);
      }

      void happy() {
          drawEyes(&RobotEyes::drawHappyEye, &RobotEyes::drawHappyEye);
      }
      
      void suspicious() {
          drawEyes(&RobotEyes::drawSuspiciousLeftEye, &RobotEyes::drawSuspiciousRightEye);
      }

      void name() {
          drawEyes(&RobotEyes::drawNameLeftEye, &RobotEyes::drawwNameRightEye);
      }

      void down() {
          drawEyes(&RobotEyes::drawDownEye, &RobotEyes::drawDownEye);
      }

      void left() {
          drawEyes(&RobotEyes::drawLeftEye, &RobotEyes::drawLeftEye);
      }

      void right() {
          drawEyes(&RobotEyes::drawRightEye, &RobotEyes::drawRightEye);
      }

      void up() {
          drawEyes(&RobotEyes::drawUpEye, &RobotEyes::drawUpEye);
      }

      void heart() {
          drawEyes(&RobotEyes::drawHeart, &RobotEyes::drawHeart);
      }

      void error() {
          drawEyes(&RobotEyes::drawError, &RobotEyes::drawError);
      }

      void blink() {
          normal();
          close();
          delay(50);
          normal();
      }
  };
  
  #endif
