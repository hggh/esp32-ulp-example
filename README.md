# esp32-ulp-example

This ESP32 ULP deep sleep example will check if three GPIOs toggle it's state and will wakeup the SoC.

GPIOs uses:
 * GPIO 26 aka RTC 7
 * GPIO 33 aka RTC 8
 * GPIO 32 aka RTC 9
 
All GPIOs needs a external pullup resistor!

The ULP program runs in background and will not be stopped if we wakeup the SoC (main.c). The ULP program exists with (halt) and will be started every [20ms](https://github.com/hggh/esp32-ulp-example/blob/master/src/main.c#L57).

The ULP program has four global variables that will be shared with the SoC program:

 * p1_status
 * p2_status
 * p3_status
 * event_counter

The first three variables hold the state of the pin. Can be high (1) or low (0). The event_counter is a 16 uint that will count the pin change for all three pins.

The ULP program has also three private variables:

 * p1_status_next
 * p2_status_next
 * p3_status_next
 
These three variables are used to detect the pin change.

TODO:
 * check power usage of the chip, because ULP FSM runs every 20ms?
 * if a pin change is happend within 20ms (from HIGH to LOW and back to HIGH) it will not detected?
