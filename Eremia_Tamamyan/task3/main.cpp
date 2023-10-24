
#include "filecheck.h"

int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    std::string str = "Usage: ./main <path>";
    std::cerr << str;
    return 1;
  }
  
  std::string file_path = argv[1];
  FileInfo info(file_path);
  info.PrintFileInfo();
  return 0;
}