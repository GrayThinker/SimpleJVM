#include <iostream>
#include "class_types.hpp"
#include "stack.hpp"

Stack::Stack(){
    sp = 0;
    stack = new u4[stack_size];
}

Stack::~Stack(){
    delete stack;
};

int Stack::get_sp(){
    return sp;
}
void Stack::set_sp(int i){
    if (i > stack_size){
        std::cerr << "Stack Overflow" << std::endl;
    } else {
    sp = i;
    // TODO: return bool
    }
}
u4 Stack::peek(){
    return stack[sp];
}
void Stack::push(u4 input){ //Template needed
    stack[sp++] = input;
}

u4 Stack::pop(){
    if (sp < 1){
        std::cerr << "Stack Underflow" << std::endl;
        return 0;
    } else {
        return stack[sp--];
    }
}

void Stack::inc(unsigned int i = 1){
    if (sp + i >= stack_size){
        std::cerr << "Stack Overflow" << std::endl;
    } else {
        sp += i;
    } //TODO: return bool
}

void Stack::dec(unsigned int i = 1){
    if (sp < i){
        std::cerr << "Stack Underflow" <<std::endl;
    } else {
        sp -= i;
    } //TODO: return bool
}

void Stack::_goto(unsigned int i){
    if (i > stack_size){
        std::cerr << "Stack Overflow" << std::endl;
    } else {
        sp = i;
    } //TODO: return bool
}
