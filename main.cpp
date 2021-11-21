#include "demo.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <mesh_path>" << std::endl;
        return 1;
    }
    std::cout << "using mesh : " << argv[1] << std::endl;
    Demo demo(argv[1]);
    demo.run();
    return 0;
}
