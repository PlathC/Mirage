//
// Created by Platholl on 04/06/2020.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <Mirage/Core/Math.hpp>

TEST_CASE( "Atan", "[atan]" )
{
    REQUIRE( mrg::Atan(0) <= std::numeric_limits<double>::epsilon());
    REQUIRE( mrg::Atan(1) == Approx(mrg::Pi / 4.));
}

TEST_CASE( "Exp", "[exo]" )
{
    REQUIRE( mrg::Exp(0.)  == Approx(1.) );
    REQUIRE( mrg::Exp(22.) > std::numeric_limits<double>::epsilon());
}

TEST_CASE( "Sqrt", "[sqrt]" )
{
    REQUIRE( mrg::Sqrt(0.)  <= std::numeric_limits<double>::epsilon() );
    REQUIRE( mrg::Sqrt(1.)  == Approx(1.) );
    REQUIRE( mrg::Sqrt(4.)  == Approx(2.) );
    REQUIRE( mrg::Sqrt(9.)  == Approx(3.) );
    REQUIRE( mrg::Sqrt(16.) == Approx(4.) );
}

TEST_CASE( "Pow", "[pow]" )
{
    REQUIRE( mrg::Pow(2., 2.)  == Approx(4.) );
    REQUIRE( mrg::Pow(2., 8.)  == Approx(256.) );
    REQUIRE( mrg::Pow(2., 16.) == Approx(65536.) );
    REQUIRE( mrg::Pow(4., 2.)  == Approx(16.) );
}

TEST_CASE( "Log", "[log]" )
{
    REQUIRE( mrg::Log(1.) == Approx(0.));
}

TEST_CASE( "Sin", "[sin]" )
{
    REQUIRE( mrg::Sin(0.)                <= std::numeric_limits<double>::epsilon());
    REQUIRE( mrg::Sin(mrg::Pi / 6.)      == Approx(1./2.));
    REQUIRE( mrg::Sin(mrg::Pi / 2.)      == Approx(1.));
    REQUIRE( mrg::Sin(mrg::Pi)           <= std::numeric_limits<double>::epsilon());
    REQUIRE( mrg::Sin(3. * mrg::Pi / 2.) == Approx(-1.));
    REQUIRE( mrg::Sin(mrg::Tau)          <= std::numeric_limits<double>::epsilon());
}

TEST_CASE( "Cos", "[cos]" )
{
    REQUIRE( mrg::Cos(0.)           == Approx( 1.));
    REQUIRE( mrg::Cos(mrg::Pi / 6.) == Approx(mrg::Sqrt(3.)/2.));
    REQUIRE( mrg::Cos(mrg::Pi / 4.) == Approx(1. / mrg::Sqrt(2.)));
    REQUIRE( mrg::Cos(mrg::Pi / 3.) == Approx(1./2.));
    REQUIRE( mrg::Cos(mrg::Pi / 2.) <= std::numeric_limits<double>::epsilon());
    REQUIRE( mrg::Cos(mrg::Pi)      <= std::numeric_limits<double>::epsilon());
}

TEST_CASE( "Ceil", "[ceil]" )
{
    REQUIRE(mrg::Ceil(2.3)       == Approx(3.));
    REQUIRE(mrg::Ceil(125.85465) == Approx(126.));
    REQUIRE(mrg::Ceil(-2.3)      == Approx(-2.));
}

TEST_CASE( "Floor", "[floor]" )
{
    REQUIRE(mrg::Floor(2.3)  == Approx(2.));
    REQUIRE(mrg::Floor(3.8)  == Approx(3.));
    REQUIRE(mrg::Floor(-3.8) == Approx(-4.));
}

TEST_CASE( "Trunc", "[trunc]" )
{
    REQUIRE(mrg::Trunc(+2.7) == Approx(2.));
    REQUIRE(mrg::Trunc(-2.9) == Approx(-2.));
}