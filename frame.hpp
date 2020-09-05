#pragma once
#include "stack.hpp"
#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_parser.hpp"

class Frame{
    Stack* operand_stack;
    u4 * locals;
    Parseclass * pclass;

    public:
    unsigned int pc;
    Frame(method_info* method);
    ~Frame();

    Stack * get_opstack();
    u4 * get_locals();

};