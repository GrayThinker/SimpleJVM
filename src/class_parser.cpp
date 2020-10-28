#include "class_parser.hpp"
#include "class_structures.hpp"
#include "class_types.hpp"
#include "utils.hpp"
#include <iostream>
#include <string.h>
#include "class_heap.hpp"

Java_class::Java_class(){}

int Java_class::parse_cp_entry(u1 *cp_handle, cp_entry *cp, int index){
    int cp_cur = 0;
    u1 tag = get_u1(&cp_handle[cp_cur]); cp_cur+= 1;
    cp->tag = tag;
    cp->index = index;
    //TODO: trace bool to print out entries during parse
    switch(tag){
        case CONSTANT_Class:{
            u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_class = CONSTANT_Class_info{
                tag, name_index
            };
        }break;
        case CONSTANT_Fieldref:{
            u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u2 name_and_type = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_fieldref = CONSTANT_Fieldref_info{ tag, class_index, name_and_type };
        } break;
        case CONSTANT_Methodref:{
            u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u2 name_and_type = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;            
            cp->c_methodref = CONSTANT_Methodref_info{ tag, class_index, name_and_type };
        } break;
        case CONSTANT_InterfaceMethodref:{
            u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u2 name_and_type = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_interfacemethodref = CONSTANT_InterfaceMethodref_info{ tag, class_index, name_and_type };
        } break;
        case CONSTANT_String:{
            u2 string_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_string = CONSTANT_String_info{
                tag, string_index
            };
        }break;
        case CONSTANT_Integer:{
            u4 bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            cp->c_integer = CONSTANT_Integer_info{ tag, bytes };
        } break;
        case CONSTANT_Float:{
            u4 bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            cp->c_float = CONSTANT_Float_info{ tag, bytes };
        } break;

        case CONSTANT_Long:{
            u4 high_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            u4 low_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            cp->c_long = CONSTANT_Long_info{ tag, high_bytes, low_bytes};
            ++index;
        } break;
        case CONSTANT_Double:{
            u4 high_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            u4 low_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
            cp->c_double = CONSTANT_Double_info{ tag, high_bytes, low_bytes };
            ++index;
        } break;
        case CONSTANT_NameAndType:{
            u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u2 descriptor = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_nameandtype = CONSTANT_NameAndType_info{
                tag, name_index, descriptor
            };
        } break;
        case CONSTANT_Utf8:{
            u2 length = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u1 *bytes = new u1[length];
            bytes = &cp_handle[cp_cur]; cp_cur += length;
            // std::string s(reinterpret_cast<char const*>(bytes));
            cp->c_utf8 = CONSTANT_Utf8_info{
                tag, length, bytes
            };
        } break;
        case CONSTANT_MethodHandle:{
            u1 reference_kind = get_u1(&cp_handle[cp_cur]); cp_cur += size_u1;
            u2 reference_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_methodhandle = CONSTANT_MethodHandle_info{ tag, reference_kind, reference_index };            
        } break;
        case CONSTANT_MethodType:{
            u2 descriptor_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_methodtype = CONSTANT_MethodType_info{ tag, descriptor_index };
        } break;        
        case CONSTANT_InvokeDynamic:{
            u2 bootstrap_method_attr_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            u2 name_and_type_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
            cp->c_invokedynamic = CONSTANT_InvokeDynamic_info{
                tag, bootstrap_method_attr_index, name_and_type_index
            };
        }break;
        
    }
    return cp_cur;
}

