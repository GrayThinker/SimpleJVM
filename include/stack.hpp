#pragma once
#include <stdlib.h>
#include "class_types.hpp"
#include "class_structures.hpp"
#include <vector>
#include <variant>

/*
create a class called generic container that has the basic enum Type
union data and struct value.
Then let stack, inherit from it and let operand stack and frame stack inherit from stack.
Also let locals inherit from it and modify Type, data.
*/


using data = std::variant<j_byte, j_short, j_int, j_long, j_char, j_bool, j_float, j_double>;
class Stack{
    public:
    int sp;
    int max_size;
    std::vector<data> stack;

    Stack(int stack_size);
    virtual ~Stack();  

    int push(data value);
    data pop();
    data peek();

    // getters and setters for sp

};