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

    char* full_path = realpath(filename, NULL);
    std::cout << "Full Path: " << (full_path ? full_path : "Error retrieving path") << std::endl;
    free(full_path);
    
    std::cout << "Type: " << (S_ISREG(file_info.st_mode) ? "File" : (S_ISDIR(file_info.st_mode) ? "Directory" : "Unknown")) << std::endl;
    std::cout << "Name: " << filename << std::endl;

    std::cout << "Size: " << file_info.st_size << " bytes" << std::endl;
    std::cout << "Block Size: " << file_info.st_blksize << " bytes" << std::endl;
    std::cout << "Number of Blocks: " << file_info.st_blocks / 8 << std::endl;


    std::cout << "Permissions: " << std::oct << (file_info.st_mode & 0777) << std::dec << std::endl;

    std::cout << "Creation Time: " << std::ctime(&file_info.st_ctime);
    std::cout << "Last Modification Time: " << std::ctime(&file_info.st_mtime);
    std::cout << "Inode Number: " << file_info.st_ino << std::endl;
    std::cout << "Hard Links: " << file_info.st_nlink << std::endl;

    close(fileDescriptor);

    return 0;
}
