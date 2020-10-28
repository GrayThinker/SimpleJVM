/*
class to load a class and all it's parent classes to the class heap
return a pointer to the newly loaded class
*/
#include "class_heap.hpp"

/*
Bootstrapper todo: 
    declare class heap
    declare object heap
    get initial program file > parse > load to heap
    create runtime env


*/
class Class_loader{
    // where will the loader be stored
    void load(Class_heap * class_heap, const char * class_name);
};
