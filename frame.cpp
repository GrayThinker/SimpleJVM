#include "frame.hpp"
#include "stack.hpp"
#include "class_types.hpp"

Frame::Frame(method_info* method, Parseclass *parent_class){
    _mp = 0;
    _method = method;
    _parent_class = parent_class;
    _parse_code(_method->attributes, _code);
    _operand_stack = new Stack(_code->max_stack);
    _locals = new u4(_code->max_locals);
    code = _code;
    stack = _operand_stack;
    locals = _locals;
}

Frame::~Frame(){
    if (_locals){
        delete _locals;
    }
    if (_operand_stack){
        delete _operand_stack;
    }
}

Stack* Frame::get_opstack(){
    return _operand_stack;
}

u4* Frame::get_locals(){
    return _locals;
}

void Frame::_parse_code(attribute_info* code_attr, code_attribute *code){
    //FIXME: make this into an operator cast from attr info to code attr

    //check if code att:
    //tag = _parent_class->constant_pool[_method->attributes->attribute_name_index]->tag == CONSTANT_Utf8_info
    //if utf_to_char(tag) == "code" proceed;
    int cp = 0;
    u1* head = code_attr->info;
    code->attribute_name_index = code_attr->attribute_name_index;
    code->attribute_length = code_attr->attribute_length;
    code->max_stack = get_u2(head + cp); cp += size_u2;
    code->code_length = get_u4(head + cp); cp += size_u4;
    code->code = new u1[code->code_length]; cp += code->code_length;
    code->exception_table_length = get_u2(head + cp); cp += size_u2;
    code->exception_table->start_pc = get_u2(head + cp); cp += size_u2;
    code->exception_table->end_pc = get_u2(head + cp); cp += size_u2;
    code->exception_table->handler_pc = get_u2(head + cp); cp += size_u2;
    code->exception_table->catch_type = get_u2(head + cp); cp += size_u2;
    code->attributes_count = get_u2(head +cp); cp += size_u2;
    code->attributes = new attribute_info[code->attributes_count];
    // code->attributes = dynamic_cast<attribute_info*>(head + cp);  // cast needed
}