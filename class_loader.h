#pragma once
#include <fstream>

int get_classfile_size(const char * file);

char* open_classfile(const char *classfile, int file_size, char* code_ptr);