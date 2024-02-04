#include <gtest/gtest.h>

#include "common/test_actor.h"
#include "common/test_message.h"

#include <exchange/actor_storage_line.h>
#include <exchange/actor_storage_table.h>
#include <exchange/exchange.h>
#include <exchange/id_generator_forward.h>
#include <exchange/id_generator_reuse.h>

#include <random>

struct LineForward {
  using Generator = exchange::IdGeneratorForward;
  using ActorStorage = exchange::ActorStorageLine;
};

struct LineReuse {
  using Generator = exchange::IdGeneratorReuse;
  using ActorStorage = exchange::ActorStorageLine;
};

struct TreeForward {
  using Generator = exchange::IdGeneratorForward;
  using ActorStorage = exchange::ActorStorageTable;
};

struct TreeReuse {
  using Generator = exchange::IdGeneratorReuse;
  using ActorStorage = exchange::ActorStorageTable;
};

using DataType = int;

template<typename T>
struct ExchangeTest : public testing::Test {
protected:
  void SetUp() override {
    auto generator = std::make_shared<typename T::Generator>();
    auto storage = std::make_unique<typename T::ActorStorage>();
    ex = std::make_shared<exchange::Exchange>(std::move(storage), generator);
  }
  void TearDown() override {
    ex.reset();
  }

public:
  exchange::ExchangePtr ex = nullptr;
};

using TypesCombine = ::testing::Types<LineForward, LineReuse, TreeForward, TreeReuse>;
TYPED_TEST_SUITE(ExchangeTest, TypesCombine);

TYPED_TEST(ExchangeTest, AddDelete) {
  auto &exchange = this->ex;

  auto actor = test::TestActor<DataType>::Create(exchange);
  EXPECT_EQ(actor->GetId(), exchange::defaultId);

  const auto id = exchange->Add(actor);
  EXPECT_NE(id, exchange::defaultId);

  EXPECT_EQ(actor->GetId(), id);

  const auto deletedActor = exchange->Delete(id);
  EXPECT_EQ(&*actor, &*deletedActor);
  EXPECT_NE(actor->GetId(), id);
  EXPECT_EQ(actor->GetId(), exchange::defaultId);
}

TYPED_TEST(ExchangeTest, Send) {
  auto &exchange = this->ex;

  auto actor = test::TestActor<DataType>::Create(exchange);
  const auto actorId = exchange->Add(actor);

  DataType data = 123;
  const auto msg = test::TestMessage<DataType>::Create(data);
  EXPECT_TRUE(exchange->Send(actorId, msg));
  EXPECT_EQ(actor->data, data);
}

TYPED_TEST(ExchangeTest, SendMany) {
  auto &exchange = this->ex;

  const size_t size = 100;
  const size_t minActors = 100;
  const size_t maxActors = minActors + size;
  const size_t minRemove = minActors / 2;
  const size_t maxRemove = minRemove + size;
  std::map<exchange::ActorId, test::TestActor<DataType>::Ptr> actors;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> createDistr(minActors, maxActors);
  std::uniform_int_distribution<size_t> removeDistr(minRemove, maxRemove);
  const auto createActors = createDistr(gen);
  const auto removeActors = removeDistr(gen);
  for (size_t i = 0; i < createActors; ++i) {
    auto actor = test::TestActor<DataType>::Create(exchange);
    const auto actorId = exchange->Add(actor);
    EXPECT_NE(exchange::defaultId, actorId);
    actors[actorId] = actor;
  }

  std::uniform_int_distribution<size_t> deleteIdDistr(actors.begin()->first, std::prev(actors.end())->first);
  for (size_t i = 0; i < removeActors; ++i) {
    const auto removeId = deleteIdDistr(gen);
    if (actors.count(removeId)) {
      EXPECT_NE(exchange->Delete(removeId), nullptr) << removeId;
      actors.erase(removeId);
    }
  }

  DataType data = 0;
  for (const auto &pair : actors) {
    const auto &id = pair.first;
    const auto &actor = pair.second;
    ++data;
    const auto msg = test::TestMessage<DataType>::Create(data);
    EXPECT_TRUE(exchange->Send(id, msg));
    EXPECT_EQ(actor->data, data);
  }
}
