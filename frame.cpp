#include "frame.hpp"
#include "stack.hpp"
#include "class_types.hpp"

Frame::Frame(method_info* method){
    int mp = 0;
    // code_attribute code = *(method->attributes);
    
    code_attribute* code;
    // code = method->attributes; attr to code attr
    operand_stack = new Stack(1000/*method->attributes->max_length*/);
    locals = new u4(100/*method->attributes->max_locals*/);
    //TODO: get parent class
}

Frame::~Frame(){
    if (locals){
        delete locals;
    }
    if (operand_stack){
        delete operand_stack;
    }
}

Stack* Frame::get_opstack(){
    return operand_stack;
}

u4* Frame::get_locals(){
    return locals;
}