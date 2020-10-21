#pragma once
#include <stdlib.h>
#include "class_types.hpp"
#include "class_structures.hpp"
#include <vector>

enum Type {BYTE, SHORT, INTEGER, LONG, DOUBLE, CHAR, BOOLEAN, FLOAT, RETURN_ADDR, REFERENCE};

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
    Type type;
    Data data;
};

class Stack{
    public:

    int sp;
    int max_size;
    std::vector<Value> stack;

    Stack(int stack_size);
    virtual ~Stack();  

    int push(Value value);
    Data pop();
    Data peek();

    // getters and setters for sp

};