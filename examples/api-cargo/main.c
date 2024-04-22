#include "/<path>/<to>/<plugin>/dataclay-plugin/dataclayplugin.h"


int main(){
    dataclay_plugin("","/<path>/<to>/<plugin>/dataclay-plugin");//If you put an alias it will remain persistent and remember the file system
    int fd2 = dataclay_open("./file.txt", O_RDWR | O_CREAT,0644);
    int fd = dataclay_open("./nom.txt", O_RDWR | O_CREAT,0644);
    char myName[512];

    int write = dataclay_pwrite(fd2,"abcde",5,3);
    printf("1st write %i\n",write);
    int read = dataclay_pread(fd2, myName, 10, 0);
    printf("Print 1st read:\n");
    for (int i = 0; i < 8; i++) {
        printf("%c", myName[i]);
    }
    printf("\n");
    write = dataclay_pwrite(fd2,"111",3,0);
    printf("2nd write %i\n",write);
    read = dataclay_pread(fd2, myName, 10, 0);
    printf("Print 2nd read: %s\n",myName);
    dataclay_close(fd);
    dataclay_close(fd2);
    return 0;
}

