#pragma once

#include <exchange/iactor.h>
#include <exchange/id.h>
#include <memory>

namespace exchange {

class IActorStorage {
public:
  IActorStorage() = default;

  virtual ~IActorStorage() = default;

  IActorStorage(const IActorStorage &) = delete;

  IActorStorage(IActorStorage &&) = delete;

  IActorStorage &operator=(const IActorStorage &) = delete;

  IActorStorage &operator=(IActorStorage &&) = delete;

  virtual void Add(ActorId id, const ActorPtr &actor) = 0;

  virtual ActorPtr Delete(ActorId id) = 0;

  virtual ActorPtr Find(ActorId id) = 0;
};

using ActorStoragePtr = std::unique_ptr<IActorStorage>;

}// namespace exchange
