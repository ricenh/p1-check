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
    //parses the command line options and fails if false
    if(!parse_command_line_p1(argc, argv, &print_header, &filename)) 
    {
        return EXIT_FAILURE;
    }
    //checks to see if the filename is not NULL
    if(filename == NULL) 
    {
        return EXIT_FAILURE;
    }
    //opens and loads file
    FILE *file = fopen(filename, "r");
    struct elf hdr;
    if(!read_header(file, &hdr)) 
    {
        //fails to read file if not true and exits program
        printf("Failed to read file\n");
        return EXIT_FAILURE;
    }
    if(print_header) 
    {
        //prints the elf header
        dump_header(&hdr);
        return EXIT_SUCCESS;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

