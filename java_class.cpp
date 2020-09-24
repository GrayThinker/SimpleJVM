#include "java_class.hpp"
#include "class_parser.hpp"

/* Java class structure
Java_class::Java_class(){
    u4 magic
    u2 minor
    u2 major
    u2 constant pool count

    constant pool{
        arr of size cp count
        can be either {
            attr info -> *(attr tag), name index, attr length, info{

            }

            field info -> access flags, name index, ls of pointers to attrs, each pointer
            starts at *(attr tag)

            method info ->
        }
    }

    u2 access flags
    u2 this class
    u2 super class
    u2 interfaces count

    interfaces{

    }

    u2 fields count

    fields{
        
    }

    u2 methods count

    methods{

    }

    u2 attributes counts

    attr{

    }
}
*/


Java_class::Java_class(){
    
};