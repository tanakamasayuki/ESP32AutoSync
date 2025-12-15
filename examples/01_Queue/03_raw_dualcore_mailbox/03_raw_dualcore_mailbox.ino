#include <Arduino.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;

// en: Core0 -> Core1 mailbox using Queue (depth=8)
// ja: Queue でコア0→コア1 のメールボックス（深さ8）
Queue<int> q(8);

void sender(void * /*pv*/)
{
  int counter = 0;
  for (;;)
  {
    q.send(counter++, 1000);
    delay(200);
  }
}

void receiver(void * /*pv*/)
{
  int v = 0;
  for (;;)
  {
    if (q.receive(v))
    {
      Serial.printf("[Queue/raw] core=%d recv=%d\n", xPortGetCoreID(), v);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  xTaskCreatePinnedToCore(sender, "sender", 4096, nullptr, 2, nullptr, 0);
  xTaskCreatePinnedToCore(receiver, "receiver", 4096, nullptr, 2, nullptr, 1);
}

void loop()
{
  delay(1);
}
