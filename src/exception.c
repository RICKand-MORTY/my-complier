#include <exception.h>
#include <stdlib.h>


char *filename = NULL;
int line_num = 0;

static void handle_exception(int stage, int level, char* fmt, va_list args)
{
    char buf[1024];
    vsprintf(buf, fmt, args);
    if(stage == STAGE_COMPILE)
    {
        if(level == LEVEL_WARNING)
        {
            printf("%s(第%d行):编译警告: %s!\n", filename, line_num, buf);
        }
        else
        {
            printf("%s(第%d行):编译错误: %s!\n", filename, line_num, buf);
            exit(-1);
        }
    }
    else
    {
        printf("链接错误: %s!\n", buf);
        exit(-1);
    }    
}

void warning(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    handle_exception(STAGE_COMPILE, LEVEL_WARNING, fmt, args);
    va_end(args);
}

void error(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    handle_exception(STAGE_COMPILE, LEVEL_ERROR, fmt, args);
    va_end(args);
}

//提出缺失成分
void expect(char* msg)
{
    error("缺少%s", msg);
}

void link_error(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    handle_exception(STAGE_LINK, LEVEL_ERROR, fmt, args);
    va_end(args);
}

//跳过单词c
void skip(int c)
{

}

//取得单词编号tkcode代表的源码字符串
char* get_tkstr(int tkcode)
{
    
}