#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;
using namespace TaskKit;

// en: Protect shared bus (I2C/SPI) across TaskKit tasks with Mutex
// ja: TaskKit タスク間で共有バスを Mutex で保護
Mutex busMutex;
Task sensorTask;
Task loggerTask;

void setup()
{
  Serial.begin(115200);

  sensorTask.startLoop(
      [] {
        Mutex::LockGuard lock(busMutex);
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
      TaskConfig{.name = "sensor", .priority = 2});

  loggerTask.startLoop(
      [] {
        Mutex::LockGuard lock(busMutex);
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
      TaskConfig{.name = "logger", .priority = 2});
}

void loop()
{
  delay(1);
}
