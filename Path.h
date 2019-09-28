#ifndef MAIEVERTIAS_PATH_H
#define MAIEVERTIAS_PATH_H

#include <string>
#include <list>
#include <iostream>

/* Windows  C:\Users\fuck.txt
 * Unix     /usr/fuck.txt
 */

namespace maievertias{
    class Path{
    public:
        using string_iterator = std::string::iterator;
        using const_string_iterator = std::string::const_iterator;
        
        class iterator{
        public:
            using itr_t = std::list<std::pair<const_string_iterator,const_string_iterator>>::iterator;

            iterator(itr_t itr);
            ~iterator();
            
            iterator &operator++()noexcept;
            const iterator operator++(int)noexcept;
            
            bool operator==(const iterator &)const noexcept;
            bool operator!=(const iterator &)const noexcept;
            
            Path operator*()const noexcept;
        protected:
        private:
            itr_t m_itr;
        };
    
        Path(const char *str);
        Path(std::string str);
        Path(const Path &);
        Path(Path &&)noexcept;
        ~Path();
        
        Path &operator=(const Path &);
        Path &operator=(Path &&)noexcept;

        bool operator==(const Path &rhs)const noexcept;
        bool operator!=(const Path &rhs)const noexcept;
        bool operator<=(const Path &rhs)const noexcept;
        bool operator>=(const Path &rhs)const noexcept;
        bool operator< (const Path &rhs)const noexcept;
        bool operator> (const Path &rhs)const noexcept;

        Path operator/(const Path &rhs)const noexcept;
        Path &operator/=(const Path &rhs)noexcept;
        
        const char *c_str()const noexcept;

        Path name()const;
        Path extension()const;
        Path parent()const;
        Path root()const;
        bool empty()const noexcept;
        bool absolute()const noexcept;
        bool relative()const noexcept;

        bool hasRoot()const noexcept;

        bool isSelf()const noexcept;
        bool isParent()const noexcept;
        bool isHome()const noexcept;


        Path &changeSeparator(char seperator)noexcept;
        
        iterator begin();
        iterator end();
        
        friend std::ostream &operator<<(std::ostream &os,const Path &path){
            os << path.m_raw_path;
            return os;
        }
//        friend std::istream &operator>>(std::istream &is,      Path &path){
//
//        }
    protected:
    private:
        void m_init();
        
        char m_separator;
        bool m_has_root;
        std::string m_raw_path;
        std::list<std::pair<const_string_iterator,const_string_iterator>> m_components;//the pair of iterators describe a range (component)
    };
}

#endif //MAIEVERTIAS_PATH_H
