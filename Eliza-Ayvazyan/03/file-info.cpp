#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <pwd.h>
#include <grp.h>
#include <limits.h>

void file_info(const char *filename) {
    struct stat file_info{};

    if (stat(filename, &file_info) == -1) {
        perror("stat");
        return;
    }

    if (S_ISREG(file_info.st_mode)) {
        std::cout << "Type: regular file" << std::endl;
    } else if (S_ISDIR(file_info.st_mode)) {
        std::cout << "Type: directory" << std::endl;
    } else if (S_ISCHR(file_info.st_mode)) {
        std::cout << "Type: character device" << std::endl;
    } else if (S_ISBLK(file_info.st_mode)) {
        std::cout << "Type: block device" << std::endl;
    } else if (S_ISFIFO(file_info.st_mode)) {
        std::cout << "Type: FIFO/pipe" << std::endl;
    } else if (S_ISSOCK(file_info.st_mode)) {
        std::cout << "Type: socket" << std::endl;
    } else if (S_ISLNK(file_info.st_mode)) {
        std::cout << "Type: symbolic link" << std::endl;
    } else {
        std::cout << "Type: unknown" << std::endl;
    }

    std::cout << "Name: " << filename << std::endl;

    char resolved_path[PATH_MAX];
    if (realpath(filename, resolved_path) != NULL) {
        std::cout << "Path: " << resolved_path << std::endl;
    }

    std::cout << "Size: " << file_info.st_size << " Bytes" << std::endl;

    std::cout << "Block size: " << file_info.st_blksize << " Bytes" << std::endl;

    std::cout << "Blocks: " << file_info.st_blocks << std::endl;

    std::cout << "Permissions: ";
    std::cout << ((file_info.st_mode & S_IRUSR) ? "r" : "-");
    std::cout << ((file_info.st_mode & S_IWUSR) ? "w" : "-");
    std::cout << ((file_info.st_mode & S_IXUSR) ? "x" : "-");
    std::cout << ((file_info.st_mode & S_IRGRP) ? "r" : "-");
    std::cout << ((file_info.st_mode & S_IWGRP) ? "w" : "-");
    std::cout << ((file_info.st_mode & S_IXGRP) ? "x" : "-");
    std::cout << ((file_info.st_mode & S_IROTH) ? "r" : "-");
    std::cout << ((file_info.st_mode & S_IWOTH) ? "w" : "-");
    std::cout << ((file_info.st_mode & S_IXOTH) ? "x" : "-");
    std::cout << std::endl;

    std::cout << "Created: " << ctime(&file_info.st_ctime);

    std::cout << "Last modified: " << ctime(&file_info.st_mtime);

    std::cout << "Inode number: " << file_info.st_ino << std::endl;

    std::cout << "Hard links: " << file_info.st_nlink << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    file_info(argv[1]);

    return 0;
}

