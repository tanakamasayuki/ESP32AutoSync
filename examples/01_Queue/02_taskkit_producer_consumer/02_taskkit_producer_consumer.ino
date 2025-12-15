#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;
using namespace TaskKit;

// en: Queue between two TaskKit tasks (producer/consumer), depth=8
// ja: TaskKit の2タスク間で使うキュー（送受信）、深さ8
Queue<int> q(8);
Task producer;
Task consumer;

void setup()
{
  Serial.begin(115200);

  producer.startLoop(
      []
      {
        static int value = 0;
        q.send(value++, 1000);
        delay(500);
        return true;
      },
      TaskConfig{.name = "producer", .priority = 2});

  consumer.startLoop(
      []
      {
        int v = 0;
        if (q.receive(v, WaitForever))
        {
          Serial.printf("[Queue/TaskKit] received: %d\n", v);
        }
        delay(1);
        return true;
      },
      TaskConfig{.name = "consumer", .priority = 2});
}

void loop()
{
  delay(1);
}
