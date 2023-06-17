#ifndef _EXCEPTION_H
#define _EXCEPTION_H


#include <stdarg.h>
#include <stdio.h>

//错误级别
enum e_ErrorLevel
{
    LEVEL_WARNING,
    LEVEL_ERROR,
};

//工作状态
enum e_WorkStage
{
    STAGE_COMPILE,       //编译
    STAGE_LINK,         //链接
};

extern char *filename;
extern int line_num;

void warning(char* fmt, ...);
void error(char* fmt, ...);
void expect(char* msg);
void link_error(char* fmt, ...);
void skip(int c);
char* get_tkstr(int tkcode);
#endif