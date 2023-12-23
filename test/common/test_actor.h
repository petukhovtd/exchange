#pragma once

#include "test_types.h"
#include "test_message.h"
#include <exchange/actor_helper.h>
#include <exchange/exchange.h>


class TestActor: public exchange::ActorHelper< TestActor >
{
public:
  explicit TestActor(const exchange::ExchangePtr &exchange);

  ~TestActor() override = default;

  void Receive(const exchange::MessagePtr &message) override;

  void Send( exchange::ActorId id ) const;

  void Send( exchange::ActorId id, const TestData& data ) const;

  TestData data = {};

private:
  exchange::ExchangePtr exchange_;
};

