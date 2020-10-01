#include <cstdint>
#include <iostream>
#include "../libTLV/TVLEncoder.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include <vector>

TEST(testTVL, decodeShort)
{
	std::vector<uint8_t> d(1);
	d[0] = 0b00000000;
	ASSERT_EQ(0, TVLEncoder::decode(d));
	d[0] = 0b00000010;
	ASSERT_EQ(2, TVLEncoder::decode(d));
	d[0] = 0b01111111;
	ASSERT_EQ(127, TVLEncoder::decode(d));
	d[0] = 0b01000000;
	ASSERT_EQ(64, TVLEncoder::decode(d));
	d[0] = 0b11111111;
	ASSERT_THROW(TVLEncoder::decode(d), std::out_of_range);
}

TEST(testTVL, decodeLong)
{
	std::vector<uint8_t> d(4);
	d[0] = 0b10000001;
	d[1] = 0b00000001;
	ASSERT_EQ(1, TVLEncoder::decode(d));
	d[0] = 0b10000001;
	d[1] = 0b00000000;
	ASSERT_EQ(0, TVLEncoder::decode(d));
	d[0] = 0b10000001;
	d[1] = 0b11111111;
	ASSERT_EQ(255, TVLEncoder::decode(d));
	d[0] = 0b10000011;
	d[1] = 0b00000001;
	d[2] = 0b11111011;
	d[3] = 0b10000001;
	ASSERT_EQ(129921, TVLEncoder::decode(d));
	d[0] = 0b10000010;
	d[1] = 0b00001111;
	d[2] = 0b11011111;
	ASSERT_EQ(4063, TVLEncoder::decode(d));
	d.clear();
}

TEST(testTVL, encodeLong)
{
	ASSERT_EQ(1, TVLEncoder::decode(TVLEncoder::encode(1, TVLEncoder::longForm)));
	ASSERT_EQ(0, TVLEncoder::decode(TVLEncoder::encode(0, TVLEncoder::longForm)));
	ASSERT_EQ(225, TVLEncoder::decode(TVLEncoder::encode(225, TVLEncoder::longForm)));
	ASSERT_EQ(129921, TVLEncoder::decode(TVLEncoder::encode(129921, TVLEncoder::longForm)));
	ASSERT_EQ(4063, TVLEncoder::decode(TVLEncoder::encode(4063, TVLEncoder::longForm)));
}

TEST(testTVL, encodeShort)
{
	ASSERT_EQ(2, TVLEncoder::decode(TVLEncoder::encode(2, TVLEncoder::shortForm)));
	ASSERT_EQ(0, TVLEncoder::decode(TVLEncoder::encode(0, TVLEncoder::shortForm)));
	ASSERT_EQ(127, TVLEncoder::decode(TVLEncoder::encode(127, TVLEncoder::shortForm)));
	ASSERT_EQ(64, TVLEncoder::decode(TVLEncoder::encode(64, TVLEncoder::shortForm)));
	ASSERT_THROW(TVLEncoder::encode(128, TVLEncoder::shortForm), std::out_of_range);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}