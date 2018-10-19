/*
getopt with help descriptions defined with options and auto generated with a certain format.
*/
#ifndef GET_OPT_H_H
#define GET_OPT_H_H

#include <getopt.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    const char * name;//if NULL no long command and also is short_name then this is the end of the options
    char short_name;//if 0 no short command
    int has_arg;
    const char * arg_name;//if NULL will show "ARG"
    const char * help_description;//if NULL will not show any description
    int * flag;
    int val;
} optionH;

extern int getopth(int argc, char * const * argv, const optionH* options, int * longind);

extern void __show_help(const optionH* options, const char * usage/*=NULL*/, FILE* file/*=stderr*/ );
struct help_args
{
    const optionH* options;
    const char * usage;
    FILE* file;
};
extern void __show_help_var(struct help_args);
#define show_help(/*const optionH* options, const char * usage=NULL, file=stderr*/...) __show_help_var((struct help_args){__VA_ARGS__});//()

extern char * get_short_opts(const optionH* options);//will return an allocated string, remember to free the space after

extern struct option * get_long_opts(const optionH * options);//will return an allocated longopt array that getopt_long and getopt_long_only requires, remember to free the space after

#ifdef __cplusplus
}
#endif
#endif