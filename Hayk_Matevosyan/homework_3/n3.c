#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libgen.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid input for %s \n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    struct stat info;

    if (lstat(path, &info) == -1) {
        perror("stat");
        return 1;
    }

    printf("Type: ");
    if (S_ISREG(info.st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(info.st_mode)) {
        printf("directory\n");
    } else if (S_ISLNK(info.st_mode)) {
        printf("symbolic link\n");
    } else if (S_ISCHR(info.st_mode)) {
        printf("character device\n");
    } else if (S_ISBLK(info.st_mode)) {
        printf("block device\n");
    } else if (S_ISFIFO(info.st_mode)) {
        printf("FIFO/pipe\n");
    } else if (S_ISSOCK(info.st_mode)) {
        printf("socket\n");
    } else {
        printf("unknown\n");
    }

    const char *filename = basename((char *)path);
    if (filename == NULL) {
        perror("basename");
        return 1;
    }

    printf("Name: %s\n", filename);
    printf("Path: %s\n", path);
    printf("Size: %ld Bytes\n", (long)info.st_size);
    printf("Block Size: %ld Bytes\n", (long)info.st_blksize);
    printf("Number of Blocks: %zu\n", (size_t)(info.st_blocks / 8));
    printf("Access Rights: %o\n", info.st_mode & 0777);

    struct tm *ctime_info = localtime(&info.st_ctime);
    if (ctime_info == NULL) {
        perror("localtime");
        return 1;
    }

    char date_created[20], date_modified[20];

    if (strftime(date_created, sizeof(date_created), "%Y-%m-%d %H:%M:%S", ctime_info) == 0) {
        fprintf(stderr, "strftime failed\n");
        return 1;
    }

    if (strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M:%S", localtime(&info.st_mtime)) == 0) {
        fprintf(stderr, "strftime failed\n");
        return 1;
    }

    printf("Creation Time: %s\n", date_created);
    printf("Last Modification Time: %s\n", date_modified);

    printf("Inode Number: %lld\n", (long long)info.st_ino);
    printf("Number of Hard Links: %lld\n", (long long)info.st_nlink);

    return 0;
}
