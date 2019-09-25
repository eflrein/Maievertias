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

        bool isRegularFile();
        bool isDirectory();
        bool isFIFO();
        bool isBlockFile();
        bool isCharacterFile();
        //bool isEmpty();

        bool exist()const noexcept;
        operator bool()const noexcept;

        std::uint32_t size();

        File copy(const Path &);
        File &move(const Path &);
        void remove();


    protected:
    private:
        bool m_stated;
        struct stat m_stat;
        Path m_path;
    };
}

#endif //MAIEVERTIAS_FILEPOSIX_H
