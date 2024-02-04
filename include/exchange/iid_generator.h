#pragma once

#include <exchange/id.h>

#include <memory>

namespace exchange {

class IIdGenerator {
public:
  virtual ~IIdGenerator() = default;

  virtual ActorId Next() = 0;

  virtual void Unused(ActorId) = 0;
};

using IdGeneratorPtr = std::shared_ptr<IIdGenerator>;

}// namespace exchange
