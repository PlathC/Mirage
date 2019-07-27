#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    Viewer viewer = Viewer(800, 600);
    try{
        viewer.Show();
    }catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}