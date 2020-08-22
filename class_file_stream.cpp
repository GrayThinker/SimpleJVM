#include "class_file_stream.hpp"
#include "java_class_types.hpp"

// TODO: implement java class file stream to by used by the parser.
Classfile_stream::Classfile_stream(const char *path, u1 *source, int length){
    _start = source;
    _current = source;
    _size = length;
    _path = path;
    _offset = 0;
}

u4 Classfile_stream::getu4(){   
    u4 output = (u4)((u4)((_current)[0]<<24) & 0xFF000000 | (u4)((_current)[1]<<16) & 0x00FF0000 | (u4)((_current)[2]<<8) & 0x0000FF00| (u4)((_current)[3]) & 0x000000FF);
    _current += size_u4;
    _offset += size_u4;
    return output;
}

u2 Classfile_stream::getu2(){
    u2 output = (u2)((u2)((_current[0])<<8) & 0xFF00 | (u2)((_current)[1] & 0x00FF));
    _current += size_u2;
    _offset += size_u2;
    return output;
}

u1 Classfile_stream::getu1(){
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
    _current = _start + offset;
}

void Classfile_stream::set_current(u1* current){
    _current = current;
    _offset = _current - _start;
}