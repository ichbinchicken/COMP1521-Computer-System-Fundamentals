#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>

int main(void)
{
    int pid;

    if ((pid = fork()) != 0) {
        int i; char c;
        setbuf(fp, NULL);
        flock(1, LOCK_EX);
        for (i = 0; i < 130; i++) {
            c = 'a' + i%26;
            fputc(c,fp);
            if (c == 'z') fputc('\n',fp);
        }
        fputc('\n',fp);
        flock(1, LOCK_UN);
    }
    else {
        int i; char c;
        setbuf(fp, NULL);
        flock(1, LOCK_EX);
        for (i = 0; i < 130; i++) {
            c = 'A' + i%26;
            fputc(c,fp);
            if (c == 'Z') fputc('\n',fp);
        }
        fputc('\n',fp);
        flock(1, LOCK_UN);
    }
    return 0;
}
