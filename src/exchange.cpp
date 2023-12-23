#include <exchange/exchange.h>

namespace exchange {

Exchange::Exchange(ActorStoragePtr storage)
    : storage_(std::move(storage)) {}

ActorId Exchange::Add(const ActorPtr &actor) {
  const auto id = GetNextId();
  storage_->Add(id, actor);
  return id;
}

ActorId Exchange::GetNextId() {
  static ActorId id = startId;
  return ++id;
}

void Exchange::Delete(ActorId id) {
  storage_->Delete(id);
}

bool Exchange::Send(ActorId id, const MessagePtr &msg) const {
  const auto actor = storage_->Find(id);
  if (!actor) {
    return false;
  }

  actor->Receive(msg);
  return true;
}

}// namespace exchange
