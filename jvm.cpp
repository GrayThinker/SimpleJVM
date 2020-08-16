#include "jvm.hpp"
#include "class_loader.hpp"
#include "class_file_stream.hpp"
#include "java_class_types.hpp"
#include "utils.hpp"

int main(int argc, char **argv){
    const char *classfile_path;
    if (argc != 2){
        classfile_path = ".\\test\\MyClass.class";
    } else { classfile_path = argv[1]; }

    Classfile_stream *code_stream = load_stream(classfile_path);
    printh(code_stream->get_u4());
}