# This is a rough, immature project right now! 
## Part of a customer POC that served its purpose back then. I do plan on improving it in the coming months for another project which is production. Note that project will not be ESP-IDF, but rather Nordic NCS (Zephyr).

# LooUQ ESP-IDF Component for STMicroelectronics (ST) VL53L1X time-of-flight (TOF) distance sensor

This package allows for inclusion of the VL53L1X TOF sensor driver provided by STMicroelectronics in your Espressif ESP-IDF projects as an ESP-IDF component.

## To install in your ESP-IDF project
1. Copy the full st_vl53l1x folder into your IDF project's "components" folder
1. Add "st_vl53l1x" to your main folder's CMakeList.txt *REQUIRES* list (see example below).
1. Note that driver component is required for I2C support

> idf_component_register( \
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SRCS "main.c" "projUtility.c" \
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;INCLUDE_DIRS "." \
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;REQUIRES ${requires} nvs_flash esp_timer esp_wifi lwip esp-tls esp_http_client driver st_vl53l1x \
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;EMBED_TXTFILES memfault_root_cert.pem \
>)


#### Base driver is copyright STMicroelectronics, ESP-IDF component and platform adaption is copyright LooUQ Incorporated.
