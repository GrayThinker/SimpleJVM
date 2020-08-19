#include <iomanip>
#include <iostream>
#include "utils.hpp"
#include "java_class_types.hpp"

void printh(int output){
    std::cout<< std::setw(8) << std::setfill('0') << std::hex <<output<<std::endl;
}

void printi(int output){
    std::cout<<output<<std::endl;
}
