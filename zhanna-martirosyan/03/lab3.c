#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // для stat
#include <libgen.h> // для basename
#include <time.h> // для strftime

int main(int argc, char *argv[]) {

    if(argc != 2){ //Если аргумента не два(имя программы и полный путь к файлу), то выводит ошибку
        fprintf(stderr, "Invalid input for %s \n", argv[0]);
        return 1;
    }

    const char *path = argv[1]; // path = указатель на второй аргумент командной строки (полный путь к файлу)
    struct stat info; //структура, которая будет содержать информацию о файле

    if (lstat(path, &info) == -1) { //функция stat для получения информации о файле по пути, который указан в path
        perror("stat");
        return 1;
    }

    printf("Type: "); //дальше идет проверка типа файла
    if (S_ISREG(info.st_mode)) {
        printf("regular file\n");
    }
    else if (S_ISDIR(info.st_mode)) {
        printf("directory\n");
    }
    else if (S_ISLNK(info.st_mode)) {
        printf("symbolic link\n");
    }
    else if (S_ISCHR(info.st_mode)) {
        printf("character device\n");
    }
    else if (S_ISBLK(info.st_mode)) {
        printf("block device\n");
    }
    else if (S_ISFIFO(info.st_mode)) {
        printf("FIFO/pipe\n");
    }
    else if (S_ISSOCK(info.st_mode)) {
        printf("socket\n");

    }else{
        printf("unknown\n");
    }

    char *filename = basename((char *)path); //basename для извлечения имени файла из полного пути
    printf("Name: %s\n", filename);
    printf("Path: %s\n", path);
    printf("Size: %ld Bytes\n", (long)info.st_size);
    printf("Block Size: %ld Bytes\n", (long)info.st_blksize);
    printf("Number of Blocks: %ld\n", (long)info.st_blocks/8);
    printf("Access Rights: %o\n", info.st_mode & 0777);
    //Побитовое "И" с 0777 помогает извлечь только права доступа,
    // игнорируя другие биты, которые могут содержать доп информацию (допустим, информацию о типе файла).

    char date_created[20], date_modified[20];

    strftime(date_created, sizeof(date_created), "%Y-%m-%d %H:%M:%S", localtime(&info.st_ctime));
    strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M:%S", localtime(&info.st_mtime));
    //date_created - буфер, sizeof(date_created) - размер буфера, "%Y-%m-%d %H:%M:%S" - формат вывода,
    // localtime(&info.st_ctime) - вызов функции localtime, который конвертирует время из file_info.st_ctime
    // в локальное представление времени.

    printf("Creation Time: %s\n", date_created);
    printf("Last Modification Time: %s\n", date_modified);

    printf("Inode Number: %ld\n", (long)info.st_ino);
    printf("Number of Hard Links: %ld\n", (long)info.st_nlink);

    return 0;
}
