#ifndef MAIEVERTIAS_FILEPOSIX_H
#define MAIEVERTIAS_FILEPOSIX_H

#include "Path.h"
#include "dirent.h"
#include "sys/stat.h"
#include "fcntl.h"

namespace maievertias{
    class File{
    public:
        static File current();

        class iterator{
        public:
            iterator(DIR *dir);
            ~iterator();

            iterator &operator++()noexcept;
            const iterator operator++(int)noexcept;

            File operator*()const noexcept;

            bool operator==(const iterator &)const noexcept;
            bool operator!=(const iterator &)const noexcept;
        protected:
        private:
            DIR *m_dir;
        };

        File(const Path &);
        File(Path &&);
        ~File();

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
        Path m_path;
    };
}

#endif //MAIEVERTIAS_FILEPOSIX_H
