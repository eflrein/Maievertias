#ifndef MAIEVERTIAS_DIRECTORY_H
#define MAIEVERTIAS_DIRECTORY_H

#if  defined(__GUNC__) || defined(__MINGW32__)
#include "DirectoryPosix.h"
#endif

#if defined(_MSVC_VER)
//#include "DirectoryWindows.h"
#endif

#endif //MAIEVERTIAS_DIRECTORY_H
