#include <gtest/gtest.h>

#include <exchange/id_generator_forward.h>
#include <exchange/id_generator_reuse.h>

TEST(IdGeneratorTest, Forward) {
  exchange::IdGeneratorForward generator;

  EXPECT_NE(generator.Next(), exchange::defaultId);

  const auto id1 = generator.Next();
  EXPECT_NE(id1, exchange::defaultId);

  const auto id2 = generator.Next();
  EXPECT_NE(id1, exchange::defaultId);
  EXPECT_NE(id1, id2);

  generator.Unused(id2);
  const auto id3 = generator.Next();

  EXPECT_NE(id3, exchange::defaultId);
  EXPECT_NE(id3, id2);
}

TEST(IdGeneratorTest, Reuse) {
  exchange::IdGeneratorReuse generator;

  EXPECT_NE(generator.Next(), exchange::defaultId);

  const auto id1 = generator.Next();
  EXPECT_NE(id1, exchange::defaultId);

  const auto id2 = generator.Next();
  EXPECT_NE(id1, exchange::defaultId);
  EXPECT_NE(id1, id2);

  generator.Unused(id2);

  const auto id3 = generator.Next();
  EXPECT_NE(id3, exchange::defaultId);
  EXPECT_EQ(id3, id2);
}
