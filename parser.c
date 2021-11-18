#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

STATE_MACHINE_RETURN_VALUE MY_AT_COMMAND_PARSE(uint8_t crt_char)
{
    static uint8_t state = 0;
    static int col_index = 0;
    static  bool stop = false;

    switch(state)
    {
        case 0:
        {   
            
            memset(my_data.data,'\0', sizeof(my_data.data));
            if(crt_char == '\r')
            {
                state = 1;
                my_data.row_count = 0;
                stop = false;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            
        }
        case 1:
        {
            if(crt_char == '\n')
            {
                state = 2;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 2:
        {
            if(crt_char == 'O')
            {
               
                state = 3;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == 'E')
            {
                state = 7;
                stop = false;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == '+')
            {
                state = 14;
                stop = false;
                return STATE_MACHINE_NOT_READY;
            }
        }
        case 3:
        {
            if(crt_char == 'K')
            {
                state = 4;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 4:
        {
            if(crt_char == '\r')
            {
                state = 5;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 5:
        {
            if(crt_char == '\n')
            {
                state = 6;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 6:
        {
            state = 0;
            stop = false;
            my_data.status = OK;
            return STATE_MACHINE_READY_OK;
        }
        case 7:
        {
            if(crt_char == 'R')
            {
                state = 8;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 8:
        {
            if(crt_char == 'R')
            {
                state = 9;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 9:
        {
            if(crt_char == 'O')
            {
                state = 10;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 10:
        {
            if(crt_char == 'R')
            {
                state = 11;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 11:
        {

            if(crt_char == '\r')
            {
                state = 12;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 12:
        {
            if(crt_char == '\n')
            {
                state = 13;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 13:
        {
            state = 0;
            stop = false;
            my_data.status = ERROR;
            return STATE_MACHINE_READY_OK;
        }
        case 14:
        {
            
            if(crt_char >= 32 && crt_char <= 126)
            {
                if(col_index < AT_COMMAND_MAX_LINE_SIZE)
                {
                    if(stop == false)
                    {
                        my_data.data[my_data.row_count][col_index] = crt_char;
                    }
                    col_index++;
                    state = 14;
                }

                return STATE_MACHINE_NOT_READY;
            }
            if(crt_char == '\r')
            {
                state = 15;
                if(col_index <= AT_COMMAND_MAX_LINE_SIZE)
                {
                    if(stop == false)
                    {
                        my_data.data[my_data.row_count][col_index] = '\0'; 
                    }
                    col_index = 0;
                }
                return STATE_MACHINE_NOT_READY;
            }

            return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 15:
        {
            if(crt_char == '\n')
            {
                
                state = 16;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 16:
        {
            if(crt_char == '+')
            {
                
                if(my_data.row_count >= AT_COMMAND_MAX_LINES - 1)
                {
                    stop=true;
                }
                else
                {
                    my_data.row_count++;
                    
                }
                state = 14;
                return STATE_MACHINE_NOT_READY;
            }
            if(crt_char == '\r')
            {
                
                state = 17;
                return STATE_MACHINE_NOT_READY;
            }
            
            return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 17:
        {
            if(crt_char == '\n')
            {
                state = 18;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 18:
        {
            if(crt_char == 'O')
            {
                state = 3;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == 'E')
            {
                state = 7;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        default:
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
}