#pragma once

#include <exchange/iid_generator.h>

namespace exchange {

class IdGeneratorForward : public IIdGenerator {
public:
  ~IdGeneratorForward() override = default;

  ActorId Next() override;

  void Unused(ActorId id) override;

private:
  ActorId id_ = defaultId;
};

}// namespace exchange
