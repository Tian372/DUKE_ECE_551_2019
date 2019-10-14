#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
void printfiletype(struct stat status) {
  const char * filetype = NULL;
  switch (status.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "fifo";
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
    default:
      filetype = "unknown?";
      break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         status.st_size,
         status.st_blocks,
         status.st_blksize,
         filetype);
}

void printLinks(struct stat status) {
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
         status.st_dev,
         status.st_dev,
         status.st_ino,
         status.st_nlink);
}

void printAccess(struct stat status) {
  char acc[10] = {0};
  switch (status.st_mode & S_IFMT) {
    case S_IFBLK:
      acc[0] = 'b';
      break;
    case S_IFCHR:
      acc[0] = 'c';
      break;
    case S_IFDIR:
      acc[0] = 'd';
      break;
    case S_IFIFO:
      acc[0] = 'p';
      break;
    case S_IFLNK:
      acc[0] = 'l';
      break;
    case S_IFREG:
      acc[0] = '-';
      break;
    case S_IFSOCK:
      acc[0] = 's';
      break;
  }
  switch (status.st_mode & S_IRUSR) {
    case 0:
      acc[1] = '-';
      break;
    default:
      acc[1] = 'r';
      break;
  }
  switch (status.st_mode & S_IWUSR) {
    case 0:
      acc[2] = '-';
      break;
    default:
      acc[2] = 'w';
      break;
  }
  switch (status.st_mode & S_IXUSR) {
    case 0:
      acc[3] = '-';
      break;
    default:
      acc[3] = 'x';
      break;
  }
  switch (status.st_mode & S_IRGRP) {
    case 0:
      acc[4] = '-';
      break;
    default:
      acc[4] = 'r';
      break;
  }
  switch (status.st_mode & S_IWGRP) {
    case 0:
      acc[5] = '-';
      break;
    default:
      acc[5] = 'w';
      break;
  }
  switch (status.st_mode & S_IXGRP) {
    case 0:
      acc[6] = '-';
      break;
    default:
      acc[6] = 'x';
      break;
  }
  switch (status.st_mode & S_IROTH) {
    case 0:
      acc[7] = '-';
      break;
    default:
      acc[7] = 'r';
      break;
  }
  switch (status.st_mode & S_IWOTH) {
    case 0:
      acc[8] = '-';
      break;
    default:
      acc[8] = 'w';
      break;
  }
  switch (status.st_mode & S_IXOTH) {
    case 0:
      acc[9] = '-';
      break;
    default:
      acc[9] = 'x';
      break;
  }
  printf("Access: (%04o/%s)\n", status.st_mode & ~S_IFMT, acc);
}
int main(int argc, char * argv[]) {
  struct stat status;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (argc > 2) {
    printf("too many arguments");
    exit(EXIT_FAILURE);
  }
  if ((argv[1]) == NULL) {
    return EXIT_FAILURE;
  }
  if (stat(argv[1], &status) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  const char * file = argv[1];
  printf("  File: '%s'\n", file);

  printfiletype(status);
  printLinks(status);
  printAccess(status);

  return EXIT_SUCCESS;
}
