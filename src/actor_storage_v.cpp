#include <algorithm>
#include <exchange/actor_storage_v.h>

namespace exchange {

ActorStorageV::StorageItem::StorageItem(ActorId i, const ActorPtr &a)
    : id(i), actor(a) {
}

void ActorStorageV::Add(exchange::ActorId id, const ActorPtr &actor) {
  storage_.emplace_back(id, actor);
}

void ActorStorageV::Delete(ActorId id) {
  const auto it = std::remove_if(storage_.begin(), storage_.end(), [id](const StorageItem &si) {
    return si.id == id;
  });
  storage_.erase(it);
}

ActorPtr ActorStorageV::Find(ActorId id) {
  const auto it = std::find_if(storage_.cbegin(), storage_.cend(), [id](const StorageItem &si) {
    return si.id == id;
  });
  if (storage_.cend() == it) {
    return nullptr;
  }
  return it->actor;
}

}// namespace exchange
