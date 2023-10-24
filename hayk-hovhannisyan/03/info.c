#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error!\n");
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 2;
    }

    printf("Type: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("file\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("directory\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("symbolic link\n");
    } else {
        printf("other\n");
    }

    printf("Name: %s\n", argv[1]);
    printf("Path: %s\n", realpath(argv[1], NULL));
    printf("Size: %ld байт\n", fileStat.st_size);
    printf("Block size: %ld байт\n", fileStat.st_blksize);
    printf("Number of blocks: %ld\n", fileStat.st_blocks/8);
    printf("Permissions %o\n", fileStat.st_mode & 0777);

    struct tm createdTime;
    struct tm modifiedTime;

    localtime_r(&fileStat.st_ctime, &createdTime);
    localtime_r(&fileStat.st_mtime, &modifiedTime);

    char createdTimeString[20];
    char modifiedTimeString[20];

    strftime(createdTimeString, sizeof(createdTimeString), "%Y-%m-%d %H:%M:%S", &createdTime);
    strftime(modifiedTimeString, sizeof(modifiedTimeString), "%Y-%m-%d %H:%M:%S", &modifiedTime);

    printf("Date of creation.: %s\n", createdTimeString);
    printf("Last modified date: %s\n", modifiedTimeString);
    printf("Number of inode: %lu\n", fileStat.st_ino);
    printf("Number of hard links.: %lu\n", fileStat.st_nlink);

    return 0;
}
