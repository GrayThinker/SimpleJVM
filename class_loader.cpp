#include <fstream>
#include "class_loader.hpp"
#include "java_class_types.hpp"
#include "class_file_stream.hpp"

int get_classfile_size(const char * file){
    FILE *ptr;
    ptr = fopen(file, "rb"); //TODO: error handling
    fseek(ptr, 0L, SEEK_END);
    long int res = ftell(ptr);
    return res;
}

u1 * open_classfile(const char *classfile, int file_size, u1* code_ptr){
    FILE *ptr;
    ptr = fopen(classfile, "rb"); //TODO: error handling
    fread(code_ptr, file_size, 1, ptr);
    fclose(ptr);
    return code_ptr;  //TODO: change to return true or false
}

Classfile_stream *load_stream(const char* classfile_path){
    int classfile_size = get_classfile_size(classfile_path);
    u1 *code_stream =  new u1[classfile_size];
    open_classfile(classfile_path, classfile_size, code_stream); // change to create classfilestream object;
    return new Classfile_stream(classfile_path, code_stream, classfile_size);
}