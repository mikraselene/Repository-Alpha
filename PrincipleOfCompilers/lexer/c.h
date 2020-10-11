int GetToken();
#define MAXLINE 512
#define BUFSIZE 4096

unsigned char *cp;
unsigned char *limit;
char *line;
unsigned int line_no;

static int bsize;