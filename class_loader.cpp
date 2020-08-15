#include "class_loader.h"

int get_classfile_size(const char * file){
    FILE *ptr;
    ptr = fopen(file, "rb"); //TODO: error handling
    fseek(ptr, 0L, SEEK_END);
    long int res = ftell(ptr);
    return res;
}

char* open_classfile(const char *classfile, int file_size, char* code_ptr){
    FILE *ptr;
    ptr = fopen(classfile, "rb"); //TODO: error handling
    fread(code_ptr, file_size, 1, ptr);
    fclose(ptr);
    return code_ptr;  //TODO: change to return true or false
}