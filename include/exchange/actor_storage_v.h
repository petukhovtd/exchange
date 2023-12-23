#pragma once

#include <exchange/iactor_storage.h>
#include <vector>

namespace exchange {

class ActorStorageV : public IActorStorage {

  struct StorageItem {
    ActorId id;
    ActorPtr actor;

    StorageItem(ActorId id, const ActorPtr &actor);
  };

public:

  ActorStorageV() = default;

  ~ActorStorageV() override = default;

  void Add(ActorId id, const ActorPtr &actor) override;

  void Delete(ActorId id) override;

  ActorPtr Find(ActorId id) override;

private:
  std::vector<StorageItem> storage_{};
};

}// namespace exchange
