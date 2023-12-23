#pragma once

#include <exchange/iactor_storage.h>
#include <unordered_map>

namespace exchange {

class ActorStorageHT : public IActorStorage {
public:
  ActorStorageHT() = default;

  ~ActorStorageHT() override = default;

  void Add(ActorId id, const ActorPtr &actor) override;

  void Delete(ActorId id) override;

  ActorPtr Find(ActorId id) override;

private:
  std::unordered_map<ActorId, ActorPtr> storage_{};
};

}// namespace exchange
