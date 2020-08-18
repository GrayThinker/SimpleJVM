#include "class_loader.hpp"
#include "class_file_stream.hpp"
#include "java_class_types.hpp"
#include "class_parser.hpp"
#include "utils.hpp"
#include <iostream>

void print_info(){
    int major_v = 0;
    int minor_v = 0;

    std::cout << "SimpleJVM" << std::endl;
    std::cout << "A simple implementation of the Java Virtual Machine specification" << std::endl;
    std::cout << "Developer: Joseph Shatti" << std::endl;
    std::cout << "Versions: " << major_v << "." << minor_v << std::endl << std::endl;
}

int main(int argc, char **argv){
    //TODO: timing
    const char *classfile_path;
    if (argc < 2){
        classfile_path = ".\\test\\MyClass.class";
    } else { classfile_path = argv[1]; }
    // TODO: flags parsing for print_info()

    Classfile_stream *code_stream = load_stream(classfile_path);
    parse_overhead(code_stream);
    int cp_length = get_cp_length(code_stream);
    std::cout << cp_length <<std::endl;
    cp_entry *cp = parse_constant_pool_entries(code_stream->get_current(), cp_length);
    
    for(int i = 1; i < cp_length; ++i)
        print_cp(cp++);
    
}