#include "utils.hpp"
#include "frame.hpp"
#include "stack.hpp"
#include "opcodes.hpp"
#include "class_types.hpp"
#include "class_parser.hpp"
#include "class_structures.hpp"

// int execute(Frame* frame){
//     // u1 * code; // get from frame
//     // unsigned int pc = 0; // get from frame
//     // Stack * stack; // TODO: change to operand stack
//     // // locals

//     while(true){
//         switch((int) frame->code){
//             case aaload:{
//                 // int index = frame->stack->pop();
//                 // int* array_ref = std::hex << frame->stack->pop(); // should be type reference
//                 // frame->stack->push(array_ref[index]);
//             } break;
//             case aastore:{
//                 // reference value = stack.pop();
//                 // int index = stack.pop();
//                 // reference array_ref = stack.pop();
//                 // array_ref[index] = value;
//             } break;
//             case aconst_null:{
//                 // stack.push(null);
//             } break;
//             case aload:{
//                 // int index = get_u1(code[pc++]);
//                 // stack.push(locals[index]);
//             } break;
//             case aload_0:
//                 // stack.push(locals[0]);
//                 break;
//             case aload_1:
//                 // stack.push(locals[1]);
//                 break;
//             case aload_2:
//                 // stack.push(locals[0]);
//                 break;
//             case aload_3:
//                 // stack.push(locals[0]);
//                 break;
//             case anewrarray:{
//                 // indexbyte1 = get_u1(code[pc++]);
//                 // indexbyte2 = get_u1(code[pc++]);
//                 // int count = stack.pop();
//                 // cp_index = (indexbyte1 << 8) | indexbyte2;
//                 // reference array_ref = heap_alloc array of constant_pool[cp_index] and size count, all components are null
//                 // stack.push(array_ref);
//             } break;
//             case areturn:{
//                 // objectref = stack.pop() must be a reference of type described by method return type
//                 // end current method and return objectref to stack of invoking method
//                 // return objectref;
//             }
//             case arraylength:{
//                 // reference array_ref = stack.pop();
//                 // stack.push(len(array_ref));
//             } break;
//             case astore:{
//                 // u1 index = get_u1(code[pc++]);
//                 // reference objref = stack.pop();
//                 // locals[index] = objref;
//             } break;
//             case astore_0:{
//                 // locals[0] = stack.pop()
//             } break;
//             case astore_1:{
//                 // locals[1] = stack.pop()
//             } break;
//             case astore_2:{
//                 // locals[2] = stack.pop()
//             } break;
//             case astore_3:{
//                 // locals[3] = stack.pop()
//             } break;
//             case athrow:{
//                 // Throwable objref = stack.pop()
//                 // search current method for first exception handler that matches the class of objref
//                 // if handler is found start execute that handler pc = that. clear op stack and stack.push(objref);
//                 // if not found exit frame and throw again. if no invoked frame close thread
//             } break;
//             case baload:{
//                 // int index = stack.pop();
//                 // arrayref = stack.pop();
//                 // if arrayref == null throw  NullPointerException
//                 // if index not in arrayref throw ArrayIndexOutOfBoundsException
//                 // stack.push(arrayref[index] => sign extend to int val);
//             } break;
//             case bastore:{
//                 //int value = stack.pop();
//                 //int index = stack.pop();
//                 // reference arrayref = stack.pop(); array of bools
//                 // arrayref[index] =  to_byte(value)
//             } break;
//             case bipush:{
//                 // byte = get_u1(code[ptr++]);
//                 // byte is sign extended to int value
//                 // stack.push(byte)
//             } break;
//             case caload:{
//                 // int index = stack.pop()
//                 // arrayref = stack.pop()
//                 // if arrayref == null throw NullPointerException
//                 // if index out of bound through ArrayIndexOutOfBoundsException
//                 // stack.push(arrayref[index] -> zero extended to int)
//             } break;
//             case castore:{
//                 // value = stack.pop()
//                 // index = stack.pop()
//                 // arrayref = stack.pop()
//                 // arrayref[index] = value;
//             } break;

//         }

//     }
//     return 1;
// }
