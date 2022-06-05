#include "data.h"

int print_unique_values_in_array(unsigned short *array, int len){

    if (len <= 0 || array == NULL)
    {
        printf("error with data");
        return 1;
    }

    int occurrences[65536] = {0}; // initialize all values to 0.


    for (int i=0; i < len; i++) {
        if (array[i] > 65535 || array[i] < 0)
        {
            printf("wrong data in array");
            return 1;
        }
        occurrences[array[i]] += 1;
    }

    int unique_occurrences = 0;

    for (int i=0; i < 65536; i++) {
        if (occurrences[i] != 0)
            unique_occurrences += 1;
    }

    printf("Total number of unique types:  %d\n", unique_occurrences);
    return 0;};

int read_file(char *file_name){
    FILE *file_pointer;

    file_pointer = fopen(file_name, "rb");
    if(file_pointer == NULL){
        printf("err #1 fopen");
        return -2;
    }

    struct headers my_header;
    struct records my_record;

    if( fread(&my_header, sizeof(my_header), 1, file_pointer) != 1){
        printf("err #2 fread header");
        return -2;
    }

    if(my_header.var != 4){
        printf("err #3 wrong variant");
        return -2;
    }

    if(my_header.record_size != 10){
        printf("err #4 wrong record size\n");
        return -2;
    }

    unsigned int test = 0;
    int i = 0;
    int j =0;
    unsigned short types[my_header.amount_of_records];
    memset(types, 0, my_header.amount_of_records);



    while(fread(&test, sizeof(test), 1, file_pointer) == 1){


        if(test == 0xDEADBEEF){

            if( fseek(file_pointer, -4, SEEK_CUR) != 0){
                printf("err #4 fseek");
                return -2;
            }

            if( fread(&my_record, sizeof(my_record), 1, file_pointer) != 1){
                printf("err #5 fread\n");
                return -2;
            }

            types[j] = my_record.data;

            j++;

        }
        else{

            if(feof(file_pointer)){
                printf("hit end of file\n");
                break;
            }

            if( fseek(file_pointer, -3, SEEK_CUR) != 0) {
                printf("err #6 fseek");
                return -2;
            }
        }
        i++;
    }

    if(print_unique_values_in_array(types, sizeof(types)/sizeof(types[0]))){
        return 1;
    }

    if( fclose(file_pointer) != 0){
        printf("err #7 fclose");
        return -2;
    }


    return 0;};


