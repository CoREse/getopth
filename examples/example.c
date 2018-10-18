#include "../getopth.h"
#include <stdio.h>

int main (int argc, char * const * argv)
{
    optionH options[]={
        {"aop",0,no_argument,0,"aaa",0,0},
        {"bop",'b',required_argument,0,"this is a b option",0,0},
        {0,'c',optional_argument,"myArg","this is a c option"},
        {"d",0,optional_argument,"myArg","this is a d option"},
        {0,0,no_argument,0,0,0,0}
    };
    int longind;
    int option= getopth(argc,argv,&options,&longind);
    if (option=='b') printf("execute bop\n");
    else if (option=='c') printf("execute cop\n");
    else if (option==0)
    {
        if (longind==0) printf("execute aop\n");
        else if (longind==1) printf("execute bop\n");
        else if (longind==2) printf("execute cop\n");//not gonna happen
        else if (longind==3) printf("execute dop\n");
    }
    else show_help(&options,"Usage: example [options]")
    return 0;
}