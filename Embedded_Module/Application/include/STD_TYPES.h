#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;
typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef signed long long int s64;

typedef enum
{
    false = 0,
    true,
    
} bool;

#define NULL_PTR    ((void *)0)
#define NULL	    ((void *)0U)


#endif //STD_TYPES_H_
