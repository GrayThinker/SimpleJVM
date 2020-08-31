#pragma once
#include "stack.hpp"
#include "class_types.hpp"
#include "class_structures.hpp"


class Frame(){
    private:
    Stack* operand_stack;

    public:
    unsigned int sp;
    unsigned int pc;
    Frame(method_info method);
    ~Frame();



    
}