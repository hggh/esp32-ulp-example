#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_sleep.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp32/ulp.h"
#include "ulp_main.h"

#include "lwip/err.h"
#include "lwip/sys.h"

static const char *TAG = "whs";
extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

static void init_ulp_program() {
  esp_err_t err = ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
  ESP_ERROR_CHECK(err);

  gpio_num_t gpio_p1 = GPIO_NUM_26;
  gpio_num_t gpio_p2 = GPIO_NUM_33;
  gpio_num_t gpio_p3 = GPIO_NUM_32;

  //    GPIO 26 - RTC 7
  //    GPIO 33 - RTC 8
  //    GPIO 32 - RTC 9

  rtc_gpio_init(gpio_p1);
  rtc_gpio_set_direction(gpio_p1, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(gpio_p1);
  rtc_gpio_pullup_dis(gpio_p1);
  rtc_gpio_hold_en(gpio_p1);
  rtc_gpio_isolate(GPIO_NUM_26);

  rtc_gpio_init(gpio_p2);
  rtc_gpio_set_direction(gpio_p2, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(gpio_p2);
  rtc_gpio_pullup_dis(gpio_p2);
  rtc_gpio_hold_en(gpio_p2);
  rtc_gpio_isolate(GPIO_NUM_33);

  rtc_gpio_init(gpio_p3);
  rtc_gpio_set_direction(gpio_p3, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(gpio_p3);
  rtc_gpio_pullup_dis(gpio_p3);
  rtc_gpio_hold_en(gpio_p3);
  rtc_gpio_isolate(GPIO_NUM_32);

  ulp_set_wakeup_period(0, 20 * 1000); // 20 ms
  err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
  ESP_ERROR_CHECK(err);
}

void app_main() {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  // disable bluetooth
  esp_bluedroid_disable();
  esp_bt_controller_disable();

  // suppress boot message
  esp_deep_sleep_disable_rom_logging();


  ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause != ESP_SLEEP_WAKEUP_ULP) {
    printf("Not ULP wakeup, initializing ULP\n");
    init_ulp_program();
  }
  printf("%d - %d - %d : %d \n", ulp_p1_status & UINT16_MAX, ulp_p2_status & UINT16_MAX, ulp_p3_status & UINT16_MAX, ulp_event_counter & UINT16_MAX);
  printf("Entering deep sleep\n\n");
  ESP_ERROR_CHECK( esp_sleep_enable_ulp_wakeup() );
  esp_deep_sleep_start();

}
