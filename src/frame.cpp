#include "frame.hpp"
#include "stack.hpp"
#include "class_types.hpp"
#include "class_parser.hpp"

Frame::Frame(method_info* method, Java_class *parent_class){
    // maybe add runtime reference, should parent class be there?
    _method = method;
    _parent_class = parent_class;
    _op_stack = new Stack(100);
    
//     _parse_code(_method->attributes, _code);
//     _operand_stack = new Stack(_code->max_stack);
//     _locals = new u4(_code->max_locals);
//     code = _code;
//     stack = _operand_stack;
//     locals = _locals;
// }
}
// Frame::~Frame(){
//     if (_locals){
//         delete _locals;
//     }
//     if (_operand_stack){
//         delete _operand_stack;
//     }
// }