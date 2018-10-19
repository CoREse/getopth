#include "getopth.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

char * get_short_opts(const optionH* options)
{
    char* result=(char*) malloc(1000);//>256*3

    unsigned j=0;
    for (unsigned i = 0; options[i].name != NULL || options[i].short_name != 0;++i)
    {
        if (options[i].short_name != 0)
        {
            result[j++]=options[i].short_name;
            switch (options[i].has_arg)
            {
            case no_argument:
                break;
            case optional_argument:
                result[j++] = ':';
            case required_argument:
                result[j++] = ':';
                break;
            }
        }
    }
    result[j]='\0';
    return result;
}

struct option *get_long_opts(const optionH *options)
{
    unsigned count = 0;
    unsigned i = 0;
    for (i = 0; options[i].name != NULL || options[i].short_name != 0; ++i)
    {
        ++count;
    }
    struct option *result = (struct option *)malloc((count + 1) * sizeof(struct option));
    unsigned j = 0;
    for (i = 0; options[i].name != NULL || options[i].short_name != 0; ++i)
    {
        if (options[i].name != NULL)
        {
            result[j].name = options[i].name;
            result[j].has_arg = options[i].has_arg;
            result[j].flag = options[i].flag;
            result[j++].val = options[i].val;
        }
    }
    result[j].name = NULL;
    return result;
}
int getopth(int argc, char * const * argv, const optionH* options, int * longind)
{
    struct option *long_options=get_long_opts(options);
    char * short_options=get_short_opts(options);
    unsigned l=0;
    while (long_options[l].name!=NULL) ++l;
    int result=getopt_long(argc,argv,short_options,long_options,longind);
    if (*longind<l && *longind>=0)
    {
        l=0;
        unsigned k=0;
        while (options[l].short_name!=0 || options[l].name!=NULL)
        {
            if (options[l].name!=NULL)
            {
                if (k++==*longind)
                {
                    *longind=l;
                    break;
                }
            }
            ++l;
        }
    }
    free(long_options);
    free(short_options);
    return result;
}

void __show_help(const optionH* options, const char * usage, FILE* file)
{
    if (usage!=NULL) fprintf(file,"%s\n",usage);
    fprintf(file,"Options:\n");
    for (unsigned i=0;options[i].name != NULL || options[i].short_name != 0; ++i)
    {
        fprintf(file,"  ");
        unsigned j = 0;
        if (options[i].short_name != 0)
        {
            fprintf(file, "-%c", options[i].short_name);
            j = 2;
            if (options[i].has_arg != no_argument)
            {
                if (options[i].has_arg == optional_argument)
                {
                    fprintf(file, "[");
                    ++j;
                }
                else
                {
                    fprintf(file, " ");
                    ++j;
                }
                if (options[i].arg_name == NULL)
                {
                    fprintf(file, "ARG");
                    j += 3;
                }
                else
                {
                    unsigned k = 0;
                    while (options[i].arg_name[k] != '\0')
                    {
                        fprintf(file, "%c", options[i].arg_name[k++]);
                        if ((j + k) % 28 == 0)
                            fprintf(file, "\n  ");
                    }
                    j += k;
                }
                if (options[i].has_arg == optional_argument)
                {
                    fprintf(file, "]");
                    ++j;
                    if (j % 28 == 0)
                        fprintf(file, "\n  ");
                }
            }
        }

        if (options[i].name != NULL)
        {
            if (options[i].short_name != 0)
            {
                fprintf(file, ",");
                ++j;
                if (j % 28 == 0)
                    fprintf(file, "\n  ");
                fprintf(file, " ");
                ++j;
                if (j % 28 == 0)
                    fprintf(file, "\n  ");
            }
            fprintf(file, "-");
            ++j;
            if (j % 28 == 0)
                fprintf(file, "\n  ");
            fprintf(file, "-");
            ++j;
            if (j % 28 == 0)
                fprintf(file, "\n  ");
            unsigned k = 0;
            while (options[i].name[k] != '\0')
            {
                fprintf(file, "%c", options[i].name[k++]);
                if ((j + k) % 28 == 0)
                    fprintf(file, "\n  ");
            }
            j += k;
            if (options[i].has_arg != no_argument)
            {
                if (options[i].has_arg == optional_argument)
                {
                    fprintf(file, "[");
                    ++j;
                    if (j % 28 == 0)
                        fprintf(file, "\n  ");
                }

                fprintf(file, "=");
                ++j;
                if (j % 28 == 0)
                    fprintf(file, "\n  ");
                const char *arg_name = options[i].arg_name == NULL ? "ARG" : options[i].arg_name;
                unsigned k = 0;
                while (arg_name[k] != '\0')
                {
                    fprintf(file, "%c", arg_name[k++]);
                    if ((j + k) % 28 == 0)
                        fprintf(file, "\n  ");
                }
                j += k;

                if (options[i].has_arg == optional_argument)
                {
                    fprintf(file, "]");
                    ++j;
                }
            }
        }
        for (unsigned k = 0; k < 32 - (j % 28); ++k)
            fprintf(file, " ");
        j = 32;
        if (options[i].help_description != NULL)
            fprintf(file, options[i].help_description);
        fprintf(file, "\n");
    }
}

void __show_help_var(struct help_args args)
{
    if (args.file == NULL)
        args.file = stderr;
    __show_help(args.options, args.usage, args.file);
}

#ifdef __cplusplus
}
#endif