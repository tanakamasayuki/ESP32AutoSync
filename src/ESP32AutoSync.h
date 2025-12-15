#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

namespace ESP32AutoSync
{

// Common constant for “wait forever”
constexpr uint32_t WaitForever = portMAX_DELAY;

// Queue (stub implementation for packaging; API surface may evolve per SPEC)
template <class T>
class Queue
{
public:
  explicit Queue(uint32_t /*depth*/) {}

  bool trySend(const T & /*value*/) { return false; }
  bool send(const T & /*value*/, uint32_t /*timeoutMs*/ = WaitForever) { return false; }
  bool tryReceive(T & /*out*/) { return false; }
  bool receive(T & /*out*/, uint32_t /*timeoutMs*/ = WaitForever) { return false; }
};

// Notify (stub)
class Notify
{
public:
  enum class Mode
  {
    Counter,
    Bits
  };

  Notify() = default;
  explicit Notify(Mode /*mode*/) {}
  explicit Notify(TaskHandle_t /*handle*/) {}
  Notify(TaskHandle_t /*handle*/, Mode /*mode*/) {}

  bool bindTo(TaskHandle_t /*handle*/) { return false; }
  bool bindToSelf() { return false; }

  bool notify() { return false; }

  bool take(uint32_t /*timeoutMs*/ = WaitForever) { return false; }
  bool tryTake() { return false; }

  bool setBits(uint32_t /*mask*/) { return false; }
  bool waitBits(uint32_t /*mask*/, uint32_t /*timeoutMs*/ = WaitForever, bool /*clearOnExit*/ = true, bool /*waitAll*/ = false) { return false; }
  bool tryWaitBits(uint32_t mask, bool clearOnExit = true, bool waitAll = false) { return waitBits(mask, 0, clearOnExit, waitAll); }
};

// BinarySemaphore (stub)
class BinarySemaphore
{
public:
  BinarySemaphore() = default;

  bool give() { return false; }
  bool take(uint32_t /*timeoutMs*/ = WaitForever) { return false; }
  bool tryTake() { return false; }
};

// Mutex (stub)
class Mutex
{
public:
  Mutex() = default;

  bool lock(uint32_t /*timeoutMs*/ = WaitForever) { return false; }
  bool tryLock() { return false; }
  bool unlock() { return false; }

  class LockGuard
  {
  public:
    explicit LockGuard(Mutex & /*m*/, uint32_t /*timeoutMs*/ = WaitForever) : locked_(false) {}
    ~LockGuard() { /* unlock only if locked */ }

    bool locked() const { return locked_; }

  private:
    bool locked_;
  };
};

} // namespace ESP32AutoSync
