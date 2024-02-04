#include <exchange/exchange.h>

namespace exchange {

Exchange::Exchange(ActorStoragePtr storage, const IdGeneratorPtr &generator)
    : storage_(std::move(storage)), generator_(generator) {}

ActorId Exchange::Add(const ActorPtr &actor) {
  const auto id = generator_->Next();
  actor->SetId(id);
  storage_->Add(id, actor);
  return id;
}

ActorPtr Exchange::Delete(ActorId id) {
  auto actor = storage_->Delete(id);
  if (actor) {
    actor->ResetId();
  }
  generator_->Unused(id);
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