void Java_class::print_cp(){
    for (int i = 1; i < constant_pool_count; ++i){
        // std::cout << constant_pool[i].tag;
        switch(constant_pool[i].tag){
            case CONSTANT_Class:  //{?
                std::cout<<"#"<<constant_pool[i].index<<" = Class\t\t#"
                <<constant_pool[i].c_class.name_index << std::endl;
                break;
            case CONSTANT_Fieldref:
                std::cout<<"#"<<constant_pool[i].index<<" = Fieldref\t\t#"
                <<constant_pool[i].c_fieldref.class_index
                <<" #"<<constant_pool[i].c_fieldref.name_and_type_index<<std::endl;
                break;
            case CONSTANT_Methodref:
                std::cout<<"#"<<constant_pool[i].index<<" = Methodref\t\t#"
                <<constant_pool[i].c_methodref.class_index
                <<" #"<<constant_pool[i].c_methodref.name_and_type_index<<std::endl;
                break;
            case CONSTANT_InterfaceMethodref:
                std::cout<<"#"<<constant_pool[i].index<<" = InterfaceMethodref\t\t"
                <<"#"<<constant_pool[i].c_interfacemethodref.class_index
                <<" #"<<constant_pool[i].c_interfacemethodref.name_and_type_index<<std::endl;
                break;
            case CONSTANT_String:
                std::cout<<"#"<<constant_pool[i].index<<" = String\t\t"
                <<"#"<<constant_pool[i].c_string.string_index<<std::endl;
                break;
            case CONSTANT_Integer:
                std::cout<<"#"<<constant_pool[i].index<<" = Integer"
                <</*"\t"<<constant_pool[i].c_integer.bytes<<*/std::endl;
                break;
            case CONSTANT_Float:
                std::cout<<"#"<<constant_pool[i].index<<" = Float"
                <</*"\t"<<constant_pool[i].c_float.bytes<<*/std::endl;
                break;
            case CONSTANT_Long:
                std::cout<<"#"<<constant_pool[i].index<<" = Long"
                <</*"\t"<<constant_pool[i].c_long.high_bytes<<" "<<constant_pool[i].c_long.low_bytes<<*/std::endl;
                break;
            case CONSTANT_Double:
                std::cout<<"#"<<constant_pool[i].index<<" = Double"
                <</*"\t"<<constant_pool[i].c_double.high_bytes<<" "<<constant_pool[i].c_double.low_bytes<<*/std::endl;
                break;
            case CONSTANT_NameAndType:
                std::cout<<"#"<<constant_pool[i].index<<" = NameAndType\t"
                "#"<<constant_pool[i].c_nameandtype.name_index
                <<" #"<<constant_pool[i].c_nameandtype.descriptor<<std::endl;
                break;
            case CONSTANT_Utf8:
                std::cout<<"#"<<constant_pool[i].index<<" = Utf8\t\t";
                std::cout << utf_to_str(constant_pool[i].c_utf8.bytes, constant_pool[i].c_utf8.length) <<std::endl;
                break;
            case CONSTANT_MethodHandle:
                std::cout<<"#"<<constant_pool[i].index<<" = MethodHandle\t\t"
                <<"#"<<constant_pool[i].c_methodhandle.reference_index<<std::endl;
                break;
            case CONSTANT_MethodType:
                std::cout<<"#"<<constant_pool[i].index<<" = MethodType\t\t"
                <<"#"<<constant_pool[i].c_methodtype.descriptor_index<<std::endl;
                break;
            case CONSTANT_InvokeDynamic:
                std::cout<<"#"<<constant_pool[i].index<<" = InvokeDynamic\t\t"
                "#"<<constant_pool[i].c_invokedynamic.bootstrap_method_attr_index
                <<" #"<<constant_pool[i].c_invokedynamic.name_and_type_index<<std::endl;
                break;
        }
    }
}

int Java_class::parse_method(u1 * method_handle, method_info * temp_method){
    int mp = 0;
    temp_method->access_flags = get_u2(method_handle + mp); mp += size_u2;
    temp_method->name_index = get_u2(method_handle + mp); mp += size_u2;
    temp_method->descriptor_index = get_u2(method_handle + mp); mp += size_u2;
    temp_method->attributes_count = get_u2(method_handle + mp); mp += size_u2;
    temp_method->attributes = new attribute[temp_method->attributes_count];
    for(int i = 0; i < temp_method->attributes_count; ++i){
        mp += parse_attribute(method_handle + mp, &temp_method->attributes[i]);
    }
    return mp;
}

void Java_class::print_methods(){
    for(int i = 0; i < methods_count; ++i){
        for(int j = 0; j < methods[i].attributes_count; ++j){
            // methods[i].attributes[j]
        }
    }
};

