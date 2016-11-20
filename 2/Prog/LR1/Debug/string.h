#ifndef TheMyString
#define TheMyString

int slen(char *s);
int schr(char s[], char c);
int stok(char str[], char delim, char *ptr[]);
int suntok(char *str, char delim, char *ptr[80], int cnt);
void scpy(char m[], char y[]);
int scmp(char m[], char n[]);

#endif
