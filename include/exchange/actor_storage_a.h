#pragma once

#include <exchange/iactor_storage.h>
#include <vector>

namespace exchange {

class ActorStorageA : public IActorStorage {
public:

  ActorStorageA() = default;

  explicit ActorStorageA( size_t preSize );

  ~ActorStorageA() override = default;

  void Add(ActorId id, const ActorPtr &actor) override;

  ActorPtr Delete(ActorId id) override;

  ActorPtr Find(ActorId id) override;

private:
  std::vector<ActorPtr> storage_{};
};

}// namespace exchange
