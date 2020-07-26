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


example output:
```

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0018,len:4
load:0x3fff001c,len:1224
load:0x40078000,len:12020
load:0x40080400,len:3524
entry 0x40080628
␛[0;32mI (292) cpu_start: Pro cpu up.␛[0m
␛[0;32mI (292) cpu_start: Application information:␛[0m
␛[0;32mI (292) cpu_start: Project name:     esp32-ulp-example␛[0m
␛[0;32mI (295) cpu_start: App version:      36e659b␛[0m
␛[0;32mI (300) cpu_start: Compile time:     Jul 26 2020 18:37:12␛[0m
␛[0;32mI (306) cpu_start: ELF file SHA256:  c26b0db18b023119...␛[0m
␛[0;32mI (312) cpu_start: ESP-IDF:          HEAD-HASH-NOTFOUND␛[0m
␛[0;32mI (318) cpu_start: Starting app cpu, entry point is 0x40082238␛[0m
␛[0;32mI (0) cpu_start: App cpu up.␛[0m
␛[0;32mI (329) heap_init: Initializing. RAM available for dynamic allocation:␛[0m
␛[0;32mI (335) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM␛[0m
␛[0;32mI (341) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM␛[0m
␛[0;32mI (348) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM␛[0m
␛[0;32mI (354) heap_init: At 3FFBDB5C len 00000004 (0 KiB): DRAM␛[0m
␛[0;32mI (360) heap_init: At 3FFC8FA8 len 00017058 (92 KiB): DRAM␛[0m
␛[0;32mI (366) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM␛[0m
␛[0;32mI (372) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM␛[0m
␛[0;32mI (379) heap_init: At 400931C0 len 0000CE40 (51 KiB): IRAM␛[0m
␛[0;32mI (385) cpu_start: Pro cpu start user code␛[0m
␛[0;32mI (404) spi_flash: detected chip: generic␛[0m
␛[0;32mI (405) spi_flash: flash io: dio␛[0m
␛[0;32mI (405) cpu_start: Starting scheduler on PRO CPU.␛[0m
␛[0;32mI (0) cpu_start: Starting scheduler on APP CPU.␛[0m
␛[0;31mE (536) BT_LOG: Bluedroid already disabled
␛[0m
␛[0;32mI (536) whs: [APP] IDF version: HEAD-HASH-NOTFOUND␛[0m
Not ULP wakeup, initializing ULP
0 - 0 - 0 : 0 
Entering deep sleep

␛[0;32mI (274) cpu_start: Pro cpu up.␛[0m
␛[0;32mI (274) cpu_start: Application information:␛[0m
␛[0;32mI (274) cpu_start: Project name:     esp32-ulp-example␛[0m
␛[0;32mI (277) cpu_start: App version:      36e659b␛[0m
␛[0;32mI (282) cpu_start: Compile time:     Jul 26 2020 18:37:12␛[0m
␛[0;32mI (288) cpu_start: ELF file SHA256:  c26b0db18b023119...␛[0m
␛[0;32mI (294) cpu_start: ESP-IDF:          HEAD-HASH-NOTFOUND␛[0m
␛[0;32mI (300) cpu_start: Starting app cpu, entry point is 0x40082238␛[0m
␛[0;32mI (0) cpu_start: App cpu up.␛[0m
␛[0;32mI (311) heap_init: Initializing. RAM available for dynamic allocation:␛[0m
␛[0;32mI (318) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM␛[0m
␛[0;32mI (324) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM␛[0m
␛[0;32mI (330) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM␛[0m
␛[0;32mI (336) heap_init: At 3FFBDB5C len 00000004 (0 KiB): DRAM␛[0m
␛[0;32mI (342) heap_init: At 3FFC8FA8 len 00017058 (92 KiB): DRAM␛[0m
␛[0;32mI (348) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM␛[0m
␛[0;32mI (354) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM␛[0m
␛[0;32mI (361) heap_init: At 400931C0 len 0000CE40 (51 KiB): IRAM␛[0m
␛[0;32mI (367) cpu_start: Pro cpu start user code␛[0m
␛[0;32mI (386) spi_flash: detected chip: generic␛[0m
␛[0;32mI (387) spi_flash: flash io: dio␛[0m
␛[0;32mI (387) cpu_start: Starting scheduler on PRO CPU.␛[0m
␛[0;32mI (0) cpu_start: Starting scheduler on APP CPU.␛[0m
␛[0;31mE (518) BT_LOG: Bluedroid already disabled
␛[0m
␛[0;32mI (518) whs: [APP] IDF version: HEAD-HASH-NOTFOUND␛[0m
1 - 1 - 0 : 1 
Entering deep sleep

␛[0;32mI (274) cpu_start: Pro cpu up.␛[0m
␛[0;32mI (274) cpu_start: Application information:␛[0m
␛[0;32mI (274) cpu_start: Project name:     esp32-ulp-example␛[0m
␛[0;32mI (277) cpu_start: App version:      36e659b␛[0m
␛[0;32mI (282) cpu_start: Compile time:     Jul 26 2020 18:37:12␛[0m
␛[0;32mI (288) cpu_start: ELF file SHA256:  c26b0db18b023119...␛[0m
␛[0;32mI (294) cpu_start: ESP-IDF:          HEAD-HASH-NOTFOUND␛[0m
␛[0;32mI (300) cpu_start: Starting app cpu, entry point is 0x40082238␛[0m
␛[0;32mI (0) cpu_start: App cpu up.␛[0m
␛[0;32mI (311) heap_init: Initializing. RAM available for dynamic allocation:␛[0m
␛[0;32mI (318) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM␛[0m
␛[0;32mI (324) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM␛[0m
␛[0;32mI (330) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM␛[0m
␛[0;32mI (336) heap_init: At 3FFBDB5C len 00000004 (0 KiB): DRAM␛[0m
␛[0;32mI (342) heap_init: At 3FFC8FA8 len 00017058 (92 KiB): DRAM␛[0m
␛[0;32mI (348) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM␛[0m
␛[0;32mI (354) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM␛[0m
␛[0;32mI (361) heap_init: At 400931C0 len 0000CE40 (51 KiB): IRAM␛[0m
␛[0;32mI (367) cpu_start: Pro cpu start user code␛[0m
␛[0;32mI (386) spi_flash: detected chip: generic␛[0m
␛[0;32mI (387) spi_flash: flash io: dio␛[0m
␛[0;32mI (387) cpu_start: Starting scheduler on PRO CPU.␛[0m
␛[0;32mI (0) cpu_start: Starting scheduler on APP CPU.␛[0m
␛[0;31mE (518) BT_LOG: Bluedroid already disabled
␛[0m
␛[0;32mI (518) whs: [APP] IDF version: HEAD-HASH-NOTFOUND␛[0m
1 - 1 - 1 : 2 
Entering deep sleep


```
