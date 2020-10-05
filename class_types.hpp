#pragma once

typedef unsigned char u1;   // one byte
typedef unsigned short u2;  // two bytes
typedef unsigned int u4;    // four bytes

// const char * a_CONSTANTVALUE = "ConstantValue";
// const char * a_CODE = "Code";


#define size_u1 1
#define size_u2 2
#define size_u4 4

// Constant pool tags
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

// Field access and property flags
#define FIELD_ACC_PUBLIC 0x0001
#define FIELD_ACC_PRIVATE 0x0002
#define FIELD_ACC_PROTECTED 0x0004
#define FIELD_ACC_STATIC 0x0008
#define FIELD_ACC_FINAL 0x0010
#define FIELD_ACC_VOLATILE 0x0040
#define FIELD_ACC_TRANSIENT 0x0080
#define FIELD_ACC_SYNTHETIC 0x1000
#define FIELD_ACC_ENUM 0x4000

// Method access and property flags
#define METHOD_ACC_PUBLIC 0x0001
#define METHOD_ACC_PRIVATE 0x0002
#define METHOD_ACC_PROTECTED 0x004
#define METHOD_ACC_STATIC 0x0008
#define METHOD_ACC_FINAL 0x0010
#define METHOD_ACC_SYNCHRONIZED 0x0020
#define METHOD_ACC_BRIDGE 0x0040
#define METHOD_ACC_VARARGS 0x0080
#define METHOD_ACC_NATIVE 0x0100
#define METHOD_ACC_ABSTRACT 0x0400
#define METHOD_ACC_STRICT 0x0800
#define METHOD_ACC_SYNTHETIC 0x1000

// Item verification types
#define ITEM_Top 0
#define ITEM_Integer 1
#define ITEM_Float 2
#define ITEM_Double 3
#define ITEM_Long 4
#define ITEM_Null 5
#define ITEM_UninitializedThis 6
#define ITEM_Object 7
#define ITEM_Uninitialized 8

#define ACC_CHECK 0xcafe

#define positive_inf 0x7f800000
#define negative_inf 0xff800000

#define get_u1(p) (u1)((p)[0])
#define get_u2(p) (u2)((u2)((p)[0]<<8) & 0xFF00 | (u2)((p)[1]) & 0x00FF)
#define get_u4(p) (u4)((u4)((p)[0]<<24) & 0xFF000000 | (u4)((p)[1]<<16) & 0x00FF0000 | (u4)((p)[2]<<8) & 0x0000FF00| (u4)((p)[3]) & 0x000000FF)