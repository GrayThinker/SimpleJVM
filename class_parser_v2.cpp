#include "class_parser_v2.hpp"
#include "class_structures.hpp"
#include "class_types.hpp"
#include <iostream>
#include <string.h>

int Java_class::parse_cp_entry(u1 *cp_handle, cp_entry *cp, int index){  //TODO: error check, return BOOL
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
    std::cout<<"Parser 1"<<std::endl;
    for (int i = 0; i < constant_pool_count; ++i){
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
                for (int j = 0; j < constant_pool[i].c_utf8.length; ++j){
                    std::cout << constant_pool[i].c_utf8.bytes[j];
                }
                std::cout<<std::endl;
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

int Java_class::parse_attribute(u1 * attr_handle, attribute * temp_attr){
    int attr_cur = 0;
    u2 attr_name_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
    u4 attr_length = get_u4(&attr_handle[attr_cur]); attr_cur += size_u4;
    CONSTANT_Utf8_info attr_name_info = constant_pool[attr_name_index].c_utf8; // parse_utf8
    u1 * attr_name = new u1[attr_name_info.length];
    attr_name = attr_name_info.bytes;
    if (strcmp((const char *) attr_name, "ConstantValue") == 0){
        u2 constval_index = get_u2(&attr_handle[attr_cur]); attr_cur += size_u2;
        temp_attr->constval_attr = {attr_name_index, attr_length, constval_index};
        //TODO: need variable to keep track of which union type is initialized
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
    if (interfaces > 0){
        interfaces = new u2[interfaces_count];
        for (int i = 0; i < interfaces_count; ++i){
        // _current += parse_interface(interface_handle, &interfaces[i]);
        // classfile->set_offset(_current);
        }
    }

    fields_count = classfile->read_u2(); _current += size_u2;
    if (fields > 0){
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
        //     _current += parse_method(classfile->get_current(), &methods[i]);
        //     classfile->set_offset(_current);
        }
    }

    attribute_count = classfile->read_u2(); _current += size_u2;
    if (attribute_count > 0){
        attributes = new attribute[attribute_count];
        for (int i = 0; i < attribute_count; ++i){
        // _current += parse_attribute(attribute_handle, &attributes[i]);
        // classfile->set_offset(_current);
        }
    }

    path = classfile->path();
}