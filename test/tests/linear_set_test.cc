/**
 * @author: Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */

#include <gtest/gtest.h>
#include "eos/linear_set.h"

namespace eos
{
namespace tests
{

TEST(linear_set_should, insert_unique_values_in_order)
{
    eos::linear_set<int> sut({10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    ASSERT_TRUE(std::is_sorted(sut.begin(), sut.end()));
}

}  // namespace tests
}  // namespace eos
