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

void ActorStorageA::Delete(ActorId id) {
  if (storage_.size() <= id) {
    return;
  }
  storage_[id] = nullptr;
}

ActorPtr ActorStorageA::Find(ActorId id) {
  return storage_[id];
}


}// namespace exchange
