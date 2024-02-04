#pragma once

#include <exchange/iactor.h>
#include <exchange/iactor_storage.h>
#include <exchange/id.h>
#include <exchange/iexchange.h>
#include <exchange/iid_generator.h>
#include <exchange/imessage.h>

namespace exchange {

class Exchange : public IExchange {
public:
  explicit Exchange(ActorStoragePtr storage, const IdGeneratorPtr& generator);

  Exchange(const Exchange &) = delete;

  Exchange(Exchange &&) = delete;

  Exchange &operator=(const Exchange &) = delete;

  Exchange &operator=(Exchange &&) = delete;

  ~Exchange() override = default;

  ActorId Add(const ActorPtr &actor) override;

  ActorPtr Delete(ActorId id) override;

  bool Send(ActorId id, const MessagePtr &msg) const override;

private:
  ActorStoragePtr storage_;
  IdGeneratorPtr generator_;
};

}// namespace exchange
