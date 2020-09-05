#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_parser.hpp"
#include "class_file_stream.hpp"
#include <iostream>

void Parseclass::parse_cp(u1 *cp_handle){
    int cps_cur = 0;
    cp_info **constant_pool = new cp_info*[constant_pool_count];
    
    for(int idx = 1; idx < constant_pool_count; ++idx){
        u1 tag = get_u1(&cp_handle[cps_cur]); cps_cur+=1;
        switch (tag){
            // size: 2
            case CONSTANT_Class:
            case CONSTANT_String:
            case CONSTANT_MethodType:{
                constant_pool[idx] = new cp_info {tag, &cp_handle[cps_cur]};
                cps_cur += 2;
            } break;

            // size: 3
            case CONSTANT_MethodHandle:{
                constant_pool[idx] = new cp_info {tag, &cp_handle[cps_cur]};
                cps_cur += 3;
            } break;
            
            // size: 4
            case CONSTANT_Fieldref:
            case CONSTANT_Methodref:
            case CONSTANT_InterfaceMethodref:
            case CONSTANT_Integer:
            case CONSTANT_Float:
            case CONSTANT_NameAndType:
            case CONSTANT_InvokeDynamic:{
                constant_pool[idx] = new cp_info {tag, &cp_handle[cps_cur]};
                cps_cur += 4;
            }break;
            
            // size: 8
            case CONSTANT_Long:
            case CONSTANT_Double:
                constant_pool[idx++] = new cp_info {tag, &cp_handle[cps_cur]};
                cps_cur += 8;
            break;

            case CONSTANT_Utf8:
                constant_pool[idx] = new cp_info {tag, &cp_handle[cps_cur]};
                u2 length = get_u2(&cp_handle[cps_cur]); cps_cur += 2;
                cps_cur += (int) length;

            break;


        }
    }
    _current += cps_cur;
    Parseclass::constant_pool = constant_pool; //change name
    // change to return true or false
}

void Parseclass::print_cp(){
    for (int i = 1; i < constant_pool_count; ++i){
        cp_info entry = *constant_pool[i];
        u1 tag = entry.tag;
        switch(tag){  // change to assign to string then cout at end
            case CONSTANT_Class:
                std::cout<<"#"<<i<<" = Class\t\t#"<<get_u2(&entry.info[0])<<std::endl;
                break;
            case CONSTANT_String:
                std::cout<<"#"<<i<<" = String\t\t#"<<get_u2(&entry.info[0])<<std::endl;
                break;
            case CONSTANT_MethodType:
                std::cout<<"#"<<i<<" = MethodType\t\t#"<<get_u2(&entry.info[0])<<std::endl;
                break;

            //u2 u2
            case CONSTANT_Fieldref:
                std::cout<<"#"<<i<<" = Fieldref\t\t#"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;
                break;
            case CONSTANT_Methodref:
                std::cout<<"#"<<i<<" = Methodref\t\t#"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;  //TODO: change to sizeof
            break;
            case CONSTANT_InterfaceMethodref:
                std::cout<<"#"<<i<<" = InterfaceMethodref\t"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;
                break;
            case CONSTANT_NameAndType:
                std::cout<<"#"<<i<<" = NameAndType\t#"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;
                break;
            case CONSTANT_InvokeDynamic:
                std::cout<<"#"<<i<<"= InvokeDynamic\t"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;
                break;
            
            // other
            case CONSTANT_Integer:
                std::cout<<"#"<<i<<" = Integer\t\t"<<std::endl;
                break;
            case CONSTANT_Float:
                std::cout<<"#"<<i<<" = Float\t\t"<<std::endl;
                break;
            case CONSTANT_Long:
                std::cout<<"#"<<i++<<" = Long\t\t"<<std::endl;
                break;
            case CONSTANT_Double:
                std::cout<<"#"<<i++<<" = Double\t\t"<<std::endl;
                break;
            case CONSTANT_MethodHandle:
                std::cout<<"#"<<i<<" = MethodHandle\t\t"<<std::endl;
                break;
            case CONSTANT_Utf8:
                std::cout<<"#"<<i<<" = Utf8\t\t"<<std::endl;
                break;
        }
    }
}

