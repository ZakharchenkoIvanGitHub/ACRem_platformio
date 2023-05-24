#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "ico.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21); // ESP32 Thing, HW I2C with pin remapping
uint8_t draw_state = 0;

void u8g2_prepare(void)
{
      u8g2.setFont(u8g2_font_6x10_tf);
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
      // u8g2.setBitmapMode(true /* solid */);
      // u8g2.drawXBMP(90, 0, u8g2_logo_heat_width, u8g2_logo_heat_height, logo_dry);

      switch (status.power)
      {
      case off:
            u8g2.setFont(u8g2_font_10x20_tf);
            u8g2.drawStr(0, 0, "OFF");
            break;
      case on:
            String buf = String(status.temp);
            int len = buf.length() + 1; // Преобразуем строку в массив символов
            char temp[len];
            buf.toCharArray(temp, len);
            u8g2.setFont(u8g2_font_fub49_tn);
            u8g2.drawStr(0, 0, temp);
            //u8g2.drawStr(0, 0, "gterg");

            switch (status.mode)
            {
            case Auto:
                  u8g2.drawXBMP(90, 0, u8g2_logo_auto_width, u8g2_logo_auto_height, logo_auto);
                  break;
            case Fun:
                  u8g2.drawXBMP(90, 0, u8g2_logo_fun_width, u8g2_logo_fun_height, logo_fun);
                  break;
            case Dry:
                  u8g2.drawXBMP(90, 0, u8g2_logo_dry_width, u8g2_logo_dry_height, logo_dry);
                  break;
            case Cool:
                  u8g2.drawXBMP(90, 0, u8g2_logo_cool_width, u8g2_logo_cool_height, logo_cool);
                  break;
            case Heat:
                  u8g2.drawXBMP(90, 0, u8g2_logo_heat_width, u8g2_logo_heat_height, logo_heat_3);
                  break;
            }

            switch (status.fan)
            {
            case Quiet:
                  u8g2.drawXBMP(90, 32, u8g2_fun_quiet_width, u8g2_fun_quiet_height, fun_quiet);
                  break;
            case Medium:
                  u8g2.drawXBMP(90, 32, u8g2_fun_medium_width, u8g2_fun_medium_height, fun_medium);
                  break;
            case Maximum:
                  u8g2.drawXBMP(90, 32, u8g2_fun_maximum_width, u8g2_fun_maximum_height, fun_maximum);
                  break;
                  ;
            case Auto_fun:
                  u8g2.drawXBMP(90, 32, u8g2_fun_auto_width, u8g2_fun_auto_height, fun_auto);
                  break;
            }

            if (status.swing_v == Auto_swing)
            {
                  u8g2.drawXBMP(90, 49, u8g2_swing_run_width, u8g2_swing_run_height, swing_run);
            }
            else
                  u8g2.drawXBMP(90, 49, u8g2_swing_stop_width, u8g2_swing_stop_height, swing_stop);

            break;
      }

      u8g2.sendBuffer();
}
