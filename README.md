# esp32_aht20_bmp280

ESP-IDF component for reading temperature, humidity, and pressure from an
**AHT20** + **BMP280** sensor pair over I2C, using the ESP-IDF I2C *master*
driver (`driver/i2c_master.h`).

Requires **ESP-IDF >= 5.2**.

## Installation

```bash
idf.py add-dependency "lbellmann/esp32_aht20_bmp280^0.1.0"
```

Or add it manually to your `main/idf_component.yml`:

```yaml
dependencies:
  lbellmann/esp32_aht20_bmp280: "^0.1.0"
```

## Usage

```c
#include "env_sensor.h"

i2c_master_bus_handle_t bus;
ESP_ERROR_CHECK(env_sensor_create_bus(GPIO_NUM_21, GPIO_NUM_22, 0, &bus));

env_sensor_t sensor;
ESP_ERROR_CHECK(env_sensor_init(bus, ENV_SENSOR_BMP280_ADDR_LOW, &sensor));

env_sensor_reading_t reading;
ESP_ERROR_CHECK(env_sensor_read(&sensor, &reading));
printf("%.2f°C  %.2f%%RH  %.2fhPa\n",
       reading.temperature, reading.humidity, reading.pressure);
```

See [`examples/basic`](examples/basic) for a complete, runnable project.

## Wiring

| Signal | Notes |
|--------|-------|
| AHT20 address | fixed at `0x38` |
| BMP280 address | `0x76` (SDO → GND) or `0x77` (SDO → VCC) — pass via `ENV_SENSOR_BMP280_ADDR_LOW`/`_HIGH` |
| SDA / SCL | any free GPIOs, internal pull-ups are enabled by `env_sensor_create_bus` |
| HINT: for the popular I2C sensor modules available on marketplaces choose `ENV_SENSOR_BMP280_ADDR_HIGH` |

## API

| Function | Description |
|----------|--------------|
| `env_sensor_create_bus()` | Create an I2C master bus on the given pins (skip if a bus already exists) |
| `env_sensor_init()` | Probe and initialize AHT20 + BMP280 on an existing bus |
| `env_sensor_read()` | Trigger a measurement and return temperature, humidity, and pressure |

## License

Apache-2.0, see [LICENSE](LICENSE).
