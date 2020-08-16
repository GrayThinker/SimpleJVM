#include "class_parser.hpp"

void parse_constant_pool_entries(u1 *cpool_ptr, u4 cpool_length){
    // TODO: include a java class instance and assigned parsed values to it. Might
    // be on the heap
    
    int ptr = 0;
    for(int i = 0; i < cpool_length; ++i){
        u1 tag = get_u1(&cpool_ptr[ptr]); ptr+= 4;
        switch(tag){
            case CONSTANT_Class:{

            }break;
            case CONSTANT_Fieldref:{

            }break;
            case CONSTANT_Methodref:{

            }break;
            case CONSTANT_InterfaceMethodref:{

            }break;
            case CONSTANT_String:{

            }break;
            case CONSTANT_Integer:{

            }break;
            case CONSTANT_Float:{

            }break;
            case CONSTANT_Long:{

            }break;
            case CONSTANT_Double:{

            }break;
            case CONSTANT_NameAndType:{

            }break;
            case CONSTANT_Utf8:{

            }break;
            case CONSTANT_MethodHandle:{

            }break;
            case CONSTANT_MethodType:{

            }break;
            case CONSTANT_InvokeDynamic:{

            }break;
            
        }
    }
};