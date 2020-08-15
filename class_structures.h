#pragma once
#include "java_class_types.h"

struct cp_info{
    u1 tag;
    u1 *info;  //array size depends on tag
};

struct attribute_info{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;  //[attribute_length]
};

struct field_info{
    u2 access_flags;
    u2 name_index;
    u2 attributes_count;
    attribute_info *attributes;  //[attributes_count]

};

struct method_info{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;  //[attributes_count]
};


struct Java_classfile_format{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;  //[constant_pool_count -1]
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;  //[interfaces_count]
    u2 fields_count;
    field_info *fields;  //[fields_count]
    u2 methods_count;
    method_info *methods;  //[methods_count;
    u2 attribute_count;
    attribute_info attributes;  //[attributes_count]
};

struct CONSTANT_Class_info{
    u1 tag;
    u2 name_index;
};

struct CONSTANT_Fieldref_info{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
};