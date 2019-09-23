#ifndef MAIEVERTIAS_FILE_H
#define MAIEVERTIAS_FILE_H

#include <exception>
#include "Path.h"

namespace maievertias{
    class File{
    public:
        static File current();
    
        File(const Path &);
        File(Path &&);
        ~File();
        
        enum class Type{
            other,
            regular,
            directory,
            fifo,
            block,
            character,
            socket,
            symlink,
        }
        
        const Path &path()const noexcept;
        Path &path()noexcept;

        bool isRegularFile()const noexcept;
        bool isDirectory()const noexcept;
        bool isFIFO()const noexcept;
        bool isBlockFile()const noexcept;
        bool isCharacterFile()const noexcept;
        bool isSocket()const noexcept;
        //bool isEmpty()const noexcept;
        bool isSymlink()const noexcept;
        bool isOther()const noexcept;

        bool exist()const noexcept;
        operator bool()const noexcept;

        std::uint32_t size()const noexcept;
        
        File copy(const Path &);
        File &move(const Path &);
        void remove();
        void create(Type type);
    protected:
    private:
        Type m_type;
        Path m_path;
    };
}

#endif //MAIEVERTIAS_FILE_H
