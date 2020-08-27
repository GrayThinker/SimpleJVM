#include "class_loader.hpp"
#include "class_file_stream.hpp"
#include "class_types.hpp"
#include "class_parser.hpp"
#include "class_parser2.hpp"
#include "utils.hpp"
#include <iostream>
// #include "java_class.hpp"

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

    Parseclass *p_class = new Parseclass;
    p_class->parse(code_stream);

    // code_stream = load_stream(classfile_path);
    // Java_class *j_class;
    // j_class->parse_class(code_stream);
    // j_class->print_cp();
    
}