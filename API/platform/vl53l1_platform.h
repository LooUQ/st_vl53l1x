/**
 * @file  vl53l1_platform.h
 * @brief Those platform functions are platform dependent and have to be implemented by the user
 */
 
#ifndef _VL53L1_PLATFORM_H_
#define _VL53L1_PLATFORM_H_

#include "esp_log.h"

#include "vl53l1_types.h"
#include "driver/i2c_types.h"

#define VL53L1_DEFAULT_TIMEOUT 50

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
	uint32_t dummy;
} VL53L1_Dev_t;

typedef VL53L1_Dev_t *VL53L1_DEV;

/**
 * @brief Placeholder value to signal that the ESP new I2C driver abstraction is being honored.
 */
#define TOF_ESP 127

/**
 * @brief ESP Master-Slave (new I2C driver) pass in a device handle to I/O (not simply the device address). This is 
 * contrary to the pattern for the ST provided platform layer. SetDeviceHandle allows for a side channel configuration
 * of the device address, which is a private member of the device handle.
 * 
 * @note The device associated with the handle MUST HAVE BEEN PREVIOUSLY added to the bus.
 * 
 * @param esp_DeviceHandle New ESP I2C driver device handle (with private device address).
 */
void VL53L1_SetDeviceHandle(i2c_master_dev_handle_t esp_DeviceHandle);


esp_log_level_t VL53L1_SetLoggingLevel(esp_log_level_t logLevel);

// #define INDEX_TO_UINT8_BFFR(indx,uint8_bffr)  uint8_bffr[0] = indx >> 8; uint8_bffr[1] = indx & 0xff;
// #define CREATE_INDEX_BFFR(indx)  uint8_t indxBffr[2] = {0}; indxBffr[0] = indx >> 8; indxBffr[1] = indx & 0xff;

/** @brief VL53L1_WriteMulti() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WriteMulti(
		uint16_t 			dev,
		uint16_t      index,
		uint8_t      *pdata,
		uint32_t      count);

/** @brief VL53L1_ReadMulti() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_ReadMulti(
		uint16_t 			dev,
		uint16_t      index,
		uint8_t      *pdata,
		uint32_t      count);
/** @brief VL53L1_WrByte() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrByte(
		uint16_t    dev,
		uint16_t    index,
		uint8_t     data);
/** @brief VL53L1_WrWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrWord(
		uint16_t dev,
		uint16_t      index,
		uint16_t      data);
/** @brief VL53L1_WrDWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrDWord(
		uint16_t dev,
		uint16_t      index,
		uint32_t      data);
/** @brief VL53L1_RdByte() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdByte(
		uint16_t dev,
		uint16_t      index,
		uint8_t      *pdata);
/** @brief VL53L1_RdWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdWord(
		uint16_t dev,
		uint16_t      index,
		uint16_t     *pdata);
/** @brief VL53L1_RdDWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdDWord(
		uint16_t dev,
		uint16_t      index,
		uint32_t     *pdata);
/** @brief VL53L1_WaitMs() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WaitMs(
		uint16_t dev,
		int32_t       wait_ms);

#ifdef __cplusplus
}
#endif

#endif
