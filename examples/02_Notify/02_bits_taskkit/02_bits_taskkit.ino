#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

constexpr uint32_t kBitRxReady = 1 << 0;
constexpr uint32_t kBitTxDone = 1 << 1;

// en: Notify in bits mode (TaskKit tasks)
// ja: Notify ビットモード（TaskKit タスクで利用）
// en: preset to bits mode
// ja: ビットモードで初期化
ESP32AutoSync::Notify evt(ESP32AutoSync::Notify::Mode::Bits);
TaskKit::Task producer;
TaskKit::Task consumer;

void setup()
{
  Serial.begin(115200);

  producer.startLoop(
      [] {
        if (!evt.setBits(kBitRxReady))
        {
          Serial.println("[Notify/bits] setBits RX failed");
        }
        delay(200);
        if (!evt.setBits(kBitTxDone))
        {
          Serial.println("[Notify/bits] setBits TX failed");
        }
        delay(800);
        return true;
      },
      TaskKit::TaskConfig{.name = "bits-setter", .priority = 2});

  consumer.startLoop(
      [] {
        if (evt.waitBits(kBitRxReady | kBitTxDone, true, true))
        {
          Serial.println("[Notify/bits] RX ready & TX done");
        }
        return true;
      },
      TaskKit::TaskConfig{.name = "bits-waiter", .priority = 2});
}

void loop()
{
  delay(1);
}
