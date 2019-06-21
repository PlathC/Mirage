#include <iostream>
#include <vector>

#include "include/Core/Vec.h"
#include "include/Image/ImageParser.h"
#include "include/Image/Matrix.h"

int main(int argc, char** argv)
{
    using namespace ImPro;

    int c = 4;
    Matrix<Vec4d> mat{5, 5};
    mat = ImageParser::FromPPM<Vec4d>("../samples/StrangeSphere.ppm");

    std::cout << "Width " << mat.Width() << "| Height " << mat.Height() << std::endl;
    for(unsigned i = 0; i < mat.Width(); i++)
    {
        for(unsigned j = 0; j < mat.Height(); j++)
        {
            Vec4d& value = mat.Get(i, j);
            //value = static_cast<double>(i * 5 + j);
            if(value[0] != 0)
                std::cout << value << "|";
        }
        std::cout << std::endl;
    }
}