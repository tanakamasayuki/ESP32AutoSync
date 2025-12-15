#include <ESP32AutoTask.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;

// en: Notify in counter mode (auto-lock on first use)
// ja: Notify カウンタモード（初回使用でモード確定）
Notify n; // en/ja: counter mode locks on first use

void setup()
{
  Serial.begin(115200);
  ESP32AutoTask::AutoTask.begin();
}

// en: Producer increments counter
// ja: 送信側がカウンタを増やす
void LoopCore0_Normal()
{
  if (!n.notify()) // en/ja: auto-locks mode to counter
  {
    Serial.println("[Notify/counter] notify failed");
  }
}

// en: Consumer takes notifications
// ja: 受信側が通知を1件消費
void LoopCore1_Normal()
{
  if (n.take())
  {
    Serial.println("[Notify/counter] got event");
  }
}

void loop()
{
  delay(1);
}
