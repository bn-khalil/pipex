#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    // int fd;

    // fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    // // dup2(fd,1);
    // // close(fd);
    // printf("This is printed in example.txt!\n");
    // if (access("example.txt", R_OK) != -1)
    //     printf("i have permission\n");
    // else
    //     printf("i dont have permission\n");

    // evecve
    // char *args[3];

    // args[0] = "ls";
    // args[1] = "-l";
    // args[2] = NULL;

    // execve("/bin/ls",args,NULL);
    // printf("this line will not be printed\n");

    //fork

    // pid_t pid;

    // pid = fork();
    // if (pid == -1)
    // {
    //     perror("fork");
    //     exit(EXIT_FAILURE);
    // }
    // if (pid == 0)
    //     printf("This is the child process. (pid: %d)\n", getpid());
    // else
    //     printf("This is the parent process. (pid: %d)\n", getpid());

    // pipe

    // int fds[2];

    // if (pipe(fds) < 0)
    // {
    //     perror("pipe");
    //     exit(1);
    // }
    // write(fds[1],"hello1",6);
    // write(fds[1],"hello2",6);
    // write(fds[1],"hello3",6);

    // char get[6];
    // read(fds[0],get,6);
    // printf("%s\n",get);
    // read(fds[0],get,6);
    // printf("%s\n",get);
    // read(fds[0],get,6);
    // printf("%s\n",get);

    // int fds[2];
    // pipe(fds);
    // int pid = fork();

    // if (pid == 0)
    // {
    //     char buf[3];
    //     close(fds[1]);
    //     read(fds[0],buf,3);
    //     printf("%s\n", buf);
    //     read(fds[0],buf,3);
    //     printf("%s\n", buf);
    //     int fd = open("example.txt", O_RDWR);
    //     char a[5];
    //     read(fd, a, 5);
    //     printf("%s \n", a);
    // }
    // else
    // {
    //     close(0);
    //     write(fds[1], "fin", 3);
    //     write(fds[1], "act", 3);
    // }

    // https://github.imc.re/michmos/42_pipex_tester
    
    int fd = open("test", O_RDWR);
    int fd2 = open("main", O_RDWR);
    dup2(fd, fd2);
    close(fd);
    
    
    return (0);
}