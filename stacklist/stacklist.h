#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $8 (int8 *)
#define $6 (int16)
#define $4 (int64)
#define $2 (int32)
#define $c (char *)
#define $i (int)

typedef int8 Entry;

struct s_stacklist {
	Entry *data;
	int16 size;
	struct s_stacklist *next;
};
typedef struct s_stacklist Stacklist;

Stacklist *mkStacklist(void);
Stacklist *findlast(Stacklist*);
Stacklist *penultimate(Stacklist*);
bool push(Stacklist*, Entry*, int16);
Entry *pop(Stacklist*);
int main(int, char**);
