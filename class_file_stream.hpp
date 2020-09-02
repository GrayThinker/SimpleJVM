#pragma once
#include "class_types.hpp"
#include <memory>

class Classfile_stream{
    private:
    FILE *_source;
    u1 *_begin;  // pointer to the beginning of the file
    u1 *_current;  // pointer to the current code stream char
    int _size;
    int _offset; // number of bytes we have already read
    const char *_path;

    public:
    Classfile_stream(const char *path);
    virtual ~Classfile_stream();
    u4 getu4();
    u2 getu2();
    u1 getu1();
    u1 * get_current();
    int get_offset();
    void set_offset(int offset);
    void set_current(u1* current);
    void get_size();
    void open();
    const char * path();
};