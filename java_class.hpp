#pragma once
#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include <iostream>

class Java_class : public Java_classfile_format{
    public:
    u1 * source;
    Java_class();
    virtual ~Java_class();
};