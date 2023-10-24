#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <cstring>
#include <string>


std::string getFileNameFromPath(std::string filePath) {
    size_t lastSlash = filePath.find_last_of('/');
    if (lastSlash != std::string::npos) {
        return filePath.substr(lastSlash + 1);
    } else {
        // If there is no slash in the path, return the original path
        return filePath;
    }
}


std::string decimalToOctal(int decimalNumber) {
    std::string octalNumber = "";

    if (decimalNumber == 0) {
        octalNumber = "0";
    } else {
        while (decimalNumber > 0) {
            int remainder = decimalNumber % 8;
            octalNumber = std::to_string(remainder) + octalNumber;
            decimalNumber /= 8;
        }
    }

    return octalNumber;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const char* file_name = argv[1];
    struct stat file_info;

    char full_path[1024];
    if (realpath(file_name, full_path) == NULL) {
        std::cerr << "Error: Could not resolve the full path for the file." << std::endl;
        return 1;
    }

    if (stat(full_path, &file_info) != 0) {
        std::cerr << "Error: Could not retrieve file information." << std::endl;
        return 1;
    }

    std::string file_type;
    if (S_ISREG(file_info.st_mode)) {
        file_type = "Regular File";
    } else if (S_ISDIR(file_info.st_mode)) {
        file_type = "Directory";
    } else {
        file_type = "Unknown";
    }
    
    std::string name_str(file_name);
    name_str = getFileNameFromPath(name_str);
    
    std::cout << "Type: " << file_type << std::endl;
    std::cout << "Name: " << name_str << std::endl;
    std::cout << "Path: " << full_path << std::endl;
    std::cout << "Size: " << file_info.st_size << " Bytes" << std::endl;
    std::cout << "Block Size: " << file_info.st_blksize << " Bytes" << std::endl;
    std::cout << "Number of Blocks: " << file_info.st_blocks/8 << std::endl;
    std::cout << "Permissions: " << decimalToOctal(file_info.st_mode & 0777) << std::endl;
    std::cout << "Creation Date: " << std::ctime(&file_info.st_ctime);
    std::cout << "Last Modification Date: " << std::ctime(&file_info.st_mtime);
    std::cout << "Inode Number: " << file_info.st_ino << std::endl;
    std::cout << "Number of Hard Links: " << file_info.st_nlink << std::endl;

    return 0;
}
