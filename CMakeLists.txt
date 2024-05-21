idf_component_register(SRCS "API/core/VL53L1X_api.c" "API/core/VL53L1X_calibration.c" "API/platform/vl53l1_platform.c"
    INCLUDE_DIRS "API/core" "API/platform" 
    REQUIRES "driver" "freertos"
)