#include <exchange/exchange.h>

namespace exchange {

Exchange::Exchange(ActorStoragePtr storage)
    : storage_(std::move(storage)) {}

ActorId Exchange::Add(const ActorPtr &actor) {
  const auto id = GetNextId();
  actor->SetId(id);
  storage_->Add(id, actor);
  return id;
}

ActorId Exchange::GetNextId() {
  static ActorId id = defaultId;
  return ++id;
}

ActorPtr Exchange::Delete(ActorId id) {
  auto actor = storage_->Delete(id);
  if (actor) {
    actor->ResetId();
  }
  return actor;
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
