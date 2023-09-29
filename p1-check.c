/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: 
 */

#include "p1-check.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
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
    if(argc <= 1 || argv == NULL || print_header == NULL || filename == NULL) {
        return false;
    }
    bool help = false;
    *print_header = false;
    int c;
    while ((c = getopt(argc, argv, "hH")) != -1) 
    {
        switch (c) {/*switches the key based on the input*/
            case'h':
                help = true;
                break;
            case'H':
                *print_header = true;
                break;
            default:
                return false;

        }
    }
    if(help) {
        usage_p1(argv);
        return true;
    } else {
         if (optind < argc) {
            *filename = argv[optind];
            return true; 
        } else {
            return false; 
        }
    }
}

void dump_header (elf_hdr_t *hdr)
{
    unsigned char *bits = (unsigned char *) hdr;
    for(int i=0; i < 16; i++) 
    {
        if(i == 8) 
        {
            printf(" ");
        }
        printf("%02x",bits[i]);
        if(i < 15) 
        {
            printf(" ");
        }
    }
    printf("\n");
    printf("Mini-ELF version %d\n", hdr->e_version);
    printf("Entry point %#x\n", hdr->e_entry);
    printf("There are %d program headers, starting at offset %d (%#x)\n", hdr->e_num_phdr, hdr->e_phdr_start, hdr->e_phdr_start);
    if(hdr->e_symtab == 0) {
        printf("There is no symbol table present\n");
    } else {
        printf("There is a symbol table starting at offset %d (%#x)\n", hdr->e_symtab, hdr->e_symtab);
    }
    if(hdr->e_strtab == 0) {
        printf("There is no string table present\n");
    } else {
        printf("There is a string table starting at offset %d (%#x)\n",hdr->e_strtab, hdr->e_strtab);
    }
}

