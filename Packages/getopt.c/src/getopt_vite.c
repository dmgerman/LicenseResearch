#ifdef WIN32
#include <windows.h>
#include <stdio.h>

char    *optarg;                // global argument pointer
int             optind = 0;     // global argv index
char c;
char *cp;

int getopt(int argc, char *argv[], char *optstring)
{
        static char *next = NULL;
        if (optind == 0)
                next = NULL;

        optarg = NULL;

        if (next == NULL || *next == '\0')
        {
                if (optind == 0)
                        optind++;

                if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
                {
                        optarg = NULL;
                        if (optind < argc)
                                optarg = argv[optind];
                        return EOF;
                }

                if (strcmp(argv[optind], "--") == 0)
                {
                        optind++;
                        optarg = NULL;
                        if (optind < argc)
                                optarg = argv[optind];
                        return EOF;
                }

                next = argv[optind];
                next++;         // skip past -
                optind++;
        }

        c = *next++;
        cp = strchr(optstring, c);

        if (cp == NULL || c == ':')
                return '?';

        cp++;
        if (*cp == ':')
        {
                if (*next != '\0')
                {
                        optarg = next;
                        next = NULL;
                }
                else if (optind < argc)
                {
                        optarg = argv[optind];
                        optind++;
                }
                else
                {
                        return '?';
                }
        }

        return c;
}

#endif
