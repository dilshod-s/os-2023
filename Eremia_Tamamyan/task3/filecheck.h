#ifndef FILECHECK_H
#define FILECHECK_H

#include <ctime>
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

class FileInfo {
private:
  std::string file_path;
  std::string inode(const struct stat &file_info);
  std::string permissions(const struct stat &file_info);
  std::string blocks(const struct stat &file_info);
  std::string block_size(const struct stat &file_info);
  std::string file_type(const struct stat &file_info);
  std::string create_time(const struct stat &file_info);
  std::string last_modified_time(const struct stat &file_info);
  std::string size(const struct stat &file_info);
  void path_and_name(const std::string &file_path);
  std::string hard_links_amount(const struct stat &file_info);

public:
  FileInfo(const std::string &file_path);
  void PrintFileInfo();
};

#endif // FILECHECK_H