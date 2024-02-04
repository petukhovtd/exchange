#pragma once

#include <exchange/iid_generator.h>

#include <vector>

namespace exchange {

class IdGeneratorReuse : public IIdGenerator {
public:
  IdGeneratorReuse() = default;

  explicit IdGeneratorReuse(size_t preSize);

  ~IdGeneratorReuse() override = default;

  ActorId Next() override;

  void Unused(ActorId id) override;

private:
  ActorId id_ = defaultId;
  std::vector<ActorId> unused_{};
};

}// namespace exchange
