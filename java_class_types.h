#pragma once

typedef unsigned char u1;   // one byte
typedef unsigned short u2;  // two bytes
typedef unsigned int u4;    // four bytes

int size_u1 = sizeof(u1);
int size_u2 = sizeof(u2);
int size_u4 = sizeof(u4);

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

#define get_u1(p) (u1)((p)[0])
#define get_u2(p) (u2)((u2)((p)[0]<<8) & 0xFF00 | (u2)((p)[1]) & 0x00FF)
#define get_u4(p) (u4)((u4)((p)[0]<<24) & 0xFF000000 | (u4)((p)[1]<<16) & 0x00FF0000 | (u4)((p)[2]<<8) & 0x0000FF00| (u4)((p)[3]) & 0x000000FF)
