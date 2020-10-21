#include <iostream>
#include "class_structures.hpp"
#include "class_types.hpp"
#include "stack.hpp"
#include <vector>

Stack::Stack(int stack_size){
    sp = 0;
    max_size = stack_size;
}

Stack::~Stack(){
};


int Stack::push(Value value){
    // TODO: check sp
    stack.push_back(value);
    return ++sp;
};

Data Stack::pop(){
    // TODO: check sp
    auto ret_val = stack.back();
    stack.pop_back();
    sp--;
    return ret_val.data;
}

Data Stack::peek(){
    // TODO: check sp
    return stack.back().data;
}
