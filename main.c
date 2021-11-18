#include "parser.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_matrix(int matrix[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE], FILE *output)
{
    int i, j;
    static int crt = 1;
    
    fprintf(output, "\n------------------- %d ----------------------\n", crt );
    for(i=0; i <= my_data.row_count; i++)
    {
        for(j=0; j < AT_COMMAND_MAX_LINE_SIZE; j++)
        {
            fprintf(output,"%c",matrix[i][j]);
        }
        fprintf(output,"\n");
    }
    fprintf(output, "\n-----------------------------------------\n");
    crt++;
}

int main(int argc, char **argv)
{
    STATE_MACHINE_RETURN_VALUE machine_result;
    int continue_ = 0;
    int crt_char;
    FILE *my_file = fopen(argv[1], "rb");
    FILE *output = fopen("output.txt", "w");
    
    if (argc != 2)
    {
        fprintf (stderr, "Usage: dir1 dir2.. %s \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (my_file == NULL)
	{
	    printf("Error in the file!\n");
		exit(EXIT_FAILURE);
	}
    if (output == NULL)
	{
	    printf("Error in the output file!\n");
		exit(EXIT_FAILURE);
	}

    crt_char = fgetc(my_file);
    while(crt_char != EOF)
    {
        machine_result = MY_AT_COMMAND_PARSE(crt_char);
        if(machine_result == 0)
        {
            continue_ ++;
        }
        if(machine_result == 1)
        {
            printf("OK: STATE_MACHINE_READY_OK\t");
            if(my_data.status == OK)
            {
                printf("Terminated with status: OK\n");
            }
            else
            {
                printf("Terminated with status: ERROR\n");
            }
            print_matrix(my_data.data, output);
        }
        if(machine_result == 2)
        {
            printf("ERROR: STATE_MACHINE_READY_WITH_ERROR\n");
            return 0;
        }
        crt_char = fgetc(my_file);
    }

    if(machine_result == 0)
        {
            printf("Something wrong happened!\n");
        }

    fclose(my_file);
    return 0;
}