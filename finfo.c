// Name, etc
// Brett Haensgen
// Lab 9 - System Calls
// Section 121
// finfo.c

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void file(mode_t mode) {
    if (S_ISREG(mode))
        printf("File type: Regular file\n");
    else if (S_ISDIR(mode))
        printf("File type: Directory\n");
    else if (S_ISLNK(mode))
        printf("File type: Symbolic link\n");
    else if (S_ISCHR(mode))
        printf("File type: Character device\n");
    else if (S_ISBLK(mode))
        printf("File type: Block device\n");
    else if (S_ISFIFO(mode))
        printf("File type: FIFO/pipe\n");
    else if (S_ISSOCK(mode))
        printf("File type: Socket\n");
    else
        printf("File type: Unknown\n");
}

void permissions(mode_t mode) {
    char perms[10];
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';

    printf("Permissions: %s\n", perms);
}


int main(int argc, char* argv[])
{
    if(argc != 2) {
        printf("No file or too many files entered\n");
        return -1;
    }

    struct stat fs;
    if(stat(argv[1], &fs) == -1) {
        printf("Error finding file info\n");
    }

    file(fs.st_mode);
    permissions(fs.st_mode);

    printf("Owner UID: %u\n", fs.st_uid);
    printf("File size: %ld bytes\n", fs.st_size);

    char buffer[100];
    struct tm *time = localtime(&fs.st_mtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time);
    printf("Last modified: %s\n", buffer);
    return 0;
}