#include <stdio.h>
#include "data.h"

int main(int argc, char **argv) {

    unsigned short var = 4;
    unsigned short amount = 100;
    unsigned short record_size = 10;

//    if(argc != 2){
//        printf("err #7 wrong format\n");
//        return -1;
//    }
//        read_file(argv[1]);

    //write_file(var, amount, record_size);
   read_file("data.dat");

    return 0;
}
