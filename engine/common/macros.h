#ifndef  _MACROS_H_
#define _MACROS_H_

#define CLEAN_DELETE(ptr)        do{ if(ptr) delete ptr; ptr=nullptr;}while(0);
#endif // ! __MACROS_H__
