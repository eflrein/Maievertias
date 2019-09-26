#ifndef MAIEVERTIAS_FILEPOSIX_H
#define MAIEVERTIAS_FILEPOSIX_H

#include <exception>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Path.h"

namespace maievertias{
    class File{
    public:

        class FileError : public std::exception{
        public:
            FileError(int err);
            ~FileError();
            virtual const char *what() const noexcept ;
        protected:
        private:
            int m_err;
        };

        File(Path path);
        ~File();

        //read-only
        const Path &path()const noexcept;

        bool isRegularFile()const;
        bool isDirectory()const;
        bool isFIFO()const;
        bool isBlockFile()const;
        bool isCharacterFile()const;
        //bool isEmpty();

        bool exist()const noexcept;
        operator bool()const noexcept;

        std::uint32_t size()const;

        File copy(const Path &);///todo
        File &move(const Path &path);
        File &rename(const Path &name);
        File &remove();

    protected:
    private:
        mutable bool m_stated;
        mutable struct stat m_stat;
        Path m_path;
    };
}

#endif //MAIEVERTIAS_FILEPOSIX_H
