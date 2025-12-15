#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;
using namespace TaskKit;

constexpr uint32_t kBitRxReady = 1 << 0;
constexpr uint32_t kBitTxDone = 1 << 1;

// en: Notify in bits mode (TaskKit tasks)
// ja: Notify ビットモード（TaskKit タスクで利用）
Notify evt(Notify::Mode::Bits); // en/ja: preset to bits mode
Task producer;
Task consumer;

void setup()
{
  Serial.begin(115200);

  producer.startLoop(
      [] {
        evt.setBits(kBitRxReady);
        delay(200);
        evt.setBits(kBitTxDone);
        delay(800);
        return true;
      },
      TaskConfig{.name = "bits-setter", .priority = 2});

  consumer.startLoop(
      [] {
        if (evt.waitBits(kBitRxReady | kBitTxDone, true, true))
        {
          Serial.println("[Notify/bits] RX ready & TX done");
        }
        return true;
      },
      TaskConfig{.name = "bits-waiter", .priority = 2});
}

void loop()
{
  delay(1);
}
