#include <word_list.h>
#include <string.h>


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

