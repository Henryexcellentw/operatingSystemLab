#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int readNum, m = 0;
    char *argArray[32];
    char readBuffer[32];
    char argBuffer[32];
    int point = 0;
    char *head = argBuffer;
    for (int i = 1; i < argc; i++)
    { // 从第二个参数开始，把已经有的参数放到argArray中
        argArray[point] = argv[i];
        point++;
    }
    while (readNum = read(0, readBuffer, sizeof(readBuffer)))
    {
        if (readNum == 0) // 如果读到输入末尾，就退出
            break;
        for (int i = 0; i < readNum; i++)
        {
            if (readBuffer[i] == '\n')
            { // 如果是换行符,说明这行的参数读完了
                argBuffer[m] = '\0';
                argArray[point] = head;
                point++;
                argArray[point] = '\0';
                m = 0;            // 重新记录参数的长度
                head = argBuffer; // 重置head和point
                point = argc - 1;
                if (fork() == 0)
                { // 创建子进程执行命令
                    exec(argv[1], argArray);
                }
                wait(0);
            }
            else if (readBuffer[i] == ' ')
            {
                argBuffer[m++] = '\0';    // 如果是空格把commandBuffer填0
                argArray[point++] = head; // 将这个参数加入到argArray中
                head = &argBuffer[m];     // 让head指向下一个参数的开头
            }
            else
            { // 如果不是空格也不是换行符，就把当前字符放入commandBuffer中
                argBuffer[m++] = readBuffer[i];
            }
        }
    }
    exit(0);
}