#pragma once
#include "stack.hpp"
#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_parser.hpp"

class Frame{
/*
    A frame needs a method, reference to constant pool, operand stack, 
    locals, reference to runtime env
*/

    method_info* _method;
    Java_class* _parent_class;
    public:
    Frame();
    Frame(method_info* method, Java_class * parent_class);
    ~Frame();
    Stack* _op_stack;
//     u4* _locals;

// //     public:
// //     code_attribute* code;
// //     Stack* stack;
// //     u4 * locals;
// //     unsigned int pc;
};