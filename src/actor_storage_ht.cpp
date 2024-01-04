#include <exchange/actor_storage_ht.h>

namespace exchange {

void ActorStorageHT::Add(ActorId id, const ActorPtr &actor) {
  storage_[id] = actor;
}

ActorPtr ActorStorageHT::Delete(ActorId id) {
  auto it = storage_.find(id);

  const auto result = it->second;
  storage_.erase(it);
  return result;
}

ActorPtr ActorStorageHT::Find(ActorId id) {
  const auto it = storage_.find(id);
  if (storage_.end() == it) {
    return nullptr;
  }
  return it->second;
}

}// namespace exchange
