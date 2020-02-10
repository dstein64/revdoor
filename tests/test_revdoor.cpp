#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <revdoor.hpp>

BOOST_AUTO_TEST_CASE( test1 ) {
    // reports 'error in "test1": test 2 == 1 failed'
    BOOST_CHECK( 2 == 1 );
}

BOOST_AUTO_TEST_CASE( test2 )
{
    int i = 0;

    // reports 'error in "test2": check i == 2 failed [0 != 2]'
    BOOST_CHECK_EQUAL( i, 2 );

    BOOST_CHECK_EQUAL( i, 0 );
}

