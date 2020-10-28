#pragma once

#include "class_heap.hpp"
#include "class_parser.hpp"
#include "precompiled.hpp"

class Runtime_env{
    /*
    stores pointers to spaces used by multiple threads
    like class heap, object heap as well as thread specific things
    like the stack frame

    a stack frame stores frames, frames store methods and method meta data,
    
    frames need a reference to the runtime constant pool of the class of the
    current method.

    methods store a reference to their corresponding class so maybe use that instead
    
    Method area is shared among all threads even though is stores per class methods
    and structures such as the run-time constant pool. Created on startup

    */
    public:
    Runtime_env();
    Runtime_env(Class_heap * class_heap);
    ~Runtime_env();

    Class_heap * class_heap;

};