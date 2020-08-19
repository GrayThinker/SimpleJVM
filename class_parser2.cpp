#include "java_class_types.hpp"
#include "class_structures.hpp"
#include "class_parser2.hpp"
#include "class_file_stream.hpp"
#include <iostream>

cp_info **Parseclass::parse_cp(u1 *cp_handle){
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
        // std::cout<<(int) constant_pool[idx]->tag<<" ";
        // std::cout<<cps_cur<<std::endl;
    }
    return constant_pool; //change name
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
            case CONSTANT_Methodref:{
                std::cout<<"#"<<i<<" = Methodref\t\t#"
                <<get_u2(&entry.info[0])<<" #"<<get_u2(&entry.info[2])<<std::endl;  //TODO: change to sizeof
            }break;
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

void Parseclass::parse(Classfile_stream *classfile){
    magic = classfile->getu4();
    minor_version = classfile->getu2();
    major_version = classfile->getu2();
    constant_pool_count = classfile->getu2();
    constant_pool = parse_cp(classfile->get_current());
}