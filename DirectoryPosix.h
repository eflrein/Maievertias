#ifndef MAIEVERTIAS_DIRECTORYPOSIX_H
#define MAIEVERTIAS_DIRECTORYPOSIX_H

#include <exception>
#include "File.h"

namespace maievertias{
    class Directory{
    public:
        class iterator{
        public:
            iterator(DIR *dir,const Path &path);
            iterator(const iterator &) = delete;
            iterator(iterator &&) = default;
            ~iterator();

            iterator &operator=(const iterator &) = delete;
            iterator &operator=(iterator &&) = default;

            iterator &operator++()noexcept;
            File operator*()const noexcept;

            bool operator==(const iterator &rhs)const noexcept;
            bool operator!=(const iterator &rhs)const noexcept;

        protected:
        private:
            DIR *m_dir;
            dirent *m_dirinfo;
            const Path &m_path;
        };

        Directory(const File &file);
        Directory(const Directory &) = delete;
        Directory(Directory &&) = delete;
        ~Directory();

        Directory &operator=(const Directory &) = delete;
        Directory &operator=(Directory &&) = delete;

        iterator begin()const;
        iterator end()const;
    protected:
    private:
        const File &m_file;
        DIR *m_dir;
    };
}

#endif //MAIEVERTIAS_DIRECTORYPOSIX_H
