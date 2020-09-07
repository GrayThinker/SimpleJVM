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

int utf_to_char(u1* input, std::string *output){
    int length;
    std::string temp;
    u1 ch1, ch2, ch3;

    switch((ch1 = input[0]) >> 4){
        case 0x8: case 0x9: case 0xA: case 0xB: case 0xF:
            break;

        case 0xC: case 0xD: // 110xxxxx
            if(((ch2 = input[1]) & 0xC0) = 0x80){
                u1 high_five = ch1 & 0x1F;
                u1 low_six = ch2 & 0x3F;
                temp = (high_five << 6) + low_six;
                length = 2;
            }
            break;
        
        case 0xE: // 1110xxxx
            if(((ch2 = input[1]) & 0xC0 = 0x80) && ((ch3 = input[2]) & 0xC0 = 0x80)){
                u1 high_four = ch1 & 0x0F;
                u2 mid_six = ch2 & 0x3F;
                u2 low_six = ch3 & 0x3F;
                temp = ((high_four << 6) + mid_six) << 6 + low_six;
                length = 3;
            }
            break;
        default: //skip char
            temp = ch1;
            length = 1;
            break;
    }
}
