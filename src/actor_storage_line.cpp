#include <exchange/actor_storage_line.h>

namespace exchange {

ActorStorageLine::ActorStorageLine(size_t preSize) : ActorStorageLine() {
  storage_.resize(preSize);
}

void ActorStorageLine::Add(ActorId id, const ActorPtr &actor) {
  if (storage_.size() <= id) {
    storage_.resize(id + 1);
  }
  storage_[id] = actor;
}

ActorPtr ActorStorageLine::Delete(ActorId id) {
  if (storage_.size() <= id) {
    return nullptr;
  }
  const auto result = storage_[id];
  storage_[id] = nullptr;
  return result;
}

ActorPtr ActorStorageLine::Find(ActorId id) {
  if (id < storage_.size()) {
    return storage_[id];
  }
  return nullptr;
}

}// namespace exchange
