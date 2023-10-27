#include <stdio.h>
#include <stdlib.h> //for example exit 
#include <sys/stat.h> // for stat
#include <unistd.h> //for lsstat
#include <time.h> // fot time

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    if (lstat(argv[1], &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    printf("File type: ");

    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  
          printf("block device\n");
          break;
        case S_IFCHR:  
          printf("character device\n");
          break;
        case S_IFDIR:  
          printf("directory\n");               
          break;
        case S_IFIFO:  
          printf("FIFO/pipe\n");            
          break;
        case S_IFLNK: 
          printf("symlink\n");       
          break;
        case S_IFREG:
          printf("regular file\n");     
          break;
        case S_IFSOCK:
          printf("socket\n"); 
          break;
        default:     
          printf("unknown?\n");
          break;
    }

    printf("File size: %lld bytes\n", (long long) sb.st_size);
    printf("Blocks allocated: %lld\n", (long long) sb.st_blocks);
    printf("Block size: %ld\n", (long) sb.st_blksize);
    printf("Last status change: %s", ctime(&sb.st_ctime));
    printf("Last file access: %s", ctime(&sb.st_atime));
    printf("Last file modification: %s", ctime(&sb.st_mtime));
    printf("Number of hard links: %lu\n", (unsigned long) sb.st_nlink);
    printf("Inode number: %lu\n", (unsigned long) sb.st_ino);

    exit(EXIT_SUCCESS);
}
