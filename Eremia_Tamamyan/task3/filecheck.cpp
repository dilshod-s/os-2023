#include "filecheck.h"
FileInfo::FileInfo(const std::string &file_path) : file_path(file_path) {}
std::string FileInfo::permissions(const struct stat &file_info) {
  std::string permissions = "permissions : ";
  if (file_info.st_mode & S_IRUSR)
    permissions += "user r ";
  if (file_info.st_mode & S_IWUSR)
    permissions += "user w ";
  if (file_info.st_mode & S_IXUSR)
    permissions += "user x ";
  if (file_info.st_mode & S_IRGRP)
    permissions += "group r ";
  if (file_info.st_mode & S_IWGRP)
    permissions += "group w ";
  if (file_info.st_mode & S_IXGRP)
    permissions += "group x ";
  if (file_info.st_mode & S_IROTH)
    permissions += "others r ";
  if (file_info.st_mode & S_IWOTH)
    permissions += "others w ";
  if (file_info.st_mode & S_IXOTH)
    permissions += "others x ";
  if (file_info.st_mode & S_ISUID)
    permissions += "setuid ";
  if (file_info.st_mode & S_ISGID)
    permissions += "setgid ";
  if (file_info.st_mode & S_ISVTX)
    permissions += "sticky ";
  return permissions;
  permissions += '\n';
  return permissions;
}
std::string FileInfo::inode(const struct stat &file_info) {
  std::string inode = "inode: ";
  inode += std::to_string(file_info.st_ino) + "\n";
  return inode;
}
std::string FileInfo::block_size(const struct stat &file_info) {
  std::string blocksize = "blocksize: ";
  blocksize += std::to_string(file_info.st_blksize / 8) + "\n";
  return blocksize;
}
std::string FileInfo::blocks(const struct stat &file_info) {
  std::string blocks = "blocks: ";
  blocks += std::to_string(file_info.st_blocks) + "\n";
  return blocks;
}
std::string FileInfo::size(const struct stat &file_info) {
  std::string size = "size : ";
  size += std::to_string(file_info.st_size) + "\n";
  return size;
}
void FileInfo::path_and_name(const std::string &file_path) {
  std::filesystem::path filename(file_path.c_str());
  std::filesystem::path canonicalPath = std::filesystem::canonical(filename);
  filename = filename.filename();
  // convert path to string
  std::string strName(filename);
  // print results
  std::cout << "Name: \t" << strName << "\n";
  std::cout << "Canonical Path: " << canonicalPath << std::endl;
}
std::string FileInfo::create_time(const struct stat &file_info) {
  std::string creation_time = "creation time: ";

  // Форматирование времени создания
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",
           localtime(&file_info.st_ctime));
  creation_time += std::string(buffer);
  return creation_time;
}
std::string FileInfo::last_modified_time(const struct stat &file_info) {
  std::string last_modified_time = "last modified time: ";

  // Форматирование времени создания
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",
           localtime(&file_info.st_mtime));
  last_modified_time += std::string(buffer);
  return last_modified_time;
}
std::string FileInfo::hard_links_amount(const struct stat &file_info) {
  std::string hard_links_amount = "hard links amount: ";
  hard_links_amount += std::to_string(file_info.st_nlink);
  return hard_links_amount;
}
std::string FileInfo::file_type(const struct stat &file_info) {
  std::string file_type = "file type: ";
  if (S_ISDIR(file_info.st_mode))
    file_type += "directory";
  else if (S_ISCHR(file_info.st_mode))
    file_type += "character device";
  else if (S_ISBLK(file_info.st_mode))
    file_type += "block device";
  else if (S_ISREG(file_info.st_mode))
    file_type += "regular file";
  else if (S_ISFIFO(file_info.st_mode))
    file_type += "named pipe";
  else if (S_ISLNK(file_info.st_mode))
    file_type += "symbolic link";
  else if (S_ISSOCK(file_info.st_mode))
    file_type += "socket";
  else
    file_type += "unknown";
  file_type += '\n';
  return file_type;
}
void FileInfo::PrintFileInfo() {
  struct stat file_info;
  if (stat(file_path.c_str(), &file_info) == -1) {
    std::cout << "Error: File not found\n";
    exit(1);
  }
  std::cout << "File info:\n";
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << file_type(file_info);
  std::cout
      << "----------------------------------------------------------------\n";
  path_and_name(file_path);
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << size(file_info);
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << block_size(file_info);
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << blocks(file_info);
  std::cout
      << "----------------------------------------------------------------\n";

  std::cout << permissions(file_info) << '\n';
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << create_time(file_info) << '\n';
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << last_modified_time(file_info) << '\n';
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << inode(file_info) << '\n';
  std::cout
      << "----------------------------------------------------------------\n";
  std::cout << hard_links_amount(file_info) << '\n';
  std::cout
      << "----------------------------------------------------------------\n";
}