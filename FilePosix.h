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
        static File current();

        class GetInfoError : public std::exception{
        public:
            GetInfoError(int err);
            ~GetInfoError();
            virtual const char *what() const noexcept ;
        protected:
        private:
            int m_err;
        };

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

        File(Path path);
        ~File();

        //read-only
        const Path &path()const noexcept;

        bool isRegularFile();
        bool isDirectory();
        bool isFIFO();
        bool isBlockFile();
        bool isCharacterFile();
        bool isSocket();
        //bool isEmpty();
        bool isSymlink();
        bool isOther();

        bool exist()const noexcept;
        operator bool()const noexcept;

        std::uint32_t size()const noexcept;

        File copy(const Path &);
        File &move(const Path &);
        void remove();

        iterator begin();
        iterator end();
    protected:
    private:
        void m_open_if_not();

        bool m_stated;
        struct stat m_stat;
        Path m_path;
    };
}

#endif //MAIEVERTIAS_FILEPOSIX_H
