#include "WordCount.h"
 
WordCount::WordCount() : word_c(0), line_c(0), countwords(false),
                         countlines(false), input(false), file{} {}
 
 bool WordCount::isFlag(const char *str)
{
    if (str[0] == '-' && str[1] == 'w' && str[2] == '\0')
        countwords = true;
    else if (str[0] == '-' && str[1] == 'l' && str[2] == '\0')
        countlines = true;
    else
    	return false;
    return true;
}

bool WordCount::isTxT(const char *inputed_file)
{
    std:::size_t i = 0;
    while (inputed_file[i] != '\0')
    	++i;
    if (i <= 4)
        return false;
 
    if (inputed_file[i-4] == '.'  && inputed_file[i-3] == 't' && inputed_file[i-2] == 'x'     && inputed_file[i-1] == 't')
        {
    	   std::string copy(inputed_file);
    	   file = copy;
    	   return true;
        }
    return false;
    
}
 

 
void WordCount::count()
{
    int fd = 0;
    
    if(input)
    {
   	const char* cstr = file.c_str();
    	fd = open(cstrFileName, O_RDONLY);
    	if (fd == -1)
   	 {
        	std::cerr << "Error opening file: " << fileName << std::endl;
       		exit(1);
    	 }
    }
    char buffer[1024];
    int bytesRead;
 
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
        for (int i = 0; i < bytesRead; ++i)
            if (buffer[i] == '\n')
                ++line_c;
            else  if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                ++word_c;
 
    if(input) 
	   {
	 	if (bytesRead == -1)
	    	{
		  std::cerr << "Error reading file. Exiting...\n";
		 exit(1);
		}
		
		close(fd)
	  }	
    
}

int WordCount::Prestart(int argc, char *argv[])
{ 
    // example: ./wordcount (< file.txt)
    if (argc == 1)
    {
        countlines = true;
        countwords = true;
        return 0;
    }
    // example: ./wordcount sample.txt
    // or     : ./wordcount -l (< file.txt)
    if (argc == 2)
    {
        // If a flag, parse. Else check if a filename and set input type. Otherwise, invalid argument passed.
        if (isFlag(argv[1]))
            return 0;
        else if (isTxt(argv[1]))
        {
            input = true;
            countlines = true;
            countwords = true;
            return 0;
        }
        else
            return 1;
    }
 
    // example: /wordcount -w sample.txt
    if (argc == 3)
    {
        if (!isFlag(argv[1]))
            return 1;
 
        if (isTxt(argv[2]))
        {
            input = true;
            return 0;
        }
        else
            return 1;
    }
 
    return 1;
}
void WordCount::print()
{
    std::string message{};
 
    if (countwords)
        message += "Word count: " + std::to_string(word_c) + "\n";
 
    if (countlines)
        message += "Line count: " + std::to_string(line_c) + "\n";
 
    const char* cstrMessage = message.c_str();
    write(STDOUT_FILENO, cstrMessage, message.length());
}
