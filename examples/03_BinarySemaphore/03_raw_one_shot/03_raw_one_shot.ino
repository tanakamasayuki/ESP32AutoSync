#include <Arduino.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;

// en: One-shot semaphore between raw FreeRTOS tasks
// ja: 生 FreeRTOS タスク間のワンショットセマフォ
BinarySemaphore sem;

void signaler(void * /*pv*/)
{
  delay(500);
  sem.give();
  vTaskDelete(nullptr);
}

void waiter(void * /*pv*/)
{
  if (sem.take(WaitForever))
  {
    Serial.println("[BinarySemaphore/raw] got signal");
  }
  vTaskDelete(nullptr);
}

void setup()
{
  Serial.begin(115200);
  xTaskCreatePinnedToCore(signaler, "signaler", 4096, nullptr, 2, nullptr, 0);
  xTaskCreatePinnedToCore(waiter, "waiter", 4096, nullptr, 2, nullptr, 1);
}

void loop()
{
  delay(1);
}
