#pragma once
#include "class_file_stream.hpp"
int get_classfile_size(const char * file);

char* open_classfile(const char *classfile, int file_size, char* code_ptr);

Classfile_stream *load_stream(const char*classfile_path);