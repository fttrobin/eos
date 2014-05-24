/**
 * @author Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */

#include <gtest/gtest.h>
#include "eos/unique_vector.h"

namespace eos
{
namespace test
{

TEST(unique_vector_should, succeed)
{
    eos::unique_vector<int> sut;
    ASSERT_TRUE(sut.push_back(101).second);
}

}  // namespace test
}  // namespace eos
