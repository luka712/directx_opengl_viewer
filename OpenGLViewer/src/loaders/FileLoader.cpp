#include "loaders/FileLoader.hpp"

#include <fstream>
#include <sstream>

namespace Viewer
{
    std::string FileLoader::LoadFile(std::string path)
    {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}