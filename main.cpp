#include <iostream>
#include <vector>

#include "include/Core/Vec.h"
#include "include/Image/ImageParser.h"
#include "include/Image/Matrix.h"

int main(int argc, char** argv)
{
    using namespace ImPro;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../samples/Kendrick.png");

    ImageParser::ToFile<Vec4d>(mat, "../samples/Kendrick2.png");
}