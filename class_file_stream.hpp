#pragma once
#include "java_class_types.hpp"

class Classfile_stream{
    private:
    u1 *_start;  // pointer to the beginning of the file
    u1 *_current;  // pointer to the current code stream char
    int _size;
    int _offset; // number of bytes we have already read
    const char *_path;

    public:
    Classfile_stream(const char *path, u1 *source, int length){
        _start = source;
        _current = source;
        _size = length;
        _path = path;
    };
    public:
    u4 get_u4();
    u2 get_u2();
    u1 get_u1();
};