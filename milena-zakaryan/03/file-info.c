#include <stdio.h> 
#include <sys/stat.h> 
#include <string.h> 
 
int main(int argc, char *argv[]) { 
    if (argc != 2) { 
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]); 
        return 1; 
    } 
 
    const char *file_path = argv[1]; 
    struct stat file_info; 
 
    if (stat(file_path, &file_info) == -1) { 
        perror("stat"); 
        return 1; 
    } 
 
    printf("Type: "); 
    if (S_ISREG(file_info.st_mode)) { 
        printf("regular file\n"); 
    } else if (S_ISDIR(file_info.st_mode)) { 
        printf("directory\n"); 
    } else if (S_ISLNK(file_info.st_mode)) { 
        printf("symbolic link\n"); 
    } else { 
        printf("unknown\n"); 
    } 
 
    printf("Name: %s\n", strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path); 
    printf("Path: %s\n", file_path); 
    printf("Size: %lld Bytes\n", (long long)file_info.st_size); 
    printf("Block Size: %lu Bytes\n", (unsigned long)file_info.st_blksize); 
    printf("Number of Blocks: %lu\n", (unsigned long)file_info.st_blocks); 
    printf("Permissions: %o\n", file_info.st_mode & 0777); 
    printf("Inode Number: %lu\n", (unsigned long)file_info.st_ino); 
    printf("Hard Links: %lu\n", (unsigned long)file_info.st_nlink); 
 
    return 0; 
}
