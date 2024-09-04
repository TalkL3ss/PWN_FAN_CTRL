---Mixed Version of pwm Fan control---
# PWN_FAN_CTRL
control a pwn fan (4 pins) 
1. esp8266 (nodeMCU)
2. ardunio (for me uno worked fine)
3. PWM FAN (12dcv)
4. 12dcv Powersupplier
5. 5 dcv powersupplier



***Note****
i fried my esp8266 CH340 chip (usb to serial), so a quick way to bypass it and still able to write a new frimware
its using arduino uno body by those steps.
  1. Remove the atmega chip
  2. Connect TX from the arduino -> RX of the ESP
  3. RX of the arduino -> TX of the ESP
  4. GND -> GND
  5. 3.3v from arduino -> VIN of the ESP
  6. on the ESP GPIO0 for me (D3) to GND (On the ESP)
  7. Reset of the Arduino -> RST of the ESP
  8. Connect the Arduino to the computer (Duoble check all the jumper wire before connect)
  9. Press on the RST
  10. Open the Arduino IDE
  11. select your sketch
  12. select the COM port of the Arduino
  13. select the ESP8266 from the Board Menu (In my case "NodeMCU 1.0 (ESP-12E Module)"
  14. Upload the sketch
  15. when finish upload you can disconnect the GPIO0 from the GND (on the ESP) and press RST button. 
      the arduino will be used as USB to Serial Convertor if needed. if not you can disconnect all and let the ESP do its work.
      **if you get Time out after upload the scketch disconnect the ESP and check it.
