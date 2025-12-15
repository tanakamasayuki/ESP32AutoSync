#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

// en: Protect shared bus (I2C/SPI) across TaskKit tasks with Mutex
// ja: TaskKit タスク間で共有バスを Mutex で保護
ESP32AutoSync::Mutex busMutex;
TaskKit::Task sensorTask;
TaskKit::Task loggerTask;

void setup()
{
  Serial.begin(115200);

  sensorTask.startLoop(
      [] {
        ESP32AutoSync::Mutex::LockGuard lock(busMutex);
        if (lock.locked())
        {
          // en: simulate I2C/SPI transaction / ja: I2C/SPI 通信を模擬
          delay(50);
        }
        else
        {
          Serial.println("[Mutex/TaskKit] lock failed");
        }
        delay(200);
        return true;
      },
      TaskKit::TaskConfig{.name = "sensor", .priority = 2});

  loggerTask.startLoop(
      [] {
        ESP32AutoSync::Mutex::LockGuard lock(busMutex);
        if (lock.locked())
        {
          Serial.println("[Mutex/TaskKit] logging with bus lock");
        }
        else
        {
          Serial.println("[Mutex/TaskKit] lock failed");
        }
        delay(500);
        return true;
      },
      TaskKit::TaskConfig{.name = "logger", .priority = 2});
}

void loop()
{
  delay(1);
}
