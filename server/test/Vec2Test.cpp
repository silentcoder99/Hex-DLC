#define BOOST_TEST_MODULE Vec2
#include <boost/test/included/unit_test.hpp>
#include "util/Vec2.hpp"

BOOST_AUTO_TEST_CASE( initVectorTo0 ){
	Vec2 vector;
	BOOST_TEST( vector.x == 0 );
	BOOST_TEST( vector.y == 0 );
}
