#include <exchange/actor_storage_table.h>

namespace exchange {

void ActorStorageTable::Add(ActorId id, const ActorPtr &actor) {
  storage_[id] = actor;
}

ActorPtr ActorStorageTable::Delete(ActorId id) {
  auto it = storage_.find(id);
  if (storage_.end() == it) {
    return nullptr;
  }
  const auto result = it->second;
  storage_.erase(it);
  return result;
}

ActorPtr ActorStorageTable::Find(ActorId id) {
  const auto it = storage_.find(id);
  if (storage_.end() == it) {
    return nullptr;
  }
  return it->second;
}

}// namespace exchange
