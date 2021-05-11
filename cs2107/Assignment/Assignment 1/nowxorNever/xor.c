#include <stdio.h>
#include <string.h>

#ifndef MAX_PATH
#define MAX_PATH    256
#endif

#define INPUTPATH "c:\\documents"
#define OUTPUTPATH ""

int main (int argc, char **argv)
{
    FILE *inp, *outp;
    int i, encode_flag = 0;
    char filename_buffer[MAX_PATH];
    char sig[] = "CF10", *ptr;

    if (argc != 3)
    {
        printf ("usage: decode [input] [output]\n");
        return -1;
    }

    filename_buffer[0] = 0;
    if (!strchr(argv[1], '/') && !strchr(argv[1], 92) && !strchr(argv[1], ':'))
        strcpy (filename_buffer, INPUTPATH);
    strcat (filename_buffer, argv[1]);

    inp = fopen (filename_buffer, "rb");
    if (inp == NULL)
    {
        printf ("bad input file '%s'\n", filename_buffer);
        return -2;
    }
    ptr = sig;
    while (*ptr)
    {
        i = fgetc (inp);
        if (*ptr != i)
        {
            encode_flag = 1;
            break;
        }
        ptr++;
    }
    if (encode_flag)
    {
        /* rewind file because we already read some bytes */
        fseek (inp, 0, SEEK_SET);
        printf ("encoding input file: '%s'\n", filename_buffer);
    } else
        printf ("decoding input file: '%s'\n", filename_buffer);

    filename_buffer[0] = 0;
    if (!strchr(argv[2], '/') && !strchr(argv[2], 92) && !strchr(argv[2], ':'))
        strcpy (filename_buffer, OUTPUTPATH);
    strcat (filename_buffer, argv[2]);

    outp = fopen (filename_buffer, "wb");
    if (outp == NULL)
    {
        printf ("bad output file '%s'\n", filename_buffer);
        return -2;
    }
    printf ("output file: '%s'\n", filename_buffer);

    if (encode_flag)
        fwrite (sig, 1, 4, outp);
    do
    {
        i = fgetc(inp);
        if (i != EOF)
            fputc (i ^ 0x3064657030646570, outp);
    } while (i != EOF);
    fclose (inp);
    fclose (outp);
    printf ("all done. bye bye\n");
    return 0;
}
