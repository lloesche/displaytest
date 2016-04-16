//   Copyright 2016 Lukas Lösche <lloesche@fedoraproject.org>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define OLED_SCL   13
#define OLED_SDA   12
#define OLED_RES   11
#define OLED_DC    10

#define SPI_fps    12
#define I2C_fps     9
#include <U8glib.h>

unsigned long last_SPI_refresh = 0;
unsigned long last_I2C_refresh = 0;
unsigned long SPI_interval = 1000 / SPI_fps;
unsigned long I2C_interval = 1000 / I2C_fps;
int SPI_angle = 0;
int I2C_angle = 0;

// SPI
// http://www.banggood.com/0_96-Inch-6Pin-12864-SPI-Blue-Yellow-OLED-Display-Module-For-Arduino-p-969145.html
U8GLIB_SSD1306_128X64 u8g_spi(OLED_SCL, OLED_SDA, U8G_PIN_NONE, OLED_DC, OLED_RES);

// I2C
// http://www.banggood.com/0_96-Inch-4Pin-White-IIC-I2C-OLED-Display-Module-12864-LED-For-Arduino-p-958196.html
// SDA = A4
// SCL = A5
U8GLIB_SSD1306_128X64 u8g_i2c(U8G_I2C_OPT_FAST);

void setup() {
}

unsigned int SPI_maxfps = 0;
unsigned int I2C_maxfps = 0;
void loop() {
  // SPI DISPLAY
  if ((unsigned long)(millis() - last_SPI_refresh) >= SPI_interval) {
    SPI_angle -= 6;
    if (SPI_angle <= 0) { SPI_angle = 360 + SPI_angle; }

    last_SPI_refresh = millis();
    u8g_spi.firstPage();  
    do {
      draw(u8g_spi, SPI_angle, SPI_maxfps);
    } while( u8g_spi.nextPage() );
    SPI_maxfps = 1000 / (millis() - last_SPI_refresh);
  }

  // I2C DISPLAY
  if ((unsigned long)(millis() - last_I2C_refresh) >= I2C_interval) {
    I2C_angle -= 6;
    if(I2C_angle <= 0) { I2C_angle = 360 + I2C_angle; }

    last_I2C_refresh = millis();
    u8g_i2c.firstPage();
    do {
      draw(u8g_i2c, I2C_angle, I2C_maxfps);
    } while( u8g_i2c.nextPage() );
    I2C_maxfps = 1000 / (millis() - last_I2C_refresh);
  }
}

const int cx = 64;
const int cy = 42;
const int r = 20;
const int x = cx + 0;
const int y = cy - r + 3;
void draw(U8GLIB u8g, int angle, int maxfps) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(0, 20, "MAX FPS: ");
  u8g.setPrintPos(70, 20);
  u8g.print(maxfps);
  u8g.drawCircle(cx, cy, r);
  float radians = 0.01745329251 * angle;  // Pi/180 * angle
  float c = cos(radians);
  float s = sin(radians);
  int nx = (c * (x - cx)) + (s * (y - cy)) + cx;
  int ny = (c * (y - cy)) - (s * (x - cx)) + cy;
  u8g.drawLine(cx, cy, nx, ny);
}