int Java_class::parse_attribute(u1 * attr_handle, attribute * temp_attr){
    int attr_cur = 0;

    u2 attr_name_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
    u4 attr_length = get_u4(&attr_handle[attr_cur]); attr_cur += size_u4;

    CONSTANT_Utf8_info attr_name_info = constant_pool[attr_name_index - 1].c_utf8;
    std::string attr_name = utf_to_str(attr_name_info.bytes, attr_name_info.length);
    std::cout << attr_name << std::endl;

    if (attr_name == "ConstantValue"){
        temp_attr->type = constant_value;
        u2 constval_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        temp_attr->constval_attr = {attr_name_index, attr_length, constval_index};
        //TODO: need variable to keep track of which union type is initialized
    }

    else if (attr_name == "Code"){
        temp_attr->type = code;
        u2 max_stack = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        u2 max_locals = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        u4 code_length = get_u4(&attr_handle[attr_cur]); attr_cur += size_u4;
        u1 * code = new u1[code_length];
        for(u4 i = 0; i < code_length; ++i){
                code[i] = get_u1(&attr_handle[attr_cur]); attr_cur += size_u1;
        }
        u2 exception_table_length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        exception *exception_table = new exception[exception_table_length];
        for(int i=0; i < exception_table_length; ++i){
            exception_table[i].start_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            exception_table[i].end_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            exception_table[i].handler_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            exception_table[i].catch_type = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        u2 attribute_count = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        attribute * attr = new attribute[attribute_count];
        if (attribute_count > 0){
            for(int i=0; i < attribute_count; ++i){
                attr_cur += parse_attribute(&attr_handle[attr_cur], &attr[i]);
            }
        }

        temp_attr->code_attr = {
            attr_name_index, attr_length, max_stack, max_locals, code_length, code,
            exception_table_length, exception_table, attribute_count, attr
        };
    }

    else if (attr_name == "StackMapTable"){
        temp_attr->type = stack_map;
        u2 number_of_entries = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        stack_map_frame * entries = new stack_map_frame[number_of_entries];
        for(int i=0; i < number_of_entries; ++i){
            // TODO:
        }
        temp_attr->stackmap_attr = {attr_name_index, attr_length, number_of_entries, entries};
    }

    else if (attr_name == "Exceptions"){
        temp_attr->type = except;
        u2 number_of_exceptions = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        u2 * exception_index_table = new u2[number_of_exceptions];
        for(int i=0; i < number_of_exceptions; ++i){
            exception_index_table[i] = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        temp_attr->except_attr = {attr_name_index, attr_length, number_of_exceptions, exception_index_table};
    }

    else if(attr_name == "InnerClasses"){
        temp_attr->type = inner_class;
        u2 number_of_classes = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        class_ *classes = new class_[number_of_classes];
        for(int i=0; i < number_of_classes; ++i){
            classes[i].inner_class_info_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            classes[i].outer_class_info_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            classes[i].inner_name_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            classes[i].inner_class_access_flags = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        temp_attr->inclass_attr = {attr_name_index, attr_length, number_of_classes, classes};
    }

    else if(attr_name == "EnclosingMethod"){
        temp_attr->type = enclosed_method;
        u2 class_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        u2 method_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        temp_attr->encmeth_attr = {attr_name_index, attr_length, class_index, method_index};
    }

    else if(attr_name == "Synthetic"){
        temp_attr->type = synthetic;
        temp_attr->synth_attr = {attr_name_index, attr_length};
    }

    else if(attr_name == "Signature"){
        temp_attr->type = signature;
        u2 signature_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        temp_attr->sign_attr = {attr_name_index, attr_length, signature_index};
    }

    else if(attr_name == "SourceFile"){
        temp_attr->type = source_file;
        u2 sourcefile_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        temp_attr->src_attr = {attr_name_index, attr_length, sourcefile_index};
    }

    else if(attr_name == "LineNumberTable"){
        temp_attr->type = line_num_table; //TODO: change name
        u2 line_number_table_length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        line_number_entry *line_number_table = new line_number_entry[line_number_table_length];
        for(int i=0; i < line_number_table_length; ++i){
            line_number_table[i].start_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            line_number_table[i].line_number = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        temp_attr->linenumtab_attr = {attr_name_index, attr_length, line_number_table_length, line_number_table};
    }

    else if(attr_name == "LocalVariableTable"){
        temp_attr->type = local_variable_table;
        u2 local_var_table_length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        local_var * local_var_table = new local_var[local_var_table_length];
        for(int i=0; i < local_var_table_length; ++i){
            local_var_table[i].start_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_table[i].length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_table[i].name_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_table[i].desc_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_table[i].index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        temp_attr->localvartab_attr = {attr_name_index, attr_length, local_var_table_length, local_var_table};
    }

    else if(attr_name == "LocalVariableTypeTable"){
        temp_attr->type = local_variable_type_table;
        u2 local_var_type_table_length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        local_var_type * local_var_type_table = new local_var_type[local_var_type_table_length];
        for(int i=0; i < local_var_type_table_length; ++i){
            local_var_type_table[i].start_pc = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_type_table[i].length = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_type_table[i].name_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_type_table[i].signature_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
            local_var_type_table[i].index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        }
        temp_attr->localvartype_attr = {attr_name_index, attr_length, local_var_type_table_length, local_var_type_table};
    }

    else if(attr_name == "Deprecated"){
        temp_attr->type = deprecated;
        temp_attr->depr_attr = {attr_name_index, attr_length};
    }

    else if(attr_name == "RuntimeVisibleAnnotations"){
        temp_attr->type = run_visible_annotations;
        u2 num_annotations = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        // TODO: annotation
        // temp_attr->runvisannot_attr = {attr_name_index, attr_length, num_annotations};
    }

    else if(attr_name == "RuntimeInvisibleAnnotations"){
        temp_attr->type = run_invisible_annotations;
        u2 num_annotations = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        // TODO: annotation
        // temp_attr->runinvannot_attr = {attr_name_index, attr_length, num_annotations};
    }
    return attr_cur;
}

Java_class::Java_class(Classfile_stream *classfile){
    _current = classfile->get_offset();
    magic = classfile->read_u4(); _current += size_u4;
    minor_version = classfile->read_u2(); _current += size_u2;
    major_version = classfile->read_u2(); _current += size_u2;
    
    // version verification: verify(min_ver, max_ver);
    
    constant_pool_count = classfile->read_u2(); _current += size_u2;
    if (constant_pool_count > 0){
        constant_pool = new cp_entry[constant_pool_count];
        for (int i = 1; i < constant_pool_count; ++i){
            _current += parse_cp_entry(classfile->get_current(), &constant_pool[i-1], i);
            classfile->set_offset(_current);
        }
    }

    access_flags = classfile->read_u2(); _current += size_u2;
    this_class = classfile->read_u2(); _current += size_u2;
    super_class = classfile->read_u2(); _current += size_u2;
    
    interfaces_count = classfile->read_u2(); _current += size_u2;
    if (interfaces_count > 0){
        interfaces = new u2[interfaces_count];
        for (int i = 0; i < interfaces_count; ++i){
            interfaces[i] = classfile->read_u2();
        }
        _current = classfile->get_offset();
    }

    fields_count = classfile->read_u2(); _current += size_u2;
    if (fields_count > 0){
        fields = new field_info[fields_count];
        for(int i = 0; i < fields_count; ++i){
            // _current += parse_field(field_handle, &fields[i]);
            // classfile->set_offset(_current);
        }
    }
    
    methods_count = classfile->read_u2(); _current += size_u2;
    if (methods_count > 0 ){
        methods = new method_info[methods_count];
        for(int i = 0; i < methods_count; ++i){
            // std::cout << "Method " << i << "\n";
            _current += parse_method(classfile->get_current(), &methods[i]);
            classfile->set_offset(_current);
        }
    }

    attribute_count = classfile->read_u2(); _current += size_u2;
    if (attribute_count > 0){
        attributes = new attribute[attribute_count];
        for (int i = 0; i < attribute_count; ++i){
            _current += parse_attribute(classfile->get_current(), &attributes[i]);
            classfile->set_offset(_current);
        }
    }

    path = classfile->path();
}