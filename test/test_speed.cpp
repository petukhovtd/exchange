#include "common/test_actor.h"
#include "common/test_message.h"
#include "common/test_types.h"
#include "common/timer.h"
#include "exchange/actor_storage_a.h"
#include <exchange/actor_storage_ht.h>
#include <exchange/actor_storage_v.h>
#include <exchange/exchange.h>
#include <iomanip>
#include <iostream>
#include <vector>

struct TestParams {
  size_t receivers;
  size_t messages;
  exchange::ExchangePtr exchange;
};

void PrintReport(std::ostream &os, const std::string &name, const TestParams &params, const Timer &timer) {
  os
      << std::setw(15) << name
      << std::setw(15) << "actors: " << std::setw(10) << params.receivers
      << std::setw(15) << "messages: " << std::setw(10) << params.messages
      << std::setw(15) << "time: " << std::setw(10) << timer.diff
      << std::setw(15) << "mpn: " << std::setw(10) << static_cast<double>(params.messages) / timer.diff
      << std::endl;
}

void NoExchangeTest(const TestParams &params) {
  TestData data = 1;
  std::vector<exchange::ActorPtr> receivers;
  receivers.reserve(params.receivers);

  for (int i = 0; i < params.receivers; ++i) {
    receivers.push_back(TestActor::Create(params.exchange));
  }

  Timer timer;
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

  for (int i = 0; i < params.receivers; ++i) {
    const auto receiver = TestActor::Create(params.exchange);
    params.exchange->Add(receiver);
  }

  Timer timer;
  timer.Start();
  for (size_t i = 0; i < params.messages; ++i) {
    const size_t actorId = i % params.receivers + 1;
    sender->Send(actorId, data);
    ++data;
  }
  timer.Stop();
  PrintReport(std::cout, name, params, timer);
}

int main() {
  std::vector<TestParams> params =
      {
          TestParams{1, 1, nullptr},
          TestParams{1, 100, nullptr},
          TestParams{1, 1'000, nullptr},
          TestParams{1, 1'000'000, nullptr},
          TestParams{10, 1, nullptr},
          TestParams{10, 100, nullptr},
          TestParams{10, 1'000, nullptr},
          TestParams{10, 1'000'000, nullptr},
          TestParams{100, 1, nullptr},
          TestParams{100, 100, nullptr},
          TestParams{100, 1'000, nullptr},
          TestParams{100, 1'000'000, nullptr},
          TestParams{1000, 1, nullptr},
          TestParams{1000, 100, nullptr},
          TestParams{1000, 1'000, nullptr},
          TestParams{1000, 1'000'000, nullptr},
          TestParams{100000, 1, nullptr},
          TestParams{100000, 100, nullptr},
          TestParams{100000, 1'000, nullptr},
          TestParams{100000, 1'000'000, nullptr},
      };

  for (auto param : params) {
    NoExchangeTest(param);
    {
      exchange::ActorStoragePtr asv = std::make_unique<exchange::ActorStorageA>(param.receivers);
      const auto ex = std::make_shared<exchange::Exchange>(std::move(asv));
      param.exchange = ex;
      ExchangeTest("ActorStorageA", param);
    }
    {
      exchange::ActorStoragePtr asv = std::make_unique<exchange::ActorStorageV>();
      const auto ex = std::make_shared<exchange::Exchange>(std::move(asv));
      param.exchange = ex;
      ExchangeTest("ActorStorageV", param);
    }
    {
      exchange::ActorStoragePtr asv = std::make_unique<exchange::ActorStorageHT>();
      const auto ex = std::make_shared<exchange::Exchange>(std::move(asv));
      param.exchange = ex;
      ExchangeTest("ActorStorageHT", param);
    }
  }
}
