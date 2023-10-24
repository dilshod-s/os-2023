#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <filesystem>

void Print_Error(const char* str){
       std::cerr<<str<<'\n';
}

bool isPath_(const std::string& str)
{
    return str.find('/') != std::string::npos ;
}
int decimalToOctal(int dec)
{
    int res = 0;
    for (int i = 1; dec != 0; dec /= 8, i *= 10)
        res += (dec % 8) * i;
    return res;
}

std::string parsePermissions(mode_t decimal)
{
    int oct = decimalToOctal(static_cast<int>(decimal));

    int permissionBits[3];
    permissionBits[0] = oct/100;
    permissionBits[1] = (oct/10) % 10;
    permissionBits[2] = oct % 10;

    std::string res{};

    for (auto& bit : permissionBits)
    {
        if (bit >= 4)
        {
            bit -= 4;
            res += "r";
        }
        else
            res += "-";

        if (bit >= 2)
        {
            bit -= 2;
            res += "w";
        }
        else
            res += "-";

        if (bit >= 1)
        {
            bit -= 1;
            res += "x";
        }
        else
            res += "-";

    }

    return res;
}


void Print_File_Info(const char* str, struct stat* file_info){
      if(stat(str,file_info)==-1){
         Print_Error("stat");
         exit(1);
      }
    
    std::cout << "Type: \t\t\t";
    if (S_ISREG(file_info->st_mode))
        std::cout << "regular file\n";
    else if (S_ISDIR(file_info->st_mode))
        std::cout << "directory\n";
    else if (S_ISCHR(file_info->st_mode))
        std::cout << "character device\n";
    else if (S_ISBLK(file_info->st_mode))
        std::cout << "block device\n";
    else if (S_ISFIFO(file_info->st_mode))
        std::cout << "FIFO/pipe\n";
    else if (S_ISLNK(file_info->st_mode))
        std::cout << "symlink\n";
    else if (S_ISSOCK(file_info->st_mode))
        std::cout << "socket\n";
    else
        std::cout << "unknown file type\n";

     if (isPath_(str))
    {
        std::filesystem::path filename(str);
        filename = filename.filename();

        std::string strName(filename);
        
        std::cout << "Name: \t\t\t" << strName << "\n";
        std::cout << "Path: \t\t\t" << str << "\n";
    }
    else
    {
        std::cout << "Name: \t\t\t" << str << "\n";
        std::cout << "Path: \t\t\t" << getcwd(nullptr, 0) << "/" << str << "\n";
    }

    std::cout << "Size: \t\t\t" << file_info->st_size << " Bytes\n";
    std::cout << "Block size: \t\t" << file_info->st_blksize << " Bytes\n";
    std::cout << "Number of blocks: \t" << file_info->st_blocks/8 << "\n";
    std::cout << "Permissions: \t\t" << parsePermissions(file_info->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) << "\n";

    char date_created[20], date_modified[20];
    strftime(date_created, sizeof(date_created), "%Y-%m-%d %H:%M:%S", localtime(&file_info->st_ctime));
    strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M:%S", localtime(&file_info->st_mtime));

    std::cout << "Date created: \t\t" << date_created << "\n";
    std::cout << "Last modified: \t\t" << date_modified << "\n";

    std::cout << "Inode number: \t\t" << file_info->st_ino << "\n";
    std::cout << "Hard links count: \t" << file_info->st_nlink << "\n";

}


int main(int argc, char* argv[]){

   if(argc!= 2){
        std::cerr<<"Usage: "<<argv[0] <<" <filename>\n";
        return -1;
   }

    struct stat file_info{};

    Print_File_Info(argv[1],&file_info);   

}