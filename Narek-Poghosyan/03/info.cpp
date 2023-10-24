#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>
#include <climits>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const char* file_path = argv[1];
    struct stat file_info;

    if (lstat(file_path, &file_info) != 0) {
        std::cerr << "Failed to get file information for " << file_path << std::endl;
        return 1;
    }

    if (S_ISLNK(file_info.st_mode)) {
        char resolved_path[PATH_MAX];
        if (realpath(file_path, resolved_path) != NULL) {
            file_path = resolved_path;
            if (stat(resolved_path, &file_info) != 0) {
                std::cerr << "Failed to get information for the target of the symbolic link." << std::endl;
                return 1;
            }
        }
    }

    std::cout << "File Type: " << (S_ISDIR(file_info.st_mode) ? "Directory" : "Regular File") << std::endl;
    std::cout << "File Name: " << file_path << std::endl;
    std::cout << "Full Path: " << realpath(file_path, nullptr) << std::endl;
    std::cout << "Size: " << file_info.st_size << " bytes" << std::endl;
    std::cout << "Block Size: " << file_info.st_blksize << " bytes" << std::endl;
    std::cout << "Number of Blocks: " << file_info.st_blocks << std::endl;
    std::cout << "Access Rights: " << (S_ISDIR(file_info.st_mode) ? "d" : "-");
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

    // Convert timestamps to human-readable format
    char created_time[20];
    char modified_time[20];
    strftime(created_time, sizeof(created_time), "%Y-%m-%d %H:%M:%S", gmtime(&file_info.st_ctime));
    strftime(modified_time, sizeof(modified_time), "%Y-%m-%d %H:%M:%S", gmtime(&file_info.st_mtime));

    std::cout << "Creation Date: " << created_time << std::endl;
    std::cout << "Last Modified Date: " << modified_time << std::endl;
    std::cout << "Inode Number: " << file_info.st_ino << std::endl;
    std::cout << "Hard Links Count: " << file_info.st_nlink << std::endl;

    return 0;
}

