#pragma once
#include <stdlib.h>
#include "class_types.hpp"
#include <vector>

class Stack{
    public:
    
    union Data {
        signed char as_byte;
        signed short as_short;
        signed int as_int;
        signed long as_long;
        unsigned short as_char;
        bool as_bool;
        float as_float;
        double as_double;
        u1 * as_returnAddr;
        void * as_reference;
    };

    struct Value{
        Data_type type;
        Data data;
    };

    int sp;
    int size;
    std::vector<Value> stack;

    Stack(int stack_size);
    
    virtual ~Stack();  

    Data peek();
    // u4 peek();
    u4 pop();

    void push(Data_type d_type, Data d_val);
    
    void inc(unsigned int i = 1);
    void dec(unsigned int i = 1);
    int get_sp();
    void set_sp(int new_p);
    void _goto(unsigned int i);

};