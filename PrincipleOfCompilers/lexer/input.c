#include "c.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

static unsigned char buffer[MAXLINE + 1 + BUFSIZE + 1];

unsigned char *cp;
unsigned char *limit;
char *line;
char *file_name;
unsigned int line_no;

static int bsize;

void warning(char *w)
{
}

void error(char *w)
{
}
void FillBuf();
void NextLine()
{
	do
	{
		if (cp >= limit)
		{
			FillBuf();
			if (cp >= limit)
			{
				cp = limit;
			}
			if (cp == limit)
			{
				return;
			}
		}
		else
		{
			line_no++;
			line = (char *)cp;
			while (*cp == ' ' || *cp == '\t')
			{
				cp++;
			}
			if (*cp == '#')
			{
				// TODO:
				//Resynchronize();
				//NextLine();
			}
		}

	} while (*cp == '\n' && cp == limit);
}

void Initialize()
{
	limit = cp = &buffer[MAXLINE + 1];
	bsize = -1;
	line_no = 0;
	//file = NULL;
	FillBuf();
	if (cp >= limit)
	{
		cp = limit;
	}
	NextLine();
}

void FillBuf()
{
	if (bsize == 0)
	{
		return;
	}
	if (cp >= limit)
	{
		cp = &buffer[MAXLINE + 1];
	}
	else // Move the tail portion.
	{
		int n = limit - cp;
		unsigned char *s = &buffer[MAXLINE + 1] - n;
		assert(s >= buffer);
		line = (char *)s - ((char *)cp - line);
		while (cp < limit)
			*s++ = *cp++;
		cp = &buffer[MAXLINE + 1] - n;
	}
	if (feof(stdin))
		bsize = 0;
	else
		bsize = fread(&buffer[MAXLINE + 1], 1, BUFSIZE, stdin);
	if (bsize < 0)
	{
		error("read error\n");
		return;
	}
	limit = &buffer[MAXLINE + 1 + bsize];
	*limit = '\n';
}
