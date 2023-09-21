#ifndef FILE_LOADER_HPP

#define FILE_LOADER_HPP

#include <string>

namespace Viewer
{
    class FileLoader final
    {
    public:
        static std::string LoadFile(std::string path);
    };
}

#endif