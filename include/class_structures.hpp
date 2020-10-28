#pragma once
#include <iostream>
#include <string>
#include "class_types.hpp"

struct cp_info;
struct attribute_info;
struct field_info;
struct exception;
struct attribute;
union stack_map_frame;
//------------------------------------------------------------

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
    // std::string name;
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
    cp_entry(){};
    virtual ~cp_entry(){};
    // cp_entry(cp_entry &cp2){cp2.index = index; cp2.tag = tag;}
    u1 tag;
    u4 index;
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
struct StackMapTable_attribute{
    u2 name_index;
    u4 length;
    u2 number_of_entries;
    stack_map_frame* entries;
};

struct ConstantValue_attribute{
    u2 name_index;
    u4 length;
    u2 constantvalue_index;
};

struct Code_attribute{
    u2 name_index;
    u4 length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;  //[code_length]
    u2 exception_table_length;
    exception *exception_table; //[exception_table_length]
    u2 attribute_count;
    attribute *attributes;  //[attributes_count]
};

struct Exceptions_attribute{
    u2 name_index;
    u4 length;
    u2 number_of_exceptions;
    u2 * exception_index_table;
};

struct class_ {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
};

struct InnerClasses_attribute{
    u2 name_index;
    u4 length;
    u2 number_of_classes;
    class_ *classes;
};

struct EnclosingMethod_attribute{
    u2 name_index;
    u4 length;
    u2 class_index;
    u2 method_index;
};

struct Synthetic_attribute{
    u2 name_index;
    u4 length;
};

struct Signature_attribute{
    u2 name_index;
    u4 length;
    u2 signature_index;
};

struct SourceFile_attribute{
    u2 name_index;
    u4 length;
    u2 sourcefile_index;
};

struct SourceDebugExtension_attribute{
    u2 name_index;
    u4 length;
    // u1* debug_extension[attr_length]
};

struct line_number_entry{
    u2 start_pc;
    u2 line_number;
};

struct LineNumberTable_attribute{
    u2 name_index;
    u4 length;
    u2 line_number_table_length;
    line_number_entry * line_number_table;
};

struct local_var{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 desc_index;
    u2 index;
};

struct LocalVariableTable_attribute{
    u2 name_index;
    u4 length;
    u2 local_var_table_length;
    local_var * local_var_table;
};

struct local_var_type{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 signature_index;
    u2 index;
};

struct LocalVariableTypeTable_attribute{
    u2 name_index;
    u4 length;
    u2 local_var_type_table_length;
    local_var_type *local_var_type_table;    
};

struct Deprecated_attribute{
    u2 name_index;
    u4 length;
};

struct element{
    int value; //TODO: check correct implementation
};

struct element_value_pair{
    u2 element_name_index;
    element element_value;
};

struct annotation{
    u2 type_index;
    u2 num_element_value_pairs;
    element_value_pair * element_value_pairs;
};

struct RuntimeVisibleAnnotations_attribute{
    u2 name_index;
    u4 length;
    u2 num_annotations;
    annotation *annotations;
};

struct RuntimeInvisibleAnnotations_attribute{
    u2 name_index;
    u4 length;
    u2 num_annotations;
    annotation *annotations;
};

struct RuntimeVisibleParameterAnnotations_attribute{
    u2 name_index;
    u4 length;
    u1 num_parameters;
    /*
    { u2 num_annotations;
    annotation annotations[num_annotations];
    } parameter_annotations[num_parameters];
    */
};

struct RuntimeInvisibleParameterAnnotations_attribute{
    u2 name_index;
    u4 length;
    u1 num_parameters;
    /*
    { u2 num_annotations;
    annotation annotations[num_annotations];
    } parameter_annotations[num_paramenters];
    */
};

struct RuntimeVisibleTypeAnnotations_attribute{
    u2 name_index;
    u4 length;
    u2 num_annotations;
    // type_annotation annotations[num_annotations];
};

struct RuntimeInvisibleTypeAnnotations_attribute{
    u2 name_index;
    u4 length;
    u2 num_annotations;
    // type_annotation annotations;
};

struct AnnotationDefault_attribute{
    u2 name_index;
    u4 length;
    // element_value default_value;
};

struct Bootstrap_attribute{
    u2 name_index;
    u4 length;
    u2 num_bootstrap_methods;
    /*
    { u2 boostrap_method_ref;
    u2 num_bootstrap_arguments;
    u2 bootstrap_arguments[num_bootstrap_arguments];
    } bootstrap_methods[num_bootstrap_methods];
    */
};

struct MethodParameters_attribute{
    u2 name_index;
    u4 length;
    u1 parameters_count;
    // parameter * parameters;
};

    enum Attr_types {
        //TODO: make same as attr_name
        constant_value,
        stack_map,
        code,
        except,
        inner_class,
        enclosed_method,
        synthetic,
        signature,
        source_file,
        source_debug,
        line_num_table,
        local_variable_table,
        local_variable_type_table,
        deprecated,
        run_visible_annotations,
        run_invisible_annotations,
        run_visible_parameter,
        run_invisible_parameter,
        run_visible_type,
        run_invisible_type,
        default_,
        bootstrap,
        method_parameter
    };

struct attribute{
    Attr_types type;
    union {
        ConstantValue_attribute constval_attr;
        StackMapTable_attribute stackmap_attr;
        Code_attribute code_attr;
        Exceptions_attribute except_attr;
        InnerClasses_attribute inclass_attr;
        EnclosingMethod_attribute encmeth_attr;
        Synthetic_attribute synth_attr;
        Signature_attribute sign_attr;
        SourceFile_attribute src_attr;
        SourceDebugExtension_attribute srcdebext_attr;
        LineNumberTable_attribute linenumtab_attr;
        LocalVariableTable_attribute localvartab_attr;
        LocalVariableTypeTable_attribute localvartype_attr;
        Deprecated_attribute depr_attr;
        RuntimeVisibleAnnotations_attribute runvisannot_attr;
        RuntimeInvisibleAnnotations_attribute runinvannot_attr;
        RuntimeVisibleParameterAnnotations_attribute runvispar_attr;
        RuntimeInvisibleParameterAnnotations_attribute runinvpar_attr;
        RuntimeVisibleTypeAnnotations_attribute runvistype_attr;
        RuntimeInvisibleTypeAnnotations_attribute runinvtype_attr;
        AnnotationDefault_attribute default_attr;
        Bootstrap_attribute boot_attr;
        MethodParameters_attribute mthdpar_attr;
    };
};


struct method_info{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute *attributes;  //[attributes_count]
};

//-------------------------------------------------

struct parameter{
    u2 name_index;
    u2 access_flags;
};

//-------------------------------------------------

struct type_parameter_target {
    u1 type_parameter_index;
};

struct supertype_target {
    u2 supertype_index;
};

struct type_parameter_bound_target{
    u1 type_parameter_index;
    u1 bound_index;
};

struct empty_target{};

struct formal_parameter_target{
    u1 formal_parameter_target;
};


struct type_annotation {
    u1 target_type;
    union {
        type_parameter_target t_par_target;
        supertype_target t_sup_target;
    };
    // type_path target_path;
    // u2 type_index;
    // u2 num_element_value_pairs;
    // { u2 element_name_index;
    // element_value value;
    // } element_value_pairs[num_element_value_pairs];

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
    attribute *attributes;  //[attributes_count]
};