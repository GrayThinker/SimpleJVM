#pragma once
#include "java_class_types.hpp"
#include "class_file_stream.hpp"
#include "class_structures.hpp"
#include <iostream>

u1 *parse_overhead(Classfile_stream * classfile);

u2 get_cp_length(Classfile_stream *classfile);

cp_entry * parse_constant_pool_entries(u1 *cp_handle, u2 cp_length);

void print_cp(cp_entry * cp);

// constant pool parsing
// u1 * parse_constant_pool();
// // interface parsing    
// void parse_intefaces();
// // field parsing
// void parse_field_attr();
// void parse_fields();
// // method parsing
// void parse_methods_ls();
// void parse_method();
// void parse_exception_table();
