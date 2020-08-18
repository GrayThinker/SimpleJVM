#include "class_file_stream.hpp"
#include "java_class_types.hpp"

// TODO: implement java class file stream to by used by the parser.


u4 Classfile_stream::getu4(){   
    u4 output = (u4)((u4)((_current)[0]<<24) & 0xFF000000 | (u4)((_current)[1]<<16) & 0x00FF0000 | (u4)((_current)[2]<<8) & 0x0000FF00| (u4)((_current)[3]) & 0x000000FF);
    _current += size_u4;
    return output;
}
u2 Classfile_stream::getu2(){
    u2 output = (u2)((u2)((_current[0])<<8) & 0xFF00 | (u2)((_current)[1] & 0x00FF));
    _current += size_u2;
    return output;
}

u1 Classfile_stream::getu1(){
    u1 output = (u1)((_current)[0]);
    _current += size_u1;
    return output;
}

u1 *Classfile_stream::get_current(){
    return _current;
}