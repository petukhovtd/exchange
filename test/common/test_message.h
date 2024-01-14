#pragma once

#include <exchange/message_helper.h>

namespace test {

template<typename T>
struct TestMessage : exchange::MessageHelper<TestMessage<T>> {
  TestMessage() = default;

  explicit TestMessage(const T &_data)
      : data(_data) {}

  ~TestMessage() override = default;

  T data{};
};

}// namespace test
