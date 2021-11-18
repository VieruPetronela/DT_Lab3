#ifndef __AT_COMMAND_PARSER__
#define __AT_COMMAND_PARSER__

#include <stdint.h>

#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 100

typedef enum{
    OK = 1,
    ERROR = 2
}Status;

typedef struct 
{
    int data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE];
    int row_count;
    Status status;

} AT_COMMAND_DATA;

typedef enum
{
    STATE_MACHINE_NOT_READY,
    STATE_MACHINE_READY_OK,
    STATE_MACHINE_READY_WITH_ERROR

} STATE_MACHINE_RETURN_VALUE;

AT_COMMAND_DATA my_data;

STATE_MACHINE_RETURN_VALUE MY_AT_COMMAND_PARSE(uint8_t crt_char);

#endif
