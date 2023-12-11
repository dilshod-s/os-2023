int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 2) {
        fprintf(stderr, "Invalid input for %s\n", argv[0]);
        return 1;
    }

    const char *option = argv[1];
    int file_descriptor = 0;  // Default for option without file argument

    if (argc == 3) {
        const char *name = argv[2];
        file_descriptor = open(name, O_RDONLY);

        if (file_descriptor == -1) {
            perror("Error opening file");
            return 1;
        }
    }

    if (strcmp(option, "-l") == 0) {
        int lineCount = countLines(file_descriptor);
        printf("Number of lines%s: %d\n", (argc == 3) ? " in the file" : "", lineCount);
    } else if (strcmp(option, "-w") == 0) {
        int wordCount = countWords(file_descriptor);
        printf("Number of words%s: %d\n", (argc == 3) ? " in the file" : "", wordCount);
    } else {
        fprintf(stderr, "Invalid input for %s\n", argv[0]);
        return 1;
    }

    if (argc == 3) {
        close(file_descriptor);
    }

    return 0;
}
