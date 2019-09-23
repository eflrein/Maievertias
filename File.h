#ifndef MAIEVERTIAS_FILE_H
#define MAIEVERTIAS_FILE_H

#include "Path.h"

namespace maievertias{
    class File{
    public:
        class FileIterator;

        File(const Path &);
        File(Path &&);
        ~File();

        bool isRegularFile()const noexcept;
        bool isDirectory()const noexcept;
        bool isFIFO()const noexcept;
        bool isBlockFile()const noexcept;
        bool isCharacterFile()const noexcept;
        bool isSocket()const noexcept;
        bool isEmpty()const noexcept;
        bool isSymlink()const noexcept;
        bool isOther()const noexcept;

        bool exist()const noexcept;

        std::uint32_t size()const noexcept;


    protected:
    private:
    };
}

#endif //MAIEVERTIAS_FILE_H
