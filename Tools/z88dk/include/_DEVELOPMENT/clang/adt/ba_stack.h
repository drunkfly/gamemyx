
// automatically generated by m4 from headers in proto subdir


#ifndef __ADT_BA_STACK_H__
#define __ADT_BA_STACK_H__

#include <stddef.h>

// DATA STRUCTURES

typedef struct ba_stack_s
{

   void       *data;
   size_t      size;
   size_t      capacity;

} ba_stack_t;

extern size_t ba_stack_capacity(ba_stack_t *s);


extern void ba_stack_clear(ba_stack_t *s);


extern void ba_stack_destroy(ba_stack_t *s);


extern int ba_stack_empty(ba_stack_t *s);


extern ba_stack_t *ba_stack_init(void *p,void *data,size_t capacity);


extern int ba_stack_pop(ba_stack_t *s);


extern int ba_stack_push(ba_stack_t *s,int c);


extern size_t ba_stack_size(ba_stack_t *s);


extern int ba_stack_top(ba_stack_t *s);



#endif
