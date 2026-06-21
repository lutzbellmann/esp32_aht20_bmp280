# esp32_aht20_bmp280: basic example

Reads temperature, humidity, and pressure from an AHT20 + BMP280 sensor pair
every 2 seconds and logs the result.

## Wiring

- AHT20 + BMP280 on the same I2C bus
- SDA → GPIO21, SCL → GPIO22 (change `EXAMPLE_I2C_SDA_GPIO`/`EXAMPLE_I2C_SCL_GPIO` in `main/main.c` if needed)
- BMP280 SDO pin tied to GND (uses `ENV_SENSOR_BMP280_ADDR_LOW`; switch to `ENV_SENSOR_BMP280_ADDR_HIGH` if SDO is tied to VCC)

## Build and flash

```bash
idf.py set-target esp32
idf.py build flash monitor
```

## Expected output

```
I (1234) env_sensor_example: T=22.41°C  RH=41.30%  P=1013.25hPa
```
