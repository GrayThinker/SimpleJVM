#include "class_parser.hpp"
#include "class_structures.hpp"
// #include "java_class.hpp"
#include <iostream>

cp_entry * Java_class::parse_constant_pool_entries(u1 *cp_handle, u2 cp_length){  //TODO: error check, return BOOL
    cp_entry *cp= new cp_entry[cp_length];
    int cp_cur = 0;

    for(int index = 1; index < cp_length; ++index){  // constant pool index starts from 1
        u1 tag = get_u1(&cp_handle[cp_cur]); cp_cur+= 1;
        cp_entry temp;  // create temporary constant pool entry
        temp.index = index;  // set its index and tag(for union) to the current index and tag
        temp.tag = tag;
        //TODO: trace bool to print out entries during parse
        switch(tag){
            case CONSTANT_Class:{
                u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2; //TODO: change to definition of sizeof
                temp.c_class = CONSTANT_Class_info{
                    tag, name_index
                };  // initialize cp_entry
                cp[index - 1] = temp;  // assign current to cp at [index - 1]. Index starts from 1
            }break;

            case CONSTANT_Fieldref:
            case CONSTANT_Methodref:
            case CONSTANT_InterfaceMethodref:{
                u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                u2 name_and_type = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                switch(tag){  //TODO: find out if fall through is better and switch vs if
                    case CONSTANT_Fieldref:
                        temp.c_fieldref = CONSTANT_Fieldref_info{ tag, class_index, name_and_type };
                        break;
                    case CONSTANT_Methodref:
                        temp.c_methodref = CONSTANT_Methodref_info{ tag, class_index, name_and_type };
                        break;
                    case CONSTANT_InterfaceMethodref:
                        temp.c_interfacemethodref = CONSTANT_InterfaceMethodref_info{ tag, class_index, name_and_type };
                        break;
                }
                cp[index - 1] = temp;
            }break;

            case CONSTANT_String:{
                u2 string_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                temp.c_string = CONSTANT_String_info{
                    tag, string_index
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Integer:
            case CONSTANT_Float:{
                u4 bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
                if (tag == CONSTANT_Integer){  //TODO: TEST: switch vs if
                    temp.c_integer = CONSTANT_Integer_info{ tag, bytes };
                } else {
                    temp.c_float = CONSTANT_Float_info{ tag, bytes };
                }
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Long:
            case CONSTANT_Double:{
                u4 high_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
                u4 low_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += size_u4;
                if (tag == CONSTANT_Long){
                    temp.c_long = CONSTANT_Long_info{ tag, high_bytes, low_bytes};
                } else {
                    temp.c_double = CONSTANT_Double_info{ tag, high_bytes, low_bytes };
                }
                cp[index - 1] = temp;
                ++index; // long and double take two entries
            }break;

            case CONSTANT_NameAndType:{
                u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                u2 descriptor = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                temp.c_nameandtype = CONSTANT_NameAndType_info{
                    tag, name_index, descriptor
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Utf8:{
                u2 length = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                u1 *bytes = new u1[length];
                for (int ii = 0; ii < length; ++ii){
                    bytes[ii] = get_u1(&cp_handle[(cp_cur++) + ii]);
                }
                temp.c_utf8 = CONSTANT_Utf8_info{
                    tag, length, bytes
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_MethodHandle:{
                u1 reference_kind = get_u1(&cp_handle[cp_cur]); cp_cur += size_u1;
                u2 reference_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                temp.c_methodhandle = CONSTANT_MethodHandle_info{ tag, reference_kind, reference_index };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_MethodType:{
                u2 descriptor_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                temp.c_methodtype = CONSTANT_MethodType_info{ tag, descriptor_index };
                cp[index - 1] = temp;                
            }break;
            
            case CONSTANT_InvokeDynamic:{
                u2 bootstrap_method_attr_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                u2 name_and_type_index = get_u2(&cp_handle[cp_cur]); cp_cur += size_u2;
                temp.c_invokedynamic = CONSTANT_InvokeDynamic_info{
                    tag, bootstrap_method_attr_index, name_and_type_index
                };
                cp[index - 1] = temp;
            }break;
            
        }  //switch(tag)
    }  //for loop
    return cp;  //FIXME: returning local
}

void Java_class::print_cp(){  //FIXME: DRY
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
            std::cout<<"#"<<constant_pool[i].index<<" = Utf8\t";
            // TODO: UTF8 conversion
            // for (int i = 0; i < constant_pool[i].c_utf8.length; ++i)
            //     std::cout<<constant_pool[i].c_utf8.bytes[i];
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

void Java_class::parse_class(Classfile_stream *classfile){
    magic = classfile->getu4();
    minor_version = classfile->getu2();
    major_version = classfile->getu2();
    constant_pool_count = classfile->getu2();
    constant_pool = parse_constant_pool_entries(classfile->get_current(), constant_pool_count);
    access_flags = classfile->getu2();
    this_class = classfile->getu2();
    super_class = classfile->getu2();
    interfaces_count = classfile->getu2();
    // interfaces = parse_interfaces();
    // ...
}