// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int cmpfunc (const void * a, const void * b);
int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   char uname[MAXNAME+1]; // UNCOMMENT this line
   char gname[MAXNAME+1]; // UNCOMMENT this line
   char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
   DIR *df; 
   df = opendir(dirname);
   if (df == NULL) {perror("open failed"); exit(1);}
   
   // read directory entries
   char *fileName[200];
   struct dirent *entry;
   int i = 0;
   while ((entry = readdir(df))) {
        if (entry->d_name[0] != '.') {
            fileName[i] = strdup(entry->d_name);
            i ++;
        }
   }
   qsort(fileName, i, sizeof(char *), cmpfunc);
   int j;
   char str[MAXFNAME+1];
   char buf[MAXFNAME+1];
   int rb;
   for(j = 0;j < i;j++) {
        snprintf(str, MAXFNAME+1, "%s/%s", dirname, fileName[j]);
        if (lstat(str, &info) < 0) perror("lstat failed");
        else {
            printf("%s  %-8.8s %-8.8s %8lld  ",
                rwxmode(info.st_mode, mode),
                username(info.st_uid, uname),
                groupname(info.st_gid, gname),
                (long long)info.st_size);
        }
        if (mode[0] == 'l') {
            rb = readlink(str, buf, MAXFNAME+1);
            if (rb < 0) error(errno, errno, "can't read: %s",str);
            else {
                buf[rb] = 0;
                printf("%s -> %s\n", fileName[j], buf);
            }
        } else printf("%s\n", fileName[j]);      
   }
   // finish up
   closedir(df);
   return EXIT_SUCCESS;
}

int cmpfunc (const void * a, const void * b) {
    return strcmp(*(char **)a, *(char **)b);
}
// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
   switch (mode & S_IFMT){
        case S_IFDIR: str[0] = 'd'; break;
        case S_IFLNK: str[0] = 'l'; break;
        case S_IFREG: str[0] = '-'; break;
        default: str[0] = '?'; break;
   }
   str[1] = (mode & (1<<8)) ? 'r' : '-';
   str[2] = (mode & (1<<7)) ? 'w' : '-';
   str[3] = (mode & (1<<6)) ? 'x' : '-';
   str[4] = (mode & (1<<5)) ? 'r' : '-';
   str[5] = (mode & (1<<4)) ? 'w' : '-';
   str[6] = (mode & (1<<3)) ? 'x' : '-';
   str[7] = (mode & (1<<2)) ? 'r' : '-';
   str[8] = (mode & (1<<1)) ? 'w' : '-';
   str[9] = (mode & (1<<0)) ? 'x' : '-';
   str[10] = '\0';
   return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
