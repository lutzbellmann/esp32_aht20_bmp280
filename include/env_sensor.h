#pragma once

#include <esp_err.h>
#include <driver/i2c_master.h>
#include <driver/gpio.h>

typedef struct {
    float temperature;  /* °C  — from AHT20 */
    float humidity;     /* %RH — from AHT20 */
    float pressure;     /* hPa — from BMP280 */
} env_sensor_reading_t;

/* Internal calibration data + device handles; declare on the stack or statically. */
typedef struct {
    i2c_master_dev_handle_t aht20;
    i2c_master_dev_handle_t bmp280;
    /* BMP280 trimming coefficients */
    uint16_t dig_T1;
    int16_t  dig_T2, dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
} env_sensor_t;

/**
 * @brief Create an I2C master bus on the given pins.
 *
 * Convenience wrapper — skip if a bus already exists.
 */
esp_err_t env_sensor_create_bus(i2c_port_num_t port, i2c_master_bus_handle_t *bus_out);

/**
 * @brief Initialize AHT20 and BMP280 on an existing I2C bus.
 *
 * @param bus         I2C master bus handle
 * @param handle      Handle to populate (caller-allocated)
 */
esp_err_t env_sensor_init(i2c_master_bus_handle_t bus, env_sensor_t *handle);

/**
 * @brief Trigger a measurement and return temperature, humidity, and pressure.
 */
esp_err_t env_sensor_read(env_sensor_t *handle, env_sensor_reading_t *out);