// # Lib Imports

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// # Local Imports

#include "../../include/Shell.hpp"

// # Static values

static const int read_size = 1024;

// # Methods

char *shell_read_line(void)
{
    char *buff = (char *)malloc(sizeof(char) * read_size);
    int size = read_size;
    char curr;
    int pos = 0;

    if (!buff)
        return (NULL);
    while (true) {
        curr = getchar();
        if (!curr || -1 == curr || curr == '\n') {
            buff[pos] = '\0';
            return (buff);
        } else
            buff[pos] = curr;
        (void)curr;
        pos++;
        if (pos >= read_size) {
            size += read_size;
            buff = (char *)realloc(buff, size);
        }
    }
}