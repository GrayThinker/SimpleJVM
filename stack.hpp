#pragma once
#include <stdlib.h>
#include "class_types.hpp"


class Stack{
    private:
    int sp;
    int stack_size;
    u4* stack;

    public:
    Stack(int stack_size);
    virtual ~Stack();  

    u4 peek();
    u4 pop();
    void push(u4 input);
    void inc(unsigned int i = 1);
    void dec(unsigned int i = 1);
    int get_sp();
    void set_sp(int new_p);
    void _goto(unsigned int i);

};