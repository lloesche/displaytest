# Arduino SSD1306 Display Test [![Build Status](https://travis-ci.org/lloesche/displaytest.svg?branch=master)](https://travis-ci.org/lloesche/displaytest)
![Display Test](https://raw.githubusercontent.com/lloesche/displaytest/master/misc/IMG_0547.jpg "Display Test")

I bought two cheap 128x64 OLED displays from China.
One using a [SPI connection](http://www.banggood.com/0_96-Inch-6Pin-12864-SPI-Blue-Yellow-OLED-Display-Module-For-Arduino-p-969145.html)
the other using an [I2C connection](http://www.banggood.com/0_96-Inch-4Pin-White-IIC-I2C-OLED-Display-Module-12864-LED-For-Arduino-p-958196.html).
This test code is using [the excellent U8Glib](https://github.com/olikraus/u8glib). It took me an hour or so to figure out the right way to wire and initialise these displays so I'm documenting it here for others to find.

The MAX FPS shown is solely based on the time it takes to refresh that one screen. It does not take into account any additional processing that has to take place or multiple screens being attached to the same Arduino.

####Video
[![Arduino SSD1306 Display Test](http://img.youtube.com/vi/0KHxU5P0x3A/0.jpg)](http://www.youtube.com/watch?v=0KHxU5P0x3A)
