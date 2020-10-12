#include "class_file_stream.hpp"
#include "execution_engine.hpp"
#include "class_types.hpp"
#include "class_parser.hpp"
#include "class_parser_v2.hpp"
#include "utils.hpp"
#include "frame.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// flag for debugging mode

void print_info(){
    int major_v = 0;
    int minor_v = 0;

    std::cout << "SimpleJVM" << std::endl;
    std::cout << "A simple implementation of the Java Virtual Machine specification" << std::endl;
    std::cout << "Developer: Joseph Shatti" << std::endl;
    std::cout << "Versions: " << major_v << "." << minor_v << std::endl << std::endl;
}

int main(int argc, char **argv){
    std::vector<std::string> args;
    const char *classfile_path;

    for (int i=1; i < argc; ++i){
        args.push_back(argv[i]);
    }

    if (args.size() < 1){ // no flags
        classfile_path = ".\\test\\test2.class";
    } 
    else if (args.size() == 1){
        classfile_path = args.back().c_str();
    } 
    else {
        for (auto i = args.begin(); i != args.end() - 1; ++i){
            switch (i->c_str()[1]){
                case 'i':{
                    print_info();
                } break;
                
                default:{
                    std::cerr << "Invalid flag\n";
                    return 0;
                }
            }
        }
        classfile_path = args.back().c_str();
    }

    std::cout << "Running...\n";
    std::shared_ptr<Classfile_stream> code_stream(new Classfile_stream(classfile_path));
    std::shared_ptr<Java_class> jclass(new Java_class(code_stream.get()));
    // jclass.get()->print_cp();
    
    // std::shared_ptr<Parseclass> p_class(new Parseclass(code_stream.get()));

    // std::cout << "COMPLETED" << std::endl;
    // Frame f = Frame(&p_class->methods[0], p_class.get());
    // execute(&f);

    // p_class->print_cp();
    
    return 0;
}