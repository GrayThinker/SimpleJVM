#include "java_class.h"
#include "class_loader.h"

int main(int argc, char **argv){
    const char *classfile_path;
    if (argc != 2){
        classfile_path = "C:\\Users\\jshat\\Documents\\Code\\MyClass.class";
    } else { classfile_path = argv[1]; }

    int classfile_size = get_classfile_size(classfile_path);

    int code_ptr = 0;
    char *code_stream =  new char[classfile_size];
    open_classfile(classfile_path, classfile_size, code_stream);
}
