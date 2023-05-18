#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "ico.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21); // ESP32 Thing, HW I2C with pin remapping
uint8_t draw_state = 0;

void u8g2_prepare(void)
{
  u8g2.setFont(u8g2_font_fub49_tn);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_disc_circle(uint8_t a)
{
  u8g2.drawStr(0, 0, "drawDisc");
  u8g2.drawDisc(10, 18, 9);
  u8g2.drawDisc(24 + a, 16, 7);
  u8g2.drawStr(0, 30, "drawCircle");
  u8g2.drawCircle(10, 18 + 30, 9);
  u8g2.drawCircle(24 + a, 16 + 30, 7);
}

void init_display()
{
  u8g2.begin();
  u8g2_prepare();
}

void output_status(Status status)
{

  u8g2.clearBuffer();
  u8g2.setBitmapMode(true /* solid */);
  u8g2.drawXBMP(90, 5, 32, 32, logo_heat);

  /*  switch (status_AC[0]){
    case 0:
          display.setCursor(0, 0);
          display.println("OFF");
          break;
    case 1:
          display.setCursor(0, 0);
          display.println(status_AC[2]);

          switch (status_AC[1]){
                  case 0:
                        display.drawBitmap(96, 0, logo_auto, ICO_WIDTH,ICO_HEIGHT,WHITE);
                        break;
                  case 1:
                        display.drawBitmap(96, 0, logo_fun, ICO_WIDTH,ICO_HEIGHT,WHITE);
                        break;
                  case 2:
                        display.drawBitmap(96, 0, logo_dry, ICO_WIDTH,ICO_HEIGHT,WHITE);
                        break;
                  case 3:
                        display.drawBitmap(96, 0, logo_cool, ICO_WIDTH,ICO_HEIGHT,WHITE);
                        break;
                  case 4:
                        display.drawBitmap(96, 0, logo_heat, ICO_WIDTH,ICO_HEIGHT,WHITE);
                        break;
                  }

                  switch (status_AC[3]){
                  case 7:
                        display.drawBitmap(60, 16, fun_auto, ICO_WIDTH,16,WHITE);
                        break;
                  case 0:
                        display.drawBitmap(60, 16, fun_quiet, ICO_WIDTH,16,WHITE);
                        break;
                  case 2:
                        display.drawBitmap(60, 16, fun_medium, ICO_WIDTH,16,WHITE);
                        break;;
                  case 4:
                        display.drawBitmap(60, 16, fun_maximum, ICO_WIDTH,16,WHITE);
                        break;
                  }

                  if (status_AC[4]==15){
                    display.drawBitmap(60, 0, swing_run, ICO_WIDTH,16,WHITE);
                  }else
                    display.drawBitmap(60, 0, swing_stop, ICO_WIDTH,16,WHITE);



          break;
    }*/

  String buf = String(status.temp);
  int len = buf.length() + 1; // Преобразуем строку в массив символов
  char temp[len];
  buf.toCharArray(temp, len);
  u8g2.drawStr(0, 0, temp);

  u8g2.sendBuffer();
}
