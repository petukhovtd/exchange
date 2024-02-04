#include <gtest/gtest.h>

#include "common/test_actor.h"
#include "common/test_message.h"
#include "common/timer.h"

#include <exchange/actor_storage_line.h>
#include <exchange/actor_storage_table.h>
#include <exchange/exchange.h>
#include <exchange/id_generator_forward.h>

#include <iomanip>
#include <iostream>
#include <vector>

struct TestParams {
  size_t receivers;
  size_t messages;
  exchange::ExchangePtr exchange;
};

using TestData = int;
using TestActor = test::TestActor<TestData>;
using TestMessage = test::TestMessage<TestData>;

void PrintReport(std::ostream &os, const std::string &name, const TestParams &params, const test::Timer &timer) {
  os
      << std::setw(20) << name
      << std::setw(15) << "actors: " << std::setw(10) << params.receivers
      << std::setw(15) << "messages: " << std::setw(10) << params.messages
      << std::setw(15) << "time: " << std::setw(10) << timer.diff
      << std::setw(15) << "mpn: " << std::setw(20) << static_cast<double>(params.messages) / timer.diff
      << std::endl;
}

void NoExchangeTest(const TestParams &params) {
  TestData data = 1;
  std::vector<exchange::ActorPtr> receivers;
  receivers.reserve(params.receivers);

  for (int i = 0; i < params.receivers; ++i) {
    receivers.push_back(TestActor::Create(params.exchange));
  }

  test::Timer timer;
  timer.Start();
  for (size_t i = 0; i < params.messages; ++i) {
    const size_t actorIndex = i % params.receivers;
    const auto msg = TestMessage::Create(data);
    receivers[actorIndex]->Receive(msg);
    ++data;
  }
  timer.Stop();
  PrintReport(std::cout, __FUNCTION__, params, timer);
}

void ExchangeTest(const std::string &name, const TestParams &params) {
  TestData data = 1;

  auto sender = TestActor::Create(params.exchange);

  std::vector<exchange::ActorId> receivers;
  receivers.reserve(params.receivers);
  for (int i = 0; i < params.receivers; ++i) {
    const auto receiver = TestActor::Create(params.exchange);
    const auto id = params.exchange->Add(receiver);
    receivers.push_back(id);
  }

  test::Timer timer;
  timer.Start();
  for (size_t i = 0; i < params.messages; ++i) {
    const size_t actorId = receivers[i % receivers.size()];
    if (!sender->Send(actorId, data)) {
      throw std::runtime_error("send failed to: " + std::to_string(actorId));
    }
    ++data;
  }
  timer.Stop();
  PrintReport(std::cout, name, params, timer);
}

struct SpeedTest : public testing::TestWithParam<TestParams> {
};

INSTANTIATE_TEST_SUITE_P(SpeedSend, SpeedTest, testing::Values(
  TestParams{1, 1, nullptr},
  TestParams{1, 10, nullptr},
  TestParams{1, 100, nullptr},
  TestParams{1, 1'000, nullptr},
  TestParams{1, 10'000, nullptr},
  TestParams{10, 1, nullptr},
  TestParams{10, 10, nullptr},
  TestParams{10, 100, nullptr},
  TestParams{10, 1'000, nullptr},
  TestParams{10, 10'000, nullptr},
  TestParams{100, 1, nullptr},
  TestParams{100, 10, nullptr},
  TestParams{100, 100, nullptr},
  TestParams{100, 1'000, nullptr},
  TestParams{100, 10'000, nullptr},
  TestParams{1000, 1, nullptr},
  TestParams{1000, 10, nullptr},
  TestParams{1000, 100, nullptr},
  TestParams{1000, 1'000, nullptr},
  TestParams{1000, 10'000, nullptr},
  TestParams{10'000, 1, nullptr},
  TestParams{10'000, 10, nullptr},
  TestParams{10'000, 100, nullptr},
  TestParams{10'000, 1'000, nullptr},
  TestParams{10'000, 10'000, nullptr}
 )
);

TEST_P(SpeedTest, SpeedTest) {
  auto param = GetParam();
  NoExchangeTest(param);
  {
    auto generator = std::make_shared<exchange::IdGeneratorForward>();
    exchange::ActorStoragePtr as = std::make_unique<exchange::ActorStorageLine>(param.receivers);
    const auto ex = std::make_shared<exchange::Exchange>(std::move(as), generator);
    param.exchange = ex;
    ExchangeTest("ActorStorageLine", param);
  }
  {
    auto generator = std::make_shared<exchange::IdGeneratorForward>();
    exchange::ActorStoragePtr as = std::make_unique<exchange::ActorStorageTable>();
    const auto ex = std::make_shared<exchange::Exchange>(std::move(as), generator);
    param.exchange = ex;
    ExchangeTest("ActorStorageTable", param);
  }
}
