#include "class_file_stream.hpp"
#include "execution_engine.hpp"
#include "class_types.hpp"
#include "class_parser.hpp"
#include "utils.hpp"
#include "frame.hpp"
#include <iostream>
#include <memory>
#include <string.h>

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
        classfile_path = ".\\test\\test2.class";
    }
    // if (strcmp(argv[1], "-i") == 0){
    //     print_info();
    //     return 0;
    // } else { classfile_path = argv[1]; }

    std::shared_ptr<Classfile_stream> code_stream(new Classfile_stream(classfile_path));
    std::shared_ptr<Parseclass> p_class(new Parseclass(code_stream.get()));
    Frame f = Frame(&p_class->methods[0], p_class.get());
    execute(&f);

    // p_class->print_cp();
    
    return 0;
}