#pragma once
#include "stack.hpp"
#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_parser.hpp"

class Frame{
    int _mp;
    method_info* _method;
    Parseclass* _parent_class;
    code_attribute* _code;
    Stack* _operand_stack;
    u4 * _locals;

    public:
    code_attribute* code;
    Stack* stack;
    u4 * locals;
    unsigned int pc;
    Frame(method_info* method, Parseclass *parent_class);
    ~Frame();

    Stack * get_opstack();
    u4 * get_locals();
    void _parse_code(attribute_info* code_handle, code_attribute *code);
};