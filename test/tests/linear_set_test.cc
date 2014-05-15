/**
 * @author: Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */

#include <gtest/gtest.h>
#include "eos/linear_set.h"

namespace eos
{
namespace tests
{

TEST(linear_set_should, succeed)
{
    eos::linear_set<int> sut;
    sut.insert(101);
    ASSERT_EQ(1, sut.size());
}

}  // namespace tests
}  // namespace eos
