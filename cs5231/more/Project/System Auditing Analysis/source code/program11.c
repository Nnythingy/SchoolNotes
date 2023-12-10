int __cdecl main(int argc, const char **argv, const char **envp)
{
  FILE *stream; // [rsp+0h] [rbp-150h]
  FILE *s; // [rsp+8h] [rbp-148h]
  __int64 ptr[2]; // [rsp+10h] [rbp-140h] BYREF
  char v7[280]; // [rsp+20h] [rbp-130h] BYREF
  int v8; // [rsp+138h] [rbp-18h]
  unsigned __int64 v9; // [rsp+148h] [rbp-8h]

  v9 = __readfsqword(0x28u);
  stream = fopen("/home/student/secret/secret.txt", "r");
  ptr[0] = 0LL;
  ptr[1] = 0LL;
  memset(v7, 0, sizeof(v7));
  v8 = 0;
  fread(ptr, 0xC8uLL, 1uLL, stream);
  printf("buf: %s\n", (const char *)ptr);
  s = fopen("/home/attacker/output.txt", "w");
  printf("opened fp %p\n.", s);
  fwrite(ptr, 0xC8uLL, 1uLL, s);
  return 0;
}