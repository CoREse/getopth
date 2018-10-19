#include "../getopth.h"
#include <stdio.h>

int main (int argc, char * const * argv)
{
    optionH options[]={
        {"aop",0,no_argument,0,"aaa",0,0},
        {"bop",'b',required_argument,0,"this is a b option",0,0},
        {0,'c',optional_argument,"INT","this is a c option"},
        {"d",0,optional_argument,"STRING","this is a d option"},
        {"help",'h',no_argument,0,"show this help"},
        {0,0,no_argument,0,0,0,0}
    };
    int longind;
    int option;
    FILE* fp_help=stderr;
    while ((option= getopth(argc,argv,&options,&longind))>=0)
    {
        if (option == 'b')
        {
            printf("execute bop with %s=%s.",options[1].arg_name?options[1].name:"ARG",optarg);
        }
        else if (option == 'c')
        {
            printf("execute cop");
            if (optarg == NULL)
                printf(" without argument.\n");
            else printf(" with %s=%d.\n",options[2].arg_name?options[2].arg_name:"ARG",atoi(optarg));
        }
        else if (option == 'h' || longind == 4)
        {
            fp_help=stdout;
        }
        else if (option == 0)
        {
            if (longind == 0)
                printf("execute aop\n");
            else if (longind == 1)
                printf("execute bop with %s=%s.", options[1].arg_name ? options[1].name : "ARG",optarg);
            else if (longind == 2)
                printf("execute cop\n"); //not gonna happen
            else if (longind == 3)
            {
                printf("execute dop");
                if (optarg == NULL)
                    printf(" without argument.\n");
                else
                    printf(" with %s=%s.\n", options[3].arg_name?options[2].arg_name:"ARG",optarg);
            }
        }
    }
    if (argc == optind)
        show_help(&options, "Usage: example [options] filename", fp_help) return 0;
}