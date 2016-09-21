#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //此处是读,也就是子进程把cat /etc/passwd 执行的结果放fp的缓存中
    //父进程直接从fp的缓存中就可以取出结果
    FILE *fp = popen("cat /etc/passwd","r");
    char buffer[1000];
    bzero(buffer,sizeof(buffer));
    while(fgets(buffer,sizeof(buffer),fp) != NULL)
    {
        printf("cmd result:%s\n",buffer);
    }
    //此处是写,也就是父进程的输入作为子进程执行命令(wc -l)的数据来源
    //执行结果放入标注输出
    fp = popen("wc -l","w");
    fprintf(fp,"1\n2\n3\n");
    pclose(fp);
    return 0;
}
