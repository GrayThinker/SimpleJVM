#pragma once
#include <iostream>
#include "java_class_types.hpp"

struct cp_info{  //for reference only, use cp_entry
    u1 tag;
    u1 *info;
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

struct exception{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

//------------------------------------------------------------
struct CONSTANT_Class_info{
    u1 tag;
    u2 name_index;
};

struct CONSTANT_Fieldref_info{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_String_info{
    u1 tag;
    u2 string_index;
};

struct CONSTANT_Integer_info{
    u1 tag;
    u4 bytes;
};

struct CONSTANT_Float_info{
    u1 tag;
    u4 bytes;
};

struct CONSTANT_Long_info{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_Double_info{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_NameAndType_info{
    u1 tag;
    u2 name_index;
    u2 descriptor;
};

struct CONSTANT_Utf8_info {
    u1 tag;
    u2 length;
    u1 *bytes;  //[length]
};

struct CONSTANT_MethodHandle_info{
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
};

struct CONSTANT_MethodType_info{
    u1 tag;
    u2 descriptor_index;
};

struct CONSTANT_InvokeDynamic_info{
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
};

/*
 *The union is only as big as necessary to hold its largest data member. 
 *The other data members are allocated in the same bytes as part of that largest member. 
 *The details of that allocation are implementation-defined but all 
 *non-static data members will have the same address (since C++14).
 */
struct cp_entry{
    public:
    u4 index;
    u1 tag; 
    union {
        CONSTANT_Class_info c_class;
        CONSTANT_Fieldref_info c_fieldref;
        CONSTANT_Methodref_info c_methodref;
        CONSTANT_InterfaceMethodref_info c_interfacemethodref;
        CONSTANT_String_info c_string;
        CONSTANT_Integer_info c_integer;
        CONSTANT_Float_info c_float;
        CONSTANT_Long_info c_long;
        CONSTANT_Double_info c_double;
        CONSTANT_NameAndType_info c_nameandtype;
        CONSTANT_Utf8_info c_utf8;
        CONSTANT_MethodHandle_info c_methodhandle;
        CONSTANT_MethodType_info c_methodtype;
        CONSTANT_InvokeDynamic_info c_invokedynamic;
    };
};

//------------------------------------------------------------

struct ConstantValue_attribute{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
};

struct Code_attribute{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;  //[code_length]
    u2 exception_table_length;
    exception *exception_table; //[exception_table_length]
    u2 attribute_count;
    attribute_info *attributes;  //[attributes_count]
};

//------------------------------------------------------------

struct Top_variable_info{
    u1 tag = ITEM_Top;  //0
};

struct Integer_variable_info{
    u1 tag = ITEM_Integer;  //1
};

struct Float_variable_info{
    u1 tag = ITEM_Float;  //2
};

struct Long_variable_info{
    u1 tag = ITEM_Long;  //4
};

struct Double_variable_info{
    u1 tag = ITEM_Double;  //3
};

struct Null_variable_info{
    u1 tag = ITEM_Null;  //5
};

struct UninitializedThis_variable_info{
    u1 tag = ITEM_UninitializedThis;  //6
};

struct Object_variable_info{
    u1 tag = ITEM_Object;  //7
    u2 cp_index;
};

struct Uninitialized_variable_info{
    u1 tag = ITEM_Uninitialized;  //8
    u2 offset;
};

union verification_type_info{  //TODO: names
    struct Top_variable_info;
    struct Integer_variable_info;
    struct Float_variable_info;
    struct Long_variable_info;
    struct Double_variable_info;
    struct Null_variable_info;
    struct UninitializedThis_variable_info;
    struct Object_variable_info;
    struct Uninitialized_variable_info;
};

//------------------------------------------------------------
// TODO: Assign constants values

struct same_frame{
    u1 frame_type;  //= SAME (0-63)
};

struct same_locals_1_stack_item_frame{
    u1 frame_type;  //= SAME_LOCALS_1_STACK_ITEM (64-127)
    // verification_type_info stack[1]
};

struct same_locals_1_stack_item_frame_extended{
    u1 frame_type;  //= SAME_LOCALS_1_STACK_ITEM_EXTENDED (247)
    u2 offset_delta;
    // verification_type_info stack[1]
};

struct chop_frame{
    u1 frame_type;  //= CHOP (248-250)
    u2 offset_delta;
};

struct same_frame_extended{
    u1 frame_type;  //= SAME_FRAME_EXTENDED (251)
    u2 offset_delta;
};

struct append_frame{
    u1 frame_type;  //= APPEND (252-254)
    u2 offset_delta;
    // verification_type_info locals[frame_type - 25]
};

struct full_frame{
    u1 frame_type;  //= FULL_FRAME (255)
    u2 offset_delta;
    u2 number_of_locals;
    // verification_type_info locals[number_of_locals]
    u2 number_of_stack_items;
    // verification_type_info stack[number_of_stack_items]
};

union stack_map_frame{  //TODO: names
    struct same_frame;
    struct same_locals_1_stack_item_frame;
    struct same_locals_1_stack_item_frame_extended;
    struct chop_frame chop_frame;
    struct same_frame_extended;
    struct append_frame;
    struct full_frame;
};

struct StackMapTable_attribute{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_entries;
    stack_map_frame entries; //[number_of_entries];
};

//------------------------------------------------------------
struct Java_classfile_format{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_entry *constant_pool;  //[constant_pool_count -1]
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
