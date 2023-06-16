#ifndef _DYNSTRUCT_H
#define _DYNSTRUCT_H
typedef struct _dynstr
{
    int count;      //length of str
    int capacity;   //buffer length of str
    char *data;
}Dynstring;

typedef struct _dynarr
{
    int count;      //num of elements
    int capacity;   //length of buffer
    void **data;
}DynArray;

void dynstring_init(Dynstring* pstr, int initsize);
void dynstring_free(Dynstring* pstr);
void dynstring_reset(Dynstring* pstr);
void dynstring_realloc(Dynstring* pstr, int newsize);
void dynstring_addchar(Dynstring* pstr, int ch);
void dynarr_realloc(DynArray* parr, int newsize);
void dynarr_add(DynArray* parr, void* data);
void dynarr_init(DynArray* parr, int initsize);
void dynarr_free(DynArray* parr);
int dynarr_search(DynArray* parr, int key);

#endif