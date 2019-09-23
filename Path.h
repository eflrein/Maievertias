#ifndef MAIEVERTIAS_PATH_H
#define MAIEVERTIAS_PATH_H

#include <string>

namespace maievertias{
    class Path{
    public:
        Path(const char *str);
        ~Path();

        
    protected:
    private:
        std::string m_raw_path;
    };
}

#endif //MAIEVERTIAS_PATH_H
