#pragma once

#include <exchange/iid_generator.h>

#include <vector>

namespace exchange {

class IdGeneratorV : public IIdGenerator {
public:
  IdGeneratorV() = default;

  explicit IdGeneratorV(size_t preSize);

  ~IdGeneratorV() override = default;

  ActorId Next() override;

  void Unused(ActorId id) override;

private:
  ActorId id_ = defaultId;
  std::vector<ActorId> unused_{};
};

}// namespace exchange
