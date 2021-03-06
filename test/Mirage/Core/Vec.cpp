//
// Created by Cyprien Plateau--Holleville on 05/06/2020.
//

#include "catch.hpp"

#include "Mirage/Core/Vec.hpp"

TEST_CASE( "Vec3", "[Vec]" )
{
    SECTION( "Default ctor and accessing function" )
    {
        mrg::Vec3c v;

        REQUIRE(v.Length() == 0);

        v.X() = 5;

        REQUIRE(v.X() == 5);
        REQUIRE(v.Y() == 0);
        REQUIRE(v.Z() == 0);

        REQUIRE(v[0] == 5);
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 0);

        REQUIRE(v.Get(0) == 5);
        REQUIRE(v.Get(1) == 0);
        REQUIRE(v.Get(2) == 0);
    }

    SECTION( "Copy ctor and assignment operator" )
    {
        mrg::Vec3c v1 = mrg::Vec3c(1, 2, 3);
        mrg::Vec3c v2 = v1;

        REQUIRE(v2.X() == 1);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 3);

        REQUIRE(v2[0] == 1);
        REQUIRE(v2[1] == 2);
        REQUIRE(v2[2] == 3);
    }

    SECTION( "Initializer list ctor" )
    {
        mrg::Vec3c v = {1, 2, 3};

        REQUIRE(v.X() == 1);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 3);

        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }

    SECTION( "Overloaded operators" )
    {
        mrg::Vec3c v{1, 1, 1};

        auto v2 = v + v;
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);

        v2 = v - v;
        REQUIRE(v2.X() == 0);
        REQUIRE(v2.Y() == 0);
        REQUIRE(v2.Z() == 0);

        v2 = v * mrg::Vec3c{2, 2, 2};
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);

        v2 = v * 2;
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);

        v2 = mrg::Vec3c{2, 2, 2} / 2;
        REQUIRE(v2.X() == 1);
        REQUIRE(v2.Y() == 1);
        REQUIRE(v2.Z() == 1);

        v *= 2;
        REQUIRE(v.X() == 2);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 2);

        v -= mrg::Vec3c{1, 1, 1} ;
        REQUIRE(v.X() == 1);
        REQUIRE(v.Y() == 1);
        REQUIRE(v.Z() == 1);

        v *= mrg::Vec3c{2, 2, 2} ;
        REQUIRE(v.X() == 2);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 2);

        v *= 3;
        REQUIRE(v.X() == 6);
        REQUIRE(v.Y() == 6);
        REQUIRE(v.Z() == 6);
    }
}

TEST_CASE( "Vec4", "[Vec]" )
{
    SECTION( "Default ctor and accessing function" )
    {
        mrg::Vec4c v;

        REQUIRE(v.Length() == 0);

        v.X() = 5;

        REQUIRE(v.X() == 5);
        REQUIRE(v.Y() == 0);
        REQUIRE(v.Z() == 0);
        REQUIRE(v.A() == 0);

        REQUIRE(v[0] == 5);
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 0);
        REQUIRE(v[3] == 0);
    }

    SECTION( "Copy ctor and assignment operator" )
    {
        mrg::Vec4c v1 = mrg::Vec4c(1, 2, 3, 4);
        mrg::Vec4c v2 = v1;

        REQUIRE(v2.X() == 1);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 3);
        REQUIRE(v2.A() == 4);

        REQUIRE(v2[0] == 1);
        REQUIRE(v2[1] == 2);
        REQUIRE(v2[2] == 3);
        REQUIRE(v2[3] == 4);
    }

    SECTION( "Initializer list ctor" )
    {
        mrg::Vec4c v = mrg::Vec4c(1, 2, 3, 4);

        REQUIRE(v.X() == 1);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 3);
        REQUIRE(v.A() == 4);

        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 4);
    }

    SECTION( "Overloaded operators" )
    {
        mrg::Vec4c v = mrg::Vec4c(1, 1, 1, 1);

        auto v2 = v + v;
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);
        REQUIRE(v2.A() == 2);

        v2 = v - v;
        REQUIRE(v2.X() == 0);
        REQUIRE(v2.Y() == 0);
        REQUIRE(v2.Z() == 0);
        REQUIRE(v2.A() == 0);

        v2 = v * mrg::Vec4c{2, 2, 2, 2};
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);
        REQUIRE(v2.A() == 2);

        v2 = v * 2;
        REQUIRE(v2.X() == 2);
        REQUIRE(v2.Y() == 2);
        REQUIRE(v2.Z() == 2);
        REQUIRE(v2.A() == 2);

        v2 = mrg::Vec4c{2, 2, 2, 2} / 2;
        REQUIRE(v2.X() == 1);
        REQUIRE(v2.Y() == 1);
        REQUIRE(v2.Z() == 1);
        REQUIRE(v2.A() == 1);

        v *= 2;
        REQUIRE(v.X() == 2);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 2);
        REQUIRE(v.A() == 2);

        v -= mrg::Vec4c{1, 1, 1, 1};
        REQUIRE(v.X() == 1);
        REQUIRE(v.Y() == 1);
        REQUIRE(v.Z() == 1);
        REQUIRE(v.A() == 1);

        v *= mrg::Vec4c{2, 2, 2, 2};
        REQUIRE(v.X() == 2);
        REQUIRE(v.Y() == 2);
        REQUIRE(v.Z() == 2);
        REQUIRE(v.A() == 2);

        v *= 3;
        REQUIRE(v.X() == 6);
        REQUIRE(v.Y() == 6);
        REQUIRE(v.Z() == 6);
        REQUIRE(v.A() == 6);
    }
}

