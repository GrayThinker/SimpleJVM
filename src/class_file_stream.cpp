#include "class_file_stream.hpp"
#include "class_types.hpp"
#include <fstream>
#include <iostream>

Classfile_stream::Classfile_stream(const char *path){
    _path = path;
    _size = get_size(_path);
    _begin = new u1[_size];
    open();
    _current = _begin;
    _offset = _current - _begin;
}

Classfile_stream::~Classfile_stream(){

}

void Classfile_stream::open(){
    FILE *temp = fopen(_path, "rb");
    if (fread(_begin, _size, 1, temp)){
        fclose(temp);
    }
    else{
        fclose(temp);
        std::cerr << "Couldn't read file";
    }
}

int Classfile_stream::get_size(const char * path){
    FILE *temp = fopen(_path, "rb");
    fseek(temp, 0L, SEEK_END);
    int size = ftell(temp);
    fclose(temp);
    return size;
}


u4 Classfile_stream::read_u4(){   
    u4 output = (u4)((u4)((_current)[0]<<24) & 0xFF000000 | (u4)((_current)[1]<<16) & 0x00FF0000 | (u4)((_current)[2]<<8) & 0x0000FF00| (u4)((_current)[3]) & 0x000000FF);
    _current += size_u4;
    _offset += size_u4;
    return output;
}

u2 Classfile_stream::read_u2(){
    u2 output = (u2)((u2)((_current[0])<<8) & 0xFF00 | (u2)((_current)[1] & 0x00FF));
    _current += size_u2;
    _offset += size_u2;
    return output;
}

u1 Classfile_stream::read_u1(){
    u1 output = (u1)((_current)[0]);
    _current += size_u1;
    _offset += size_u1;
    return output;
}

u1 *Classfile_stream::get_current(){
    return _current;
}

int Classfile_stream::get_offset(){
    return _offset;
}

void Classfile_stream::set_offset(int offset){
    _offset = offset;
    _current = _begin + offset;
}

void Classfile_stream::set_current(u1* current){
    _current = current;
    _offset = _current - _begin;
}

const char * Classfile_stream::path(){
    return _path;
}