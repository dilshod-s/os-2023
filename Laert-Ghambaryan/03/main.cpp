#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    struct stat file_info;

    int fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1) {
        perror("Error");
        return 1;
    }

    if (fstat(fileDescriptor, &file_info) != 0) {
        perror("Error");
        close(fileDescriptor);
        return 1;
    }

    std::cout << "Type: ";
    if (S_ISREG(file_info.st_mode)) {
        std::cout << "Regular File" << std::endl;
    } else if (S_ISDIR(file_info.st_mode)) {
        std::cout << "Directory" << std::endl;
    } else if (S_ISLNK(file_info.st_mode)) {
        std::cout << "Symbolic Link" << std::endl;
    } else {
        std::cout << "Unknown" << std::endl;
    }

    std::cout << "Name: " << filename << std::endl;

    char permissions[10];
    snprintf(permissions, sizeof(permissions), "%o", file_info.st_mode & 0777);
    std::cout << "Permissions: " << permissions << std::endl;

    std::cout << "Size: " << file_info.st_size << " bytes" << std::endl;
    std::cout << "Block Size: " << file_info.st_blksize << " bytes" << std::endl;
    std::cout << "Number of Blocks: " << file_info.st_blocks << std::endl;

    std::cout << "Creation Time: " << std::ctime(&file_info.st_ctime);
    std::cout << "Last Modification Time: " << std::ctime(&file_info.st_mtime);
    std::cout << "Inode Number: " << file_info.st_ino << std::endl;
    std::cout << "Hard Links: " << file_info.st_nlink << std::endl;

    close(fileDescriptor);

    return 0;
}
