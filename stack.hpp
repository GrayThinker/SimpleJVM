#include <stdlib.h>
#include "java_class_types.hpp"

class Stack{
    private:
    int sp;
    int stack_size;
    u4* stack;

    public:
    Stack(){
        sp = 0;
        stack = new u4[stack_size];
    };

    virtual ~Stack(){
        delete stack;
    };
    
    int get_sp(){
        return sp;
    }
    u4 read_stack(){
        return stack[sp];
    }

    void push_stack(u4 input){ //Template needed
        stack[sp++] = input;
    }

    u4 pop_stack(){
        return stack[sp--];
    }

    void inc_sp(int i = 1){
        sp += i;
        //check if sp < stack-size
    }

    void dec_sp(int i = 1){
        sp -= i;
        //check if sp > 0
    }


};