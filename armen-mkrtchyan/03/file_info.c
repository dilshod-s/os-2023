#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    //beryot argument i nastraivaet stat
    char *file_path = argv[1];
    struct stat file_stat;

    if(stat(file_path, &file_stat) == -1){
        
        perror("stat");
        return 1;
    }

    //opredelyaet tip faila
    const char *file_type = S_ISREG(file_stat.st_mode) ? "Regular File" :
                            S_ISDIR(file_stat.st_mode) ? "Directory" :
                            S_ISLNK(file_stat.st_mode) ? "Symbolic Link" :
                            "Other";

    //krasivo pechataet
    char *file_name = strrchr(file_path, '/');
    if(file_name == NULL){
        
        file_name = file_path;
        
    }else{ ++file_name; }

    printf("Type: %s\n", file_type);
    printf("Name: %s\n", file_name);
    printf("Path: %s\n", file_path);
    printf("Size: %ld Bytes\n", (long)file_stat.st_size);
    printf("Block size: %ld Bytes\n", (long)file_stat.st_blksize);
    printf("Number of Blocks: %ld\n", (long)file_stat.st_blocks);
    printf("File Permissions: %o\n", file_stat.st_mode & 0777); 
    printf("Creation Time: %s", ctime(&file_stat.st_ctime));
    printf("Last Modification Time: %s", ctime(&file_stat.st_mtime));
    printf("Inode Number: %lu\n", (unsigned long)file_stat.st_ino);
    printf("Hard Links: %lu\n", (unsigned long)file_stat.st_nlink);

    return 0;
}