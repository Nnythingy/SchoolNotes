int __cdecl main(int argc, const char **argv, const char **envp)
{
  int i; // [rsp+4h] [rbp-18Ch]
  FILE *stream; // [rsp+8h] [rbp-188h]
  char s[64]; // [rsp+10h] [rbp-180h] BYREF
  char ptr[312]; // [rsp+50h] [rbp-140h] BYREF
  unsigned __int64 v8; // [rsp+188h] [rbp-8h]

  v8 = __readfsqword(0x28u);
  for ( i = 20; i <= 29; ++i )
  {
    sprintf(s, "/tmp/file_%d.txt", (unsigned int)(i + 1));
    stream = fopen(s, "r");
    fread(ptr, 0x32uLL, 1uLL, stream);
    printf("content: %s", ptr);
  }
  return 0;
}