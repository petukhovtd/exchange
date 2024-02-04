#include <gtest/gtest.h>

#include <exchange/actor_storage_line.h>
#include <exchange/actor_storage_table.h>
#include <exchange/iactor_storage.h>

class SimpleActor : public exchange::IActor {
public:
  explicit SimpleActor(const std::string &_tag)
      : tag(_tag) {}

  ~SimpleActor() override = default;

  void Receive(const exchange::MessagePtr &) override {
  }

  void SetId(exchange::ActorId id) override {
  }

  void ResetId() override {
  }

  exchange::ActorId GetId() override {
    return 0;
  }

  std::string tag{};
};

std::shared_ptr<SimpleActor> MakeActor(const std::string &tag) {
  return std::make_shared<SimpleActor>(tag);
}

template<typename T>
struct ActorStorageTest : public testing::Test {
protected:
  void SetUp() override {
    storage = std::make_unique<T>();
  }
  void TearDown() override {
    storage.reset();
  }

public:
  exchange::ActorStoragePtr storage = nullptr;
};

using ActorStorageTypes = ::testing::Types<exchange::ActorStorageLine, exchange::ActorStorageTable>;
TYPED_TEST_SUITE(ActorStorageTest, ActorStorageTypes);

TYPED_TEST(ActorStorageTest, Add) {
  exchange::ActorStoragePtr &actorStorage = this->storage;

  auto actor1 = MakeActor("first");
  auto actor2 = MakeActor("second");
  auto actor3 = MakeActor("third");
  auto actor4 = MakeActor("new_first");
  const exchange::ActorId id1 = 2;
  const exchange::ActorId id2 = 6;
  const exchange::ActorId id3 = 9;

  std::vector<std::pair<exchange::ActorId, std::shared_ptr<SimpleActor>>> testPlan =
      {
          {id1, actor1},// add
          {id2, actor2},// add
          {id3, actor3},// add
          {id2, actor4},// replace
      };

  for (const auto &item : testPlan) {
    const auto &id = item.first;
    const auto &actor = item.second;

    actorStorage->Add(id, actor);
    auto findActor = actorStorage->Find(id);

    ASSERT_TRUE(findActor);
    const auto findSimple = std::dynamic_pointer_cast<SimpleActor>(findActor);
    EXPECT_STREQ(findSimple->tag.c_str(), actor->tag.c_str());
  }
}

TYPED_TEST(ActorStorageTest, Find) {
  exchange::ActorStoragePtr &actorStorage = this->storage;

  auto actor1 = MakeActor("first");
  auto actor2 = MakeActor("second");
  auto actor3 = MakeActor("third");
  const exchange::ActorId id1 = 18;
  const exchange::ActorId id2 = 4;
  const exchange::ActorId id3 = 12;

  std::vector<std::pair<exchange::ActorId, std::shared_ptr<SimpleActor>>> testPlan =
      {
          {id1, actor1},
          {id2, actor2},
          {id3, actor3},
      };

  for (const auto &item : testPlan) {
    auto findActor = actorStorage->Find(item.first);
    EXPECT_FALSE(findActor);

    actorStorage->Add(item.first, item.second);
  }

  for (const auto &item : testPlan) {
    auto findActor = actorStorage->Find(item.first);
    ASSERT_TRUE(findActor);

    const auto findSimple = std::dynamic_pointer_cast<SimpleActor>(findActor);
    EXPECT_STREQ(findSimple->tag.c_str(), item.second->tag.c_str());
  }
}

TYPED_TEST(ActorStorageTest, Delete) {
  exchange::ActorStoragePtr &actorStorage = this->storage;

  auto actor1 = MakeActor("first");
  auto actor2 = MakeActor("second");
  auto actor3 = MakeActor("third");
  const exchange::ActorId id1 = 6;
  const exchange::ActorId id2 = 14;
  const exchange::ActorId id3 = 27;

  std::vector<std::pair<exchange::ActorId, std::shared_ptr<SimpleActor>>> testPlan =
      {
          {id1, actor1},
          {id2, actor2},
          {id3, actor3},
      };

  for (const auto &item : testPlan) {
    actorStorage->Add(item.first, item.second);
  }

  const auto deleteActor = actorStorage->Delete(id2);
  ASSERT_TRUE(deleteActor);
  const auto deleteSimple = std::dynamic_pointer_cast<SimpleActor>(deleteActor);
  EXPECT_STREQ(deleteSimple->tag.c_str(), actor2->tag.c_str());

  auto findActor = actorStorage->Find(id2);
  ASSERT_FALSE(findActor);

  EXPECT_TRUE(actorStorage->Find(id1));
  EXPECT_TRUE(actorStorage->Find(id3));
}
