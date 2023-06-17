#ifndef _WORD_LIST_H
#define _WORD_LIST_H
#include "dynstruct.h"

#define MAXKEY      1024                        //哈希表容量
extern TKWord *tk_hashtable[MAXKEY];            //单词的哈希表
extern DynArray tktable;                        //单词表

//单词编码表
enum e_TokenCode
{
    TK_PLUS,        //;
    TK_MINUS,       //-
    TK_STAR,        //*
    TK_DIVIDE,      // /
    TK_MOD,         //%
    TK_EQ,          //==
    TK_NEQ,         //!=
    TK_LT,          //<
    TK_LEQ,         //<=
    TK_GT,          //>
    TK_GEQ,         //>=
    TK_ASSIGN,      //=
    TK_POINTSTO,    //->
    TK_DOT,         //.
    TK_AND,         //&
    TK_OPENPA,      //(
    TK_CLOSEPA,     //)
    TK_OPENBR,      //[
    TK_CLOSEBR,     //]
    TK_BEGIN,       //{
    TK_END,         //}
    TK_SEMICOLON,   //;
    TK_COMMA,       //,
    TK_ELLTPSIS,    //...
    TK_EOF,         //end of file
    
    TK_CINT,        //integer constant
    TK_CCHAR,       //char constant
    TK_CSTR,        //str constant

    KW_CHAR,        //char
    KW_SHORT,       //short
    KW_INT,         //int
    KW_VOID,        //void
    KW_STRUCT,      //struct
    KW_IF,          //if
    KW_ELSE,        //else
    KW_FOR,         //for
    KW_CONTINUE,    //continue
    KW_BREAK,       //break
    KW_RETURN,      //return
    KW_SIZEOF,      //sizeof
    KW_ALIGN,       //__align
    KW_CDECL,       //__cdecl
    KW_STDCALL,     //__stdcall

    TK_IDENT        //Identifier
};

//单词存储结构
typedef struct _TKWord
{
    int tkcode;
    struct _TKWord* next;
    char* spelling;
}TKWord;

unsigned int ELFHash(char *s);
TKWord *tkword_direct_insert(TKWord * tp);
TKWord* tkword_find(char *word, int hashno);
TKWord* tkword_insert(char* p);
void init_lex();
#endif