int Parseclass::parse_fields(u1 *field_handle, field_info * field){
    int fp = 0;
    field_info * temp_fields = new field_info[fields_count];
    field->access_flags = get_u2(field_handle + fp); fp += size_u2;
    field->name_index = get_u2(field_handle + fp); fp += size_u2;
    field->attributes_count = get_u2(field_handle + fp); fp += size_u2;
    field->attributes = new attribute_info[field->attributes_count];

    for (int attr = 0; attr < field->attributes_count; ++attr){
        fp += parse_attributes(field_handle + fp, field->attributes + attr);
    }
    return fp;
}

int Parseclass::parse_methods(u1 *method_handle, method_info* method){
    int mp = 0;
    method->access_flags = get_u2(method_handle + mp); mp += size_u2;
    method->name_index = get_u2(method_handle + mp); mp += size_u2;
    method->descriptor_index = get_u2(method_handle + mp); mp += size_u2;
    method->attributes_count = get_u2(method_handle + mp); mp += size_u2;
    method->attributes = new attribute_info[method->attributes_count];

    for (int attr = 0; attr < method->attributes_count; ++attr){
        mp += parse_attributes(method_handle + mp, method->attributes + attr);
    }
    return mp;
}

int Parseclass::parse_attributes(u1 *attribute_handle, attribute_info* attribute){
    int ap = 0;
    attribute->attribute_name_index = get_u2(attribute_handle + ap); ap += size_u2;      
    attribute->attribute_length = get_u4(attribute_handle + ap); ap += size_u4;
    attribute->info = new u1[attribute->attribute_length];
    attribute->info = attribute_handle + ap; ap += attribute->attribute_length;
    return ap;
}

Parseclass::Parseclass(Classfile_stream *classfile){
    _current = classfile->get_offset();
    
    // magic check
    magic = classfile->getu4(); _current += size_u4;
    
    // version check -> pass to version checker function
    minor_version = classfile->getu2(); _current += size_u2;
    major_version = classfile->getu2(); _current += size_u2;
    
    constant_pool_count = classfile->getu2(); _current += size_u2;
    if (constant_pool_count > 0){
        parse_cp(classfile->get_current());
        classfile->set_offset(_current);
    }

    access_flags = classfile->getu2(); _current += size_u2;
    this_class = classfile->getu2(); _current += size_u2;
    super_class = classfile->getu2(); _current += size_u2; 
    interfaces_count = classfile->getu2(); _current += size_u2;

    if (interfaces_count > 0){ //maybe give it its own function
        interfaces = new u2[interfaces_count];
        for (int i = 0; i < interfaces_count; ++i){
            interfaces[i] = classfile->getu2(); _current += size_u2;
        }
    }

    fields_count = classfile->getu2(); _current += size_u2;
    fields = new field_info[fields_count];
    for (int f; f < fields_count; ++f){
        _current += parse_fields(classfile->get_current(), fields + f);
        classfile->set_offset(_current);
    }
    
    methods_count = classfile->getu2(); _current += size_u2;
    methods = new method_info[methods_count];
    for (int mthd = 0; mthd < methods_count; ++mthd){
        _current += parse_methods(classfile->get_current(), methods + mthd);
        classfile->set_offset(_current);
    }
    
    attributes_count = classfile->getu2(); _current += size_u2;
    attributes = new attribute_info[attributes_count];
    for (int attr = 0; attr < attributes_count; ++attr){
        _current += parse_attributes(classfile->get_current(), attributes + attr);
        classfile->set_offset(_current);
    }
}

Parseclass::~Parseclass(){
    ;
}