TEST_CASE( "Vec5", "[Vec]" )
{
    SECTION( "Default ctor and accessing function" )
    {
        mrg::Vec<char, 5> v;

        REQUIRE(v.Length() == 0);

        v.Get(0) = 5;

        REQUIRE(v.Get(0) == 5);
        REQUIRE(v.Get(1) == 0);
        REQUIRE(v.Get(2) == 0);
        REQUIRE(v.Get(3) == 0);
        REQUIRE(v.Get(4) == 0);

        REQUIRE(v[0] == 5);
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 0);
        REQUIRE(v[3] == 0);
        REQUIRE(v[4] == 0);
    }

    SECTION( "Copy ctor and assignment operator" )
    {
        mrg::Vec<char, 5> v1 = mrg::Vec<char, 5>({1, 2, 3, 4, 5});
        mrg::Vec<char, 5> v2 = v1;

        REQUIRE(v2.Get(0) == 1);
        REQUIRE(v2.Get(1) == 2);
        REQUIRE(v2.Get(2) == 3);
        REQUIRE(v2.Get(3) == 4);
        REQUIRE(v2.Get(4) == 5);

        REQUIRE(v2[0] == 1);
        REQUIRE(v2[1] == 2);
        REQUIRE(v2[2] == 3);
        REQUIRE(v2[3] == 4);
        REQUIRE(v2[4] == 5);
    }

    SECTION( "Initializer list ctor" )
    {
        mrg::Vec<char, 5> v = mrg::Vec<char, 5>({1, 2, 3, 4, 5});

        REQUIRE(v.Get(0) == 1);
        REQUIRE(v.Get(1) == 2);
        REQUIRE(v.Get(2) == 3);
        REQUIRE(v.Get(3) == 4);
        REQUIRE(v.Get(4) == 5);

        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 4);
        REQUIRE(v[4] == 5);
    }

    SECTION( "Overloaded operators" )
    {
        mrg::Vec<char, 5> v = mrg::Vec<char, 5>({1, 1, 1, 1, 1});

        auto v2 = v + v;
        REQUIRE(v2.Get(0) == 2);
        REQUIRE(v2.Get(1) == 2);
        REQUIRE(v2.Get(2) == 2);
        REQUIRE(v2.Get(3) == 2);
        REQUIRE(v2.Get(4) == 2);

        v2 = v - v;
        REQUIRE(v2.Get(0) == 0);
        REQUIRE(v2.Get(1) == 0);
        REQUIRE(v2.Get(2) == 0);
        REQUIRE(v2.Get(3) == 0);
        REQUIRE(v2.Get(4) == 0);

        v2 = v * mrg::Vec<char, 5>{2, 2, 2, 2, 2};
        REQUIRE(v2.Get(0) == 2);
        REQUIRE(v2.Get(1) == 2);
        REQUIRE(v2.Get(2) == 2);
        REQUIRE(v2.Get(3) == 2);
        REQUIRE(v2.Get(4) == 2);

        v2 = v * 2;
        REQUIRE(v2.Get(0) == 2);
        REQUIRE(v2.Get(1) == 2);
        REQUIRE(v2.Get(2) == 2);
        REQUIRE(v2.Get(3) == 2);
        REQUIRE(v2.Get(4) == 2);

        v2 = mrg::Vec<char, 5>{2, 2, 2, 2, 2} / 2;
        REQUIRE(v2.Get(0) == 1);
        REQUIRE(v2.Get(1) == 1);
        REQUIRE(v2.Get(2) == 1);
        REQUIRE(v2.Get(3) == 1);
        REQUIRE(v2.Get(4) == 1);

        v *= 2;
        REQUIRE(v.Get(0) == 2);
        REQUIRE(v.Get(1) == 2);
        REQUIRE(v.Get(2) == 2);
        REQUIRE(v.Get(3) == 2);
        REQUIRE(v.Get(4) == 2);

        v -= mrg::Vec<char, 5>{1, 1, 1, 1, 1};
        REQUIRE(v.Get(0) == 1);
        REQUIRE(v.Get(1) == 1);
        REQUIRE(v.Get(2) == 1);
        REQUIRE(v.Get(3) == 1);
        REQUIRE(v.Get(4) == 1);

        v *= mrg::Vec<char, 5>{2, 2, 2, 2, 2};
        REQUIRE(v.Get(0) == 2);
        REQUIRE(v.Get(1) == 2);
        REQUIRE(v.Get(2) == 2);
        REQUIRE(v.Get(3) == 2);
        REQUIRE(v.Get(4) == 2);

        v *= 3;
        REQUIRE(v.Get(0) == 6);
        REQUIRE(v.Get(1) == 6);
        REQUIRE(v.Get(2) == 6);
        REQUIRE(v.Get(3) == 6);
        REQUIRE(v.Get(4) == 6);
    }
}

