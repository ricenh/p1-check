/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: Noah Rice
 */

#include "p1-check.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    //checks the file if it is null, reads the elf header of the file to see if its is true, checks the magic number
    if(file == NULL || (fread(hdr, sizeof(elf_hdr_t), 1, file) != 1) || hdr->magic != 4607045) {
        return false;
    }
    return true;
}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void usage_p1 (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
}

bool parse_command_line_p1 (int argc, char **argv, bool *print_header, char **filename)
{
    //checks all args to not be NULL
    if(argc <= 1 || argv == NULL || print_header == NULL || filename == NULL) 
    {
        return false;
    }
    bool help = false;
    *print_header = false;
    int file_count = 0;
    int c;
    //getopt for -h help and -H print the header and its default which prints usage_p1
    while ((c = getopt(argc, argv, "hH")) != -1) 
    {
        switch (c) {
            case'h':
                help = true;
                break;
            case'H':
                *print_header = true;
                break;
            default:
                usage_p1(argv);
                return false;

        }
    }
        //checks to see that there are not multiple files or params and returns false
        for (int i = optind; i < argc; ++i) {
        *filename = argv[i];
        file_count++;
        if (file_count > 1) {
            usage_p1(argv);
            return false;
        }
    }
    if(help) 
    {
        usage_p1(argv);
        return true;
    } else {
        //stores the file into filename to be used and if null returns false
        *filename = argv[optind];
        if(*filename == NULL)
        {
            usage_p1(argv);
            return false;
        }

        return true;
    }
}


void dump_header (elf_hdr_t *hdr)
{
    //type casts the hdr to unsigned char
    unsigned char *bits = (unsigned char *) hdr;
    for(int i=0; i < 16; i++) 
    {
        //extra space after 8 bits for readability
        if(i == 8) 
        {
            printf(" ");
        }
        //prints two bits
        printf("%02x",bits[i]);
        if(i < 15) 
        {
            //spaces after every pair of bits besides the last one
            printf(" ");
        }
    }
    printf("\n");
    printf("Mini-ELF version %d\n", hdr->e_version);
    printf("Entry point %#x\n", hdr->e_entry);
    printf("There are %d program headers, starting at offset %d (%#x)\n", hdr->e_num_phdr, hdr->e_phdr_start, hdr->e_phdr_start);
    //prints the symbol table if it is present and its location
    if(hdr->e_symtab == 0) {
        printf("There is no symbol table present\n");
    } else {
        printf("There is a symbol table starting at offset %d (%#x)\n", hdr->e_symtab, hdr->e_symtab);
    }
    //prints the strig table if it is present and its location
    if(hdr->e_strtab == 0) {
        printf("There is no string table present\n");
    } else {
        printf("There is a string table starting at offset %d (%#x)\n",hdr->e_strtab, hdr->e_strtab);
    }
}

