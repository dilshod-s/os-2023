#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *filePath = argv[1];
    struct stat fileInfo;

    if (stat(filePath, &fileInfo) == -1) {
        perror("stat");
        return 1;
    }

    printf("Type: ");
    if (S_ISREG(fileInfo.st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(fileInfo.st_mode)) {
        printf("directory\n");
    } else if (S_ISLNK(fileInfo.st_mode)) {
        printf("symbolic link\n");
    } else {
        printf("unknown\n");
    }

    printf("Name: %s\n", strrchr(filePath, '/') ? strrchr(filePath, '/') + 1 : filePath);
    printf("Path: %s\n", filePath);
    printf("Size: %lld Bytes\n", (long long)fileInfo.st_size);
    printf("Block Size: %lu Bytes\n", (unsigned long)fileInfo.st_blksize);
    printf("Number of Blocks: %lu\n", ((unsigned long)fileInfo.st_blocks)/(((unsigned long)fileInfo.st_blksize) / 512));
    printf("Permissions: %o\n", fileInfo.st_mode & 0777);
    printf("Inode Number: %lu\n", (unsigned long)fileInfo.st_ino);
    printf("Hard Links: %lu\n", (unsigned long)fileInfo.st_nlink);

    return 0;
}
