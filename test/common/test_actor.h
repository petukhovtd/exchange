#pragma once

#include "test_message.h"
#include <exchange/actor_helper.h>
#include <exchange/exchange.h>

namespace test {

template<typename T>
class TestActor : public exchange::ActorHelper<TestActor<T>> {
public:
  explicit TestActor(const exchange::ExchangePtr &exchange)
      : exchange_(exchange), id_(exchange::defaultId) {
  }

  void Receive(const exchange::MessagePtr &message) override {
    const auto ptr = std::dynamic_pointer_cast<TestMessage<T>>(message);
    if (ptr) {
      data = ptr->data;
    }
  }

  bool Send(exchange::ActorId id) const {
    return Send(id, data);
  }

  bool Send(exchange::ActorId id, const T &_data) const {
    const auto message = TestMessage<T>::Create(_data);
    auto exchange = exchange_.lock();
    if (exchange) {
      return exchange->Send(id, message);
    }
    return false;
  }

  void SetId(exchange::ActorId id) override {
    id_ = id;
  }

  void ResetId() override {
    id_ = exchange::defaultId;
  }

  exchange::ActorId GetId() override {
    return id_;
  }

  T data = {};

private:
  exchange::ExchangeWeak exchange_;
  exchange::ActorId id_;
};

}// namespace test
