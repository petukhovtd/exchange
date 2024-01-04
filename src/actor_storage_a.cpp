#include <exchange/actor_storage_a.h>

namespace exchange {

ActorStorageA::ActorStorageA(size_t preSize) : ActorStorageA() {
  storage_.resize(preSize);
}

void ActorStorageA::Add(ActorId id, const ActorPtr &actor) {
  if (storage_.size() <= id) {
    storage_.resize(id + 1);
  }
  storage_[id] = actor;
}

ActorPtr ActorStorageA::Delete(ActorId id) {
  if (storage_.size() <= id) {
    return nullptr;
  }
  const auto result = storage_[id];
  storage_[id] = nullptr;
  return result;
}

ActorPtr ActorStorageA::Find(ActorId id) {
  return storage_[id];
}

}// namespace exchange
