#include <iomanip>
#include <iostream>
#include "utils.hpp"
#include "class_types.hpp"

void printh(int output){
    std::cout<< std::setw(8) << std::setfill('0') << std::hex <<output<<std::endl;
}

void printi(int output){
    std::cout<<output<<std::endl;
}

std::string to_utf(u1* input, u2 length, std::string output){

    for (int i = 0; i < length; ++i){
        u1 cur = input[i];

    }
    return output;
}
