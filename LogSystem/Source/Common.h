#pragma once

#define SafeDeletePtr(p) if(p!=nullptr){delete p; p=nullptr;}
#define SafeDeleteArray(p) if(p!=nullptr){delete [] p; p=nullptr;}

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define __CODELOCAL__ "FILE: ", __FILENAME__ , ", LINE: ",  __LINE__