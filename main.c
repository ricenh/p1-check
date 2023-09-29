/*
 * CS 261: Main driver
 *
 * Name: Noah Rice
 */

#include "p1-check.h"


int main (int argc, char **argv)
{
    bool print_header = false;
    char *filename = NULL;
    if(!parse_command_line_p1(argc, argv, &print_header, &filename)) 
    {
        return EXIT_FAILURE;
    }
    if(filename == NULL) 
    {
        return EXIT_FAILURE;
    }
    FILE *file = fopen(filename, "r");
    struct elf hdr;
    if(!read_header(file, &hdr)) 
    {
        printf("Failed to read file\n");
        return EXIT_FAILURE;
    }
    if(print_header) 
    {
        dump_header(&hdr);
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

