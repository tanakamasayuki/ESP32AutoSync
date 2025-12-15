#include <ESP32TaskKit.h>
#include <ESP32AutoSync.h>

using namespace ESP32AutoSync;
using namespace TaskKit;

constexpr int kButtonPin = 0; // en/ja: adjust to your board

// en: Button ISR gives semaphore; TaskKit task takes it
// ja: ボタン ISR が give し、TaskKit タスクが take
BinarySemaphore buttonSem;
Task handlerTask;

void IRAM_ATTR onButton()
{
  buttonSem.give(); // en/ja: ISR-safe give
}

void setup()
{
  Serial.begin(115200);
  pinMode(kButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(kButtonPin), onButton, FALLING);

  handlerTask.startLoop(
      [] {
        if (buttonSem.take(WaitForever))
        {
          Serial.println("[BinarySemaphore] button pressed");
        }
        return true;
      },
      TaskConfig{.name = "button", .priority = 2});
}

void loop()
{
  delay(1);
}
