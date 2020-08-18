#include "class_parser.hpp"
#include "class_structures.hpp"

u1* parse_overhead(Classfile_stream *classfile){  //right now just a get constant pool pointer function
    u4 magic = classfile->getu4();
    u2 minor_version = classfile->getu2();
    u2 major_version = classfile->getu2();
    return classfile->get_current();
}

u2 get_cp_length(Classfile_stream *classfile){
    return classfile->getu2();
}

cp_entry * parse_constant_pool_entries(u1 *cp_handle, u2 cp_length){  //TODO: error check, return BOOL
    cp_entry *cp= new cp_entry[cp_length];  //bare constant pool TODO: start from 1
    int cp_cur = 0;

    for(int index = 1; index < cp_length; ++index){  // constant pool index starts from 1
        u1 tag = get_u1(&cp_handle[cp_cur]); cp_cur+= 1;  //TODO: TEST: Check tag doesn't change with subsequent get_uX calls
        //TODO: trace bool to print out entries during parse
        switch(tag){
            case CONSTANT_Class:{
                u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2; //TODO: change to definition of sizeof
                cp_entry temp;  // declare cp_entry
                temp.index = index;  // assign cp index to current index
                temp.tag = tag;
                temp.c_class = CONSTANT_Class_info{
                    tag, name_index
                };  // initialize cp_entry
                cp[index - 1] = temp;  // assign current to cp at [index - 1]
            }break;

            case CONSTANT_Fieldref:{ // FIXME: can fall through to _InterfaceM
                u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                u2 name_and_type_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_fieldref = CONSTANT_Fieldref_info{
                    tag, class_index, name_and_type_index
                };
                cp[index - 1] = temp;
            }break;
            
            case CONSTANT_Methodref:{  // FIXME: can fall through to _InterfaceM
                u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                u2 name_and_type_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_methodref = CONSTANT_Methodref_info{
                    tag, class_index, name_and_type_index
                }; 
                cp[index - 1] = temp;
            }break;

            case CONSTANT_InterfaceMethodref:{
                u2 class_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                u2 name_and_type = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_interfacemethodref = CONSTANT_InterfaceMethodref_info{
                    tag, class_index, name_and_type
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_String:{
                u2 string_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_string = CONSTANT_String_info{
                    tag, string_index
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Integer:{  //FIXME: can fall through to _Float
                u4 bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_integer = CONSTANT_Integer_info{
                    tag, bytes
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Float:{
                u4 bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_float = CONSTANT_Float_info{
                    tag, get_u4(&cp_handle[cp_cur])
                }; cp_cur += 4;  //TODO: change to definition of sizeof
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Long:{  //FIXME: can fall through to _Double
                u4 high_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof
                u4 low_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_long = CONSTANT_Long_info{
                    tag, high_bytes, low_bytes
                };
                cp[index - 1] = temp;
            }break;
            
            case CONSTANT_Double:{
                u4 high_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof
                u4 low_bytes = get_u4(&cp_handle[cp_cur]); cp_cur += 4;  //TODO: change to definition of sizeof                
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_double = CONSTANT_Double_info{
                    tag, high_bytes, low_bytes
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_NameAndType:{
                u2 name_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                u2 descriptor = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_nameandtype = CONSTANT_NameAndType_info{
                    tag, name_index, descriptor
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_Utf8:{
                u2 length = get_u2(&cp_handle[cp_cur]); cp_cur += 2;  //TODO: change to definition of sizeof
                u1 *bytes = new u1[length];  //TODO: change to definition of sizeof
                for (int ii = 0; ii < length; ++ii){
                    bytes[ii] = get_u1(&cp_handle[(cp_cur++) + ii]);
                }
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_utf8 = CONSTANT_Utf8_info{
                    tag, length, bytes
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_MethodHandle:{
                u1 reference_kind = get_u1(&cp_handle[cp_cur]); cp_cur += 1;
                u2 reference_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_methodhandle = CONSTANT_MethodHandle_info{
                    tag, reference_kind, reference_index
                };
                cp[index - 1] = temp;
            }break;

            case CONSTANT_MethodType:{
                u2 descriptor_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_methodtype = CONSTANT_MethodType_info{
                    tag, descriptor_index
                };
                cp[index - 1] = temp;                
            }break;
            
            case CONSTANT_InvokeDynamic:{
                u2 bootstrap_method_attr_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;
                u2 name_and_type_index = get_u2(&cp_handle[cp_cur]); cp_cur += 2;
                cp_entry temp;
                temp.index = index;
                temp.tag = tag;
                temp.c_invokedynamic = CONSTANT_InvokeDynamic_info{
                    tag, bootstrap_method_attr_index, name_and_type_index
                };
                cp[index - 1] = temp;
            }break;
            
        }  //switch(tag)
    }  //for loop
    return cp;  //FIXME: returning local
}

void print_cp(cp_entry * cp){  //FIXME: DRY
    switch(cp->tag){
        case CONSTANT_Class:  //{?
            std::cout<<"#"<<cp->index<<" = "<< cp->tag  //TODO: switch to cp->c_x.tag
            <<"\t#"<<cp->c_class.name_index << std::endl;
            break;
        
        case CONSTANT_Fieldref:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_fieldref.class_index
            <<" #"<<cp->c_fieldref.name_and_type_index<<std::endl;
            break;

        case CONSTANT_Methodref:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_methodref.class_index
            <<" #"<<cp->c_methodref.name_and_type_index<<std::endl;
            break;

        case CONSTANT_InterfaceMethodref:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_interfacemethodref.class_index
            <<" #"<<cp->c_interfacemethodref.name_and_type_index<<std::endl;
            break;

        case CONSTANT_String:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_string.string_index<<std::endl;
            break;
        
        case CONSTANT_Integer:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t"<<cp->c_integer.bytes<<std::endl;
            break;

        case CONSTANT_Float:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t"<<cp->c_float.bytes<<std::endl;
            break;

        case CONSTANT_Long:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t"<<cp->c_long.high_bytes<<" "<<cp->c_long.low_bytes<<std::endl;
            break;

        case CONSTANT_Double:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t"<<cp->c_double.high_bytes<<" "<<cp->c_double.low_bytes<<std::endl;
            break;

        case CONSTANT_NameAndType:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_nameandtype.name_index<<" #"
            <<cp->c_nameandtype.descriptor<<std::endl;
            break;
        
        case CONSTANT_Utf8:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag<<"\t";
            for (int i = 0; i < cp->c_utf8.length; ++i)
                std::cout<<cp->c_utf8.bytes[i];
            std::cout<<std::endl;
            break;

        case CONSTANT_MethodHandle:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_methodhandle.reference_index<<std::endl;
            break;

        case CONSTANT_MethodType:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_methodtype.descriptor_index<<std::endl;
            break;
        
        case CONSTANT_InvokeDynamic:
            std::cout<<"#"<<cp->index<<" = "<<cp->tag
            <<"\t#"<<cp->c_invokedynamic.bootstrap_method_attr_index
            <<" #"<<cp->c_invokedynamic.name_and_type_index<<std::endl;
            break;
    }
}
