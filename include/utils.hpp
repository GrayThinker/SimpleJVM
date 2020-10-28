#pragma once
#include <string>
#include "class_types.hpp"
#include "class_structures.hpp"

void printh(int output);
void printi(int output);
std::string utf_to_str(u1* bytes, u2 length);
std::string utfinfo_to_str(CONSTANT_Utf8_info info);

// std::string to_utf(u1* input, u2 length, std::string output);