#include "data.h"

int init_data(int serial, struct records *record){

    record->magic = 0xDEADBEEF;
    record->serial = serial;
    record->data = rand() % 0xFFFFFFFF;

    return 0;
};

int write_file(unsigned short var, unsigned short amount_of_records, unsigned short record_size){


    time_t timer;
    srand((unsigned) time(&timer));

    FILE *file_pointer;

    bool alignment[100];
    for(int j = 0; j < sizeof(alignment); j++){
        alignment[j] = rand() & 2;
    }

    struct headers header = {.var = var, .amount_of_records = amount_of_records, .record_size = record_size};
    struct records array_of_records[header.amount_of_records];

    file_pointer = fopen("data.dat", "wb");
    if(file_pointer == NULL){
        printf("err fopen");
    }

    if( fwrite(&header, sizeof(struct headers), 1, file_pointer) != 1 ){
        printf("err fwrite header");
    }

    for(int i = 0; i < header.amount_of_records; i++){
        if( init_data(i, &array_of_records[i]) != 0){
            printf("err init_data");
        }

        if( fwrite(&array_of_records[i], header.record_size, 1, file_pointer) != 1 ){
            printf("err fwrite record #%d", i);
        }


        int rand_num = rand() % 100;


        for(int j =0; j < rand_num; j++){
            int fwrite_t = fwrite(&alignment, sizeof(alignment[0]), 1, file_pointer);
            if(fwrite_t != 1){
                printf("alignment write err\n");
            }
        }


    }

    if( fclose(file_pointer) != 0){
        printf("err fclose");
    }

    return 0;
};