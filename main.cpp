#include <iostream>
#include <vector>

#include "include/Core/Vec.h"
#include "include/Image/ImageParser.h"
#include "include/Image/Matrix.h"

int main(int argc, char** argv)
{
    using namespace ImPro;

    Matrix<Vec3d> mat{};
    mat = ImageParser::FromFile<Vec3d>("../samples/StrangeSphere.ppm");

    ImageParser::ToFile<Vec3d>(mat, "../samples/ExportSpheres2.ppm");
}