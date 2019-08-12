#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;
    Matrix<Vec4ui8> mat = ImageParser::FromFile<Vec4ui8>("../samples/tiled4x3.png", 4);
    Viewer viewer = Viewer(800,800, mat);
    try{
        viewer.Show();
    }catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}