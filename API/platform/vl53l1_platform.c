
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

/*******************************************************************************
 * Copyright 2024, LooUQ Incorporated
 * 
 * ESP-IDF platform abstraction and make directives are copyright LooUQ 
 * Incorporated. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the above conditions are met. 
 * Including the inclusion of this notice.
 * 
 * Licensed under the MIT open source license.
*******************************************************************************/

#include "vl53l1_platform.h"

#include <string.h>
#include <time.h>
#include <math.h>

#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "[VL53L1_PLATFORM]";

static i2c_master_dev_handle_t devHndl = NULL;

esp_log_level_t VL53L1_SetLoggingLevel(esp_log_level_t logLevel)
{
    ESP_LOGI(TAG, "Previous VL53L1 logging level=%d", esp_log_level_get(TAG));
    esp_log_level_set(TAG, logLevel);
    esp_log_level_t newLevel = esp_log_level_get(TAG);
    ESP_LOGI(TAG, "New VL53L1 logging level=%d", newLevel);
    return newLevel;
}


void VL53L1_SetDeviceHandle(i2c_master_dev_handle_t esp_DeviceHandle)
{
    ESP_LOGD(TAG, "(SetDeviceHandle) devHndl=%p", esp_DeviceHandle);
    devHndl = esp_DeviceHandle;
}


/* ST platform 
 * --------------------------------------------------------------------------------------------- */

int8_t VL53L1_WriteMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) 
{
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t regAddr = (uint8_t)(index >> 8);
    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, &regAddr, 1, VL53L1_DEFAULT_TIMEOUT));                         // index (register)
    regAddr = (uint8_t)(index);
    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, &regAddr, 1, VL53L1_DEFAULT_TIMEOUT));

    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, pdata, count, VL53L1_DEFAULT_TIMEOUT));                        // data
	return 0;
}


int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count)
{
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t regAddr = (uint8_t)(index >> 8);
    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, &regAddr, 1, VL53L1_DEFAULT_TIMEOUT));                         // index (register)
    regAddr = (uint8_t)(index);
    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, &regAddr, 1, VL53L1_DEFAULT_TIMEOUT));

    ESP_ERROR_CHECK(i2c_master_receive(devHndl, pdata, count, VL53L1_DEFAULT_TIMEOUT));                         // data
	return 0;
}


int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) 
{
    ESP_LOGD(TAG, "(WrByte) devHndl=%p, index=%2X, data=%2X", devHndl, index, data);
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t wrBffr[3];
    wrBffr[0] = index >> 8; 
    wrBffr[1] = index & 0xff;
    wrBffr[2] = data;

    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, wrBffr, 3, VL53L1_DEFAULT_TIMEOUT));
	return 0;
}


int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data)
{
    ESP_LOGD(TAG, "(WrWord) devHndl=%p, index=%2X, data=%4X", devHndl, index, data);
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t wrBffr[4];
    wrBffr[0] = index >> 8; 
    wrBffr[1] = index & 0xff;
    wrBffr[2] = data >> 8; 
    wrBffr[3] = data & 0xff;

    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, wrBffr, 4, VL53L1_DEFAULT_TIMEOUT));
	return 0;
}


int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) 
{
    ESP_LOGD(TAG, "(WrDWord) devHndl=%p, index=%2X, data=%" PRIu32, devHndl, index, data);
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t wrBffr[6];
    wrBffr[0] = index >> 8; 
    wrBffr[1] = index & 0xff;
    wrBffr[2] = data >> 24; 
    wrBffr[3] = data >> 16;
    wrBffr[4] = data >> 8; 
    wrBffr[5] = data & 0xff;

    ESP_ERROR_CHECK(i2c_master_transmit(devHndl, wrBffr, 4, VL53L1_DEFAULT_TIMEOUT));
	return 0;
}


int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *data) 
{
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);
    
    uint8_t indxBffr[2] = {0}; 
    indxBffr[0] = index >> 8; 
    indxBffr[1] = index & 0xff;

    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHndl, indxBffr, 2, data, 1, VL53L1_DEFAULT_TIMEOUT));
    ESP_LOGD(TAG, "(RdByte) devHndl=%p, index=%2X, data=%2X", devHndl, index, *data);
	return 0;
}


int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) 
{
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t indxBffr[2] = {0}; 
    indxBffr[0] = index >> 8; 
    indxBffr[1] = index & 0xff;

    uint8_t valueBffr[2];
    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHndl, indxBffr, 2, valueBffr, 2, VL53L1_DEFAULT_TIMEOUT));
    *data = valueBffr[0] << 8 | valueBffr[1];
    ESP_LOGD(TAG, "(RdWord) devHndl=%p, index=%2X, data=%4X", devHndl, index, *data);
    return 0;
}


int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) 
{
    ESP_ERROR_CHECK(devHndl == NULL || dev != TOF_ESP);

    uint8_t indxBffr[2] = {0}; 
    indxBffr[0] = index >> 8; 
    indxBffr[1] = index & 0xff;

    uint8_t valueBffr[4];
    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHndl, indxBffr, 2, valueBffr, 4, VL53L1_DEFAULT_TIMEOUT));
    *data = valueBffr[0] << 24 | valueBffr[1] << 16 | valueBffr[2] << 8 | valueBffr[3];
    ESP_LOGD(TAG, "(RdDWord) devHndl=%p, index=%2X, data=%" PRIu32 , devHndl, index, *data);
	return 0;
}


int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms)
{
    // dependent on sdkConfig (menuConfig) for portTICK_PERIOD_MS
    vTaskDelay(wait_ms / portTICK_PERIOD_MS);
	return 0;
}
