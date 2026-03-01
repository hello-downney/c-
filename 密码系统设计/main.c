/*
密码系统设计思路：

1.设置密码
2.查询密码
3.修改密码
4.退出
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
void blsz(char *shuzu);                   // 遍历数组
void qingling(char *shuzu);               // 清零数组
void shezhimm(char *my_mm, char **qishi); // 设置密码函数    同时是修改密码函数
void chaxunmm(char *my_mm);               // 查询密码函数

int bianlishuzu(char *shuzu); // 数数组元素个数
void clear_input_buffer();    // 确保一次只读一个字符，针对getch，后续键盘缓冲区的丢弃

int main(void)
{
    char my_mm[16] = {0};
    char my_mm_cpy[16] = {0}; // 校验my_mm是否被修改
    int option;
    int test;
    while (1)
    {

        char mm_len[16] = {0};
        char *p = mm_len;
        char **qishi = &p;
        option = 0;
        puts("\n输入1：设置密码\n输入2：查询密码\n输入3：修改密码\n输入4：退出");
        scanf_s("%d", &option);
        test = memcmp(my_mm_cpy, my_mm, 15); // 校验两个数组是否相等，判断my_mm有没有被修改,test!=0就是被修改，test=0就是没修改
        if (option == 1 || option == 2 || option == 3 || option == 4)
        {
            switch (option)
            {
            case 1:
                if (test == 0)
                {
                    shezhimm(my_mm, qishi);
                    printf("你的密码是：\n");
                    blsz(*qishi);
                }
                else
                {
                    puts("你已设置密码");
                }
                break;

            case 2:

                if (test != 0)
                {
                    chaxunmm(my_mm);
                }
                else
                {
                    puts("你未设置密码");
                }
                break;

            case 3:
                if (test == 0)
                {
                    puts("你未设置密码");
                }
                else
                {
                    puts("默认通过人脸识别");
                    shezhimm(my_mm, qishi);
                    printf("你的密码是：\n");
                    blsz(*qishi);
                }

                break;

            case 4:
                printf("你已退出");
                return 0;
            }
        }
        else
        {
            while (getchar() != '\n')
                ; // 清空缓冲区
            continue;
        }
    }
}

void shezhimm(char *my_mm, char **qishi)
{
    puts("设置密码，6-15位");

    char ch;
    int i;

    for (i = 0; i < 15;)
    {
        ch = _getch();

        // 功能键检测
        if (ch == -32 || ch == 224)
        {
            // 功能键，读取第二个字节并忽略
            printf("\n请输入有效字符（可见字符）\n");
            clear_input_buffer();
            //_getch(); // 读取并丢弃第二个字节
            // printf("\n");      // 换行提示
            blsz(*qishi); // 显示当前密码
            continue;     // 不计数，继续循环
        }
        else if (ch == 13)
        { // 按下回车键

            if (i < 6)
            {
                // puts("\n设置密码，6-15位");
                puts("\n密码不足6位");
                qingling(*qishi);
                i = 0;
                continue;
            }

            else
            {
                memcpy(my_mm, *qishi, 15);
                printf("\n设置成功,密码已经自动保存密码,共设置%d位\n", bianlishuzu(*qishi));
                (*qishi)[i] = '\0';
                // qingling(*qishi);
                return;
            }
        }

        else if (ch >= 32 && ch <= 126) // 32是空格，看需求要不要包含
        {                               // 仅仅输入可见字符

            (*qishi)[i] = ch;
            printf("%c", (*qishi)[i]);
        }
        else if (ch == 8) // 处理退格键
        {
            if (i > 0)
            {
                printf("\b \b"); // 视觉上退格

                i--; // 逻辑上退格
                (*qishi)[i] = 0;
                // i--
            }

            continue;
        }

        else // 防止用户输入了其他字符
        {
            /*   while (getchar() != '\n')
                   ;*/
            clear_input_buffer(); // 一次只读一个字符
            printf("\n请输入在ASCII范围里的有效字符\n");
            blsz(*qishi);
            // qingling(*qishi);
            // shezhimm(*qishi, qishi);
            // i = 0;
            continue;
        }
        i++;
    }

    if (i == 15)
    {
        qingling(*qishi);
        puts("\n输入达到最大上限,请重新输入");
        // qingling(*qishi);
        shezhimm(*qishi, qishi);
    }

    return;
}

void chaxunmm(char *my_mm)
{
    puts("查询密码成功，你的密码是：");
    blsz(my_mm);
}

void qingling(char *shuzu)
{
    for (int i = 0; i < 15; i++)
    {
        shuzu[i] = 0;
    }
}

int bianlishuzu(char *shuzu)
{
    int total_num;
    total_num = strlen(shuzu);
    return total_num;
}

void blsz(char *shuzu)
{
    int k = 0;
    while (shuzu[k] != '\0')
    {
        printf("%c", shuzu[k]);
        k++;
    }
}

void clear_input_buffer() // 清空键盘缓冲区，确保一次只读一个字符，针对getch，后续键盘缓冲区的丢弃
{
    while (_kbhit()) // _kbhit()函数，有按键被按下，它会返回一个非零值，否则返回0。这是一个非阻塞函数
    {
        _getch(); // 读取并丢弃，这是一个阻塞函数，不按下就一直卡在这里
    }
}
