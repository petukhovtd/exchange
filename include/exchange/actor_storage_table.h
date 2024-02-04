#pragma once

#include <exchange/iactor_storage.h>
#include <unordered_map>

namespace exchange {

class ActorStorageTable : public IActorStorage {
public:
  ActorStorageTable() = default;

  ~ActorStorageTable() override = default;

  void Add(ActorId id, const ActorPtr &actor) override;

  ActorPtr Delete(ActorId id) override;

  ActorPtr Find(ActorId id) override;

private:
  std::unordered_map<ActorId, ActorPtr> storage_{};
};

}// namespace exchange
