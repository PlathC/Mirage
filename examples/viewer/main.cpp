#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    Viewer viewer = Viewer(800,800, ImageParser::FromFile<Vec4ui8>("../samples/lena.png", 4));
    try{
        viewer.Show();
    }catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}