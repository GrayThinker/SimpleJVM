#pragma once
#include "java_class_types.hpp"

#define JAVA_CLASS_MAGIC = 0xcafebabe

// constant pool parsing
void parse_constant_pool_entries(u1 *cpool_ptr, u4 cpool_length);
u1 * parse_constant_pool();

// interface parsing    
void parse_intefaces();

// field parsing
void parse_field_attr();
void parse_fields();

// method parsing
void parse_methods_ls();
void parse_method();
void parse_exception_table();

