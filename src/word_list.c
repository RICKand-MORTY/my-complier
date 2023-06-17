#include <word_list.h>
#include <string.h>
#include <stdlib.h>

#define FILLIN(tkcode, symbol)          {(int)(tkcode), NULL, (char*)(symbol)}

TKWord *tk_hashtable[MAXKEY];           //单词的哈希表
DynArray tktable;                       //单词表

//哈希函数
unsigned int ELFHash(char *s)
{
    int h = 0, g = 0;
    while(*s)
    {
        h = (h << 4) + *s++;        //目的为了每个字符都能影响到哈希值
        g = h & 0xf0000000;         //取最高四位
        /*
            判断最高4位是否为0,如果最高4位不为0,则左移会溢出,
            溢出会让最开始的字符对哈希值的影响失效          
        */
        if(g)       
        {
            h ^= g >> 24;   //影响低8位中的高8位
        }
        h &= ~g;            //最高4位清0
    }
    return h%MAXKEY;
}

//直接插入,运算符,关键字,常量使用
TKWord *tkword_direct_insert(TKWord * tp)
{
    int no;
    dynarr_add(&tktable, (void*)tp);
    no = ELFHash(tp->spelling);         //计算哈希值
    tp->next = tk_hashtable[no];
    tk_hashtable[no] = tp;
    return tp;
}

TKWord* tkword_find(char *word, int hashno)
{
    TKWord *p = tk_hashtable[hashno];
    while(p != NULL)
    {
        if(strcmp(p, p->spelling) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}


//将标识符插入单词表
TKWord* tkword_insert(char* p)
{
    TKWord *tp = NULL;
    int no = ELFHash(p);
    tp = tkword_find(p, no);
    if(tp == NULL)
    {
        int len = strlen(p);
        tp = (TKWord*)malloc(sizeof(TKWord) + len + 1);     //预留空间存字符串p
        memset(tp, 0, (sizeof(TKWord) + len + 1));
        tp->next = tk_hashtable[no];
        tk_hashtable[no] = tp;
        dynarr_add(&tktable, (void*)tp);
        tp->tkcode = tktable.count - 1;                     //单词的编码与动态数组下标是一一对应的
        char *str = (char*)tp + sizeof(TKWord);             
        char *end = p + len;
        char *start = p;
        while(start != end)
        {
            //将字符串p存入tp中
            *str = *start;
            str++;
            start++;
        }
        *str = '\0';
    }
    return tp;
}

//初始化单词表(词法分析初始化时调用)
void init_lex()
{
    TKWord* tp = NULL;
    memset(tk_hashtable, NULL, (MAXKEY * sizeof(TKWord*)));
    static TKWord keywords[]=
    {
        FILLIN(TK_PLUS,         "+"),
        FILLIN(TK_MINUS,        "-"),
        FILLIN(TK_STAR,         "*"),
        FILLIN(TK_DIVIDE,       "/"),
        FILLIN(TK_MOD,          "%"),
        FILLIN(TK_EQ,           "="),
        FILLIN(TK_NEQ,          "!="),
        FILLIN(TK_LT,           "<"),
        FILLIN(TK_LEQ,          "<="),
        FILLIN(TK_GT,           ">"),
        FILLIN(TK_GEQ,          ">="),
        FILLIN(TK_ASSIGN,       "="),
        FILLIN(TK_POINTSTO,     "->"),
        FILLIN(TK_DOT,          "."),
        FILLIN(TK_AND,          "&"),
        FILLIN(TK_OPENPA,       "("),
        FILLIN(TK_CLOSEPA,      ")"),
        FILLIN(TK_OPENBR,       "["),
        FILLIN(TK_CLOSEBR,      "]"),
        FILLIN(TK_BEGIN,        "{"),
        FILLIN(TK_END,          "}"),
        FILLIN(TK_SEMICOLON,    ";"),
        FILLIN(TK_COMMA,        ","),
        FILLIN(TK_ELLTPSIS,     "..."),
        FILLIN(TK_EOF,          "End_Of_File"),
        FILLIN(TK_CINT,         "整型常量"),
        FILLIN(TK_CCHAR,        "字符常量"),
        FILLIN(TK_CSTR,         "字符串常量"),
        FILLIN(KW_CHAR,         "char"),
        FILLIN(KW_SHORT,        "short"),
        FILLIN(KW_INT,          "int"),
        FILLIN(KW_VOID,         "void"),
        FILLIN(KW_STRUCT,       "struct"),
        FILLIN(KW_IF,           "if"),
        FILLIN(KW_ELSE,         "else"),
        FILLIN(KW_FOR,          "for"),
        FILLIN(KW_CONTINUE,     "continue"),
        FILLIN(KW_BREAK,        "break"),
        FILLIN(KW_RETURN,       "return"),
        FILLIN(KW_SIZEOF,       "sizeof"),
        FILLIN(KW_ALIGN,         "__align"),
        FILLIN(KW_CDECL,         "__cdecl"),
        FILLIN(KW_STDCALL,       "__stdcall"),
        {0, NULL, NULL} //结束标志
    };
    dynarr_init(&tktable, 8);
    for(tp = &keywords[0]; tp->spelling != NULL; tp++)
    {
        tkword_direct_insert(tp);
    }
}