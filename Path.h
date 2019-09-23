#ifndef MAIEVERTIAS_PATH_H
#define MAIEVERTIAS_PATH_H

#include <string>
#include <list>
#include <iostream>

/* Windows    C:\Users\fuck.txt
 * Unix    \usr\fuck.txt
 */

namespace maievertias{
    class Path{
    public:
        using string_iterator = std::string::iterator;
        
        class iterator{
        public:
            iterator(string_iterator itr,string_iterator end);
            ~iterator();
            
            iterator &operator++()noexcept
            const iterator operator++(int)noexcept;
            
            bool operator==()const noexcept;
            bool operator!=()const noexcept;
            
            Path operator*()const noexcept;
        protected:
        private:
            string_iterator m_itr;
            string_iterator m_end;
        }
    
        Path(const std::string &str);
        Path(const Path &);
        Path(Path &&);
        ~Path();
        
        Path &operator=(const Path &);
        Path &operator=(Path &&);
        
        const char *c_str()const noexcept;

        Path name()const noexcept;
        Path extension()const noexcept;
        Path parent()const noexcept;
        Path path()const noexcept;
        Path stem()const noexcept;
        Path root()const noexcept;
        bool empty()const noexcept;
        
        iterator begin();
        iterator end();
        
        friend std::ostream &operator<<(std::ostream &os,const Path &os);
        friend std::istream &operator<<(std::istream &is,const Path &os);
    protected:
    private:
        std::string m_raw_path;
        
    };
}

#endif //MAIEVERTIAS_PATH_H
