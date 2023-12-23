#pragma once

#include "test_types.h"

#include <exchange/message_helper.h>

class TestMessage : public exchange::MessageHelper<TestMessage> {
public:
  TestMessage() = default;

  explicit TestMessage(const TestData &data);

  ~TestMessage() override = default;

  TestData data{};

private:
};
