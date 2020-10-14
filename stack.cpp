#include <iostream>
#include "class_types.hpp"
#include "stack.hpp"
#include <vector>

Stack::Stack(int stack_size){
    sp = 0;
    size = stack_size;
}

Stack::~Stack(){
};

void Stack::push(Data_type d_type, Data d_val){
        stack.push_back({d_type, d_val});
};

// template <typename T>

// void Stack::push(Data_type d_type, T d_val){
//     stack.push_back({d_type, d_val});
    // stack.push_back({Data_type, Data});
// };
