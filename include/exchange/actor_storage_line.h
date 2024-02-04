#pragma once

#include <exchange/iactor_storage.h>
#include <vector>

namespace exchange {

class ActorStorageLine : public IActorStorage {
public:
  ActorStorageLine() = default;

  explicit ActorStorageLine(size_t preSize);

  ~ActorStorageLine() override = default;

  void Add(ActorId id, const ActorPtr &actor) override;

  ActorPtr Delete(ActorId id) override;

  ActorPtr Find(ActorId id) override;

private:
  std::vector<ActorPtr> storage_{};
};

}// namespace exchange
