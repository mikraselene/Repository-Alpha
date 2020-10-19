#include "c.h"

uchar *buf;

uint ReadFile(const char *name)
{
    FILE *fp = fopen(name, "r");
    fseek(fp, 0, SEEK_END);
    uint len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = MALLOC(uchar, len);
    cp = buf;
    fread(cp, len, 1, fp);
    fclose(fp);
    return len;
}
