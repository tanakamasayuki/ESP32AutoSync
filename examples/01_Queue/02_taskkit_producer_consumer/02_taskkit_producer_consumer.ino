#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

// en: Queue between two TaskKit tasks (producer/consumer), depth=8
// ja: TaskKit の2タスク間で使うキュー（送受信）、深さ8
ESP32AutoSync::Queue<int> q(8);
ESP32TaskKit::Task producer;
ESP32TaskKit::Task consumer;

void setup()
{
  Serial.begin(115200);

  producer.startLoop(
      []
      {
        static int value = 0;
        q.send(value++, 1000);
        if (!q.send(value++, 1000))
        {
          Serial.println("[Queue/TaskKit] send failed");
        }
        delay(500);
        return true;
      },
      ESP32TaskKit::TaskConfig{.name = "producer", .priority = 2});

  consumer.startLoop(
      []
      {
        int v = 0;
        if (q.receive(v))
        {
          Serial.printf("[Queue/TaskKit] received: %d\n", v);
        }
        delay(1);
        return true;
      },
      ESP32TaskKit::TaskConfig{.name = "consumer", .priority = 2});
}

void loop()
{
  delay(1);
}
