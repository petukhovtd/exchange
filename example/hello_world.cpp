#include <exchange/actor_helper.h>
#include <exchange/message_helper.h>
#include <exchange/id_generator_forward.h>
#include <exchange/actor_storage_line.h>
#include <exchange/exchange.h>

#include <string>
#include <iostream>

struct Message : exchange::MessageHelper<Message> {
  ~Message() override = default;
  std::string data{};
};

struct Actor : exchange::ActorHelper<Actor> {
  explicit Actor(const exchange::ExchangePtr &_exchange)
      : exchange(_exchange) {}

  ~Actor() override = default;

  void Receive(const exchange::MessagePtr &message) override {
    const auto m = std::dynamic_pointer_cast<Message>(message);
    if (m) {
      std::cout << "Actor with id: " << id << ", receive: " << m->data << std::endl;
    }
  }
  // SetId call in Exchange::Add
  void SetId(exchange::ActorId _id) override {
    id = _id;
  }
  // SetId call in Exchange::Delete
  void ResetId() override {
    id = exchange::defaultId;
  }

  exchange::ActorId GetId() override {
    return id;
  }

  void Send(exchange::ActorId _id, const std::string& data) const {
    auto ex = exchange.lock();
    if (ex) {
      auto message = Message::Create();
      message->data = data;
      std::cout << "Actor with id: " << id << ", send: " << data<< std::endl;
      ex->Send(_id, message);
    }
  }

  exchange::ActorId id = exchange::defaultId;
  // Use weak ptr, because exchange store shared_ptr<Actor>
  exchange::ExchangeWeak exchange;
};

int main() {
  auto idGenerator = std::make_shared<exchange::IdGeneratorForward>();
  auto storage = std::make_unique<exchange::ActorStorageLine>();
  auto exchange = std::make_shared<exchange::Exchange>(std::move(storage), idGenerator);

  auto sender = Actor::Create(exchange);
  auto receiver = Actor::Create(exchange);

  const auto senderId = exchange->Add(sender);
  const auto receiverId = exchange->Add(receiver);

  sender->Send( receiverId, "Hello World!" );
}
