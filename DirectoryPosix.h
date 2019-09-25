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
            const Path &m_path;
            Path m_name;
        };

        Directory(File &file);
        Directory(const Directory &) = delete;
        Directory(Directory &&) = delete;
        ~Directory();

        Directory &operator=(const Directory &) = delete;
        Directory &operator=(Directory &&) = delete;

        iterator begin();
        iterator end();
    protected:
    private:
        File &m_file;
        DIR *m_dir;
    };
}

#endif //MAIEVERTIAS_DIRECTORYPOSIX_H
