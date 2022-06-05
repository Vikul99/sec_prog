#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int write_file(unsigned short var, unsigned short amount_of_records, unsigned short record_size);
int read_file(char *file_name);



struct headers{
    unsigned short var;
    unsigned short amount_of_records;
    unsigned short record_size;
};

struct records{
    unsigned int magic;
    unsigned short serial;
    unsigned int data;
};


#ifndef DZ1_DATA_H
#define DZ1_DATA_H

#endif //DZ1_DATA_H
