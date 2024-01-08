#include "test_actor.h"

TestActor::TestActor(const exchange::ExchangePtr &exchange) : exchange_(exchange) {}

void TestActor::Receive(const exchange::MessagePtr &message) {
  const auto ptr = std::dynamic_pointer_cast<TestMessage>(message);
  if (ptr) {
    data = ptr->data;
  }
}

void TestActor::Send(exchange::ActorId id) const {
  Send(id, data);
}

void TestActor::Send(exchange::ActorId id, const TestData &data) const {
  const auto message = TestMessage::Create(data);
  exchange_->Send(id, message);
}

void TestActor::SetId(exchange::ActorId id) {
}

void TestActor::ResetId() {
}

exchange::ActorId TestActor::GetId() {
  return 0;
}
