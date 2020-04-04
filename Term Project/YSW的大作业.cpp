#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100           // 字符串最大长度
#define STU_NUM 40            // 学生数量
#define COURSE_NUM 3          // 课程数
#define COURSE_MAX_LEN 100    // 课程字符串最大长度
#define ADMIN_PASSWORD 123456 // 管理员密码
typedef struct student
{
    long num;
    long password;
    char name[MAX_LEN];
    char course[COURSE_NUM][COURSE_MAX_LEN];
} STU;
STU stu[STU_NUM];
int n; // 学生数

// 学生主菜单本体
int MainMenu_Stu(STU stu[], int i)
{
    int func;
    printf("用户: %s\n", stu[i].name);
    printf("*****************************************\n");
    printf("*                主菜单                 *\n");
    printf("*                1.修改                 *\n");
    printf("*                2.查询                 *\n");
    printf("*                3.改密                 *\n");
    printf("*                4.退出                 *\n");
    printf("*****************************************\n");
    printf("请输入功能选项: ");
    while (scanf("%d", &func))
    {
        if (func >= 1 && func <= 4)
            return func;
        else
            printf("无效的数字，请重新输入: ");
    }
    return 0;
}

// 学生选课
int SubModify_Stu(STU stu[], int i)
{
    int j;
    printf("请修改你的 %d 门所选科目名称: \n", COURSE_NUM);
    for (j = 0; j < COURSE_NUM; j++)
    {
        scanf("%s", stu[i].course[j]);
    }
    printf("已修改。\n");
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 学生查询自己的课程
int SubInquire_Stu(STU stu[], int i)
{
    int j;
    printf("学号\t\t姓名\t\t");
    for (j = 0; j < COURSE_NUM; j++)
    {
        printf("课程%d\t\t", j + 1);
    }
    printf("\n%ld\t\t%s\t\t", stu[i].num, stu[i].name);
    for (j = 0; j < COURSE_NUM; j++)
    {
        printf("%s\t\t", stu[i].course[j]);
    }
    printf("\n");
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 学生修改密码
int ChangePassword_Stu(STU stu[], int i)
{
    printf("请输入新密码: ");
    scanf("%ld", &stu[i].password);
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 学生主菜单
int StuMain(STU stu[], int i)
{
    int main_swch;
    while (1)
    {
        main_swch = MainMenu_Stu(stu, i);
        if (main_swch == 1)
        {
            SubModify_Stu(stu, i);
            system("clear");
        }
        else if (main_swch == 2)
        {
            SubInquire_Stu(stu, i);
            system("clear");
        }
        else if (main_swch == 3)
        {
            ChangePassword_Stu(stu, i);
            system("clear");
        }
        else if (main_swch == 4)
        {
            printf("退出学生系统。\n");
            return 0;
        }
    }
}

// 管理员主菜单本体
int MainMenu_Admin()
{
    int func;
    printf("用户: 管理员\n");
    printf("*****************************************\n");
    printf("*                主菜单                 *\n");
    printf("*                1.输入                 *\n");
    printf("*                2.修改                 *\n");
    printf("*                3.查询                 *\n");
    printf("*                4.输出                 *\n");
    printf("*                5.文件                 *\n");
    printf("*                6.退出                 *\n");
    printf("*****************************************\n");
    printf("请输入功能选项: ");
    while (scanf("%d", &func))
    {
        if (func >= 1 && func <= 6)
            return func;
        else
            printf("无效的数字，请重新输入: ");
    }
    return 0;
}

// 管理员录入学生
int Read_Admin(STU stu[], int n)
{
    int i, j;
    printf("请输入学生的学号和姓名: \n");
    for (i = 0; i < n; i++)
    {
        scanf("%ld%s", &stu[i].num, stu[i].name);
        stu[i].password = 123456;
        for (j = 0; j < COURSE_NUM; j++)
        {
            strcpy(stu[i].course[j], "待选");
        }
    }
    printf("已录入 %d 位学生。\n", n);
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 管理员修改学生信息
int SubModify_Admin()
{
    int func;
    printf("*****************************************\n");
    printf("*                 修改                  *\n");
    printf("*                1.添加                 *\n");
    printf("*                2.删除                 *\n");
    printf("*                3.修改                 *\n");
    printf("*****************************************\n");
    printf("请输入功能选项: ");
    while (scanf("%d", &func))
    {
        if (func == 1 || func == 2 || func == 3)
            return func;
        else
            printf("无效的数字，请重新输入: ");
    }
    return 0;
}
// 管理员添加学生信息
int Add_Admin(STU stu[], int n)
{
    int i;
    if (n >= 40)
    {
        printf("人数已满，无法添加。\n");
        return n;
    }
    else
    {
        printf("请输入新增学生的学号和姓名: \n");
        scanf("%ld%s", &stu[n].num, stu[n].name);
        stu[n].password = 123456;
        for (i = 0; i < COURSE_NUM; i++)
        {
            strcpy(stu[n].course[i], "待选");
        }
        printf("已添加学号为 %ld 的学生。\n", stu[n].num);
        getchar();
        printf("按 Enter 回到主菜单。");
        getchar();
        return n + 1;
    }
}
// 管理员删除学生信息
int Delete_Admin(STU stu[], int n)
{
    int i, k;
    long num;
    printf("请输入需要删除的学号: ");
    scanf("%ld", &num);
    for (i = 0; i < n; i++)
    {
        if (num == stu[i].num) // 查找学号为 num 的学生
            break;
    }
    if (i < n)
    {
        for (k = i + 1; k < n; k++)
        {
            stu[k - 1] = stu[k]; // 将后面的学生前移一位
        }
        printf("已删除学号为 %ld 的学生。\n", num);
        getchar();
        printf("按 Enter 回到主菜单。");
        getchar();
        return n - 1; // 学生数也 -1
    }
    else
    {
        printf("该学生不存在。\n");
        getchar();
        printf("按 Enter 回到主菜单。");
        getchar();
    }
    return n;
}
// 管理员更改学生信息
int Modify_Admin(STU stu[], int n)
{
    int i, j;
    long num;
    printf("请输入待修改学生学号: ");
    scanf("%ld", &num);
    for (i = 0; i < n; i++)
    {
        if (num == stu[i].num)
            break;
    }
    if (i < n)
    {
        printf("请输入修改后");
        printf("学生的学号和姓名: \n");
        scanf("%ld%s", &stu[i].num, stu[i].name);
        for (j = 0; j < COURSE_NUM; j++)
        {
            strcpy(stu[i].course[j], "待选");
        }
        printf("已修改学号为 %ld 的学生。\n", num);
        getchar();
        printf("按 Enter 回到主菜单。");
        getchar();
    }
    else
    {
        printf("该学生不存在。\n");
        getchar();
        printf("按 Enter 回到主菜单。");
        getchar();
    }
    return 0;
}

// 管理员查询信息
int SubInquire_Admin()
{
    int func;
    printf("*****************************************\n");
    printf("*                 查询                  *\n");
    printf("*          1.按照学号进行查询           *\n");
    printf("*          2.按照姓名进行查询           *\n");
    printf("*****************************************\n");
    printf("请输入功能选项: ");
    while (scanf("%d", &func))
    {
        if (func == 1 || func == 2)
            return func;
        else
            printf("无效的数字，请重新输入: ");
    }
    return 0;
}
// 按照学号查询
int SearchNum_Admin(STU stu[], int n)
{
    long x;
    int i, k, j;
    int flag = 0;
    printf("请输入待查找学生的学号: \n");
    scanf("%ld", &x);
    for (i = 0; i < n; i++)
    {
        if (stu[i].num == x)
        {
            flag = 1;
            printf("学号\t\t姓名\t\t");
            for (k = 0; k < COURSE_NUM; k++)
            {
                printf("课程%d\t\t", k + 1);
            }
            printf("\n%ld\t\t%s\t\t", stu[i].num, stu[i].name);
            for (j = 0; j < COURSE_NUM; j++)
            {
                printf("%s\t\t", stu[i].course[j]);
            }
            printf("\n");
            break;
        }
    }
    if (flag == 0)
    {
        printf("未找到该学生。\n");
    }
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}
// 按照姓名查询
int SearchName_Admin(STU stu[], int n)
{
    char x[MAX_LEN];
    int i, j;
    int flag = 0;
    int k;
    printf("请输入待查找学生的姓名: \n");
    scanf("%s", x);
    for (i = 0; i < n; i++)
    {
        if (strcmp(stu[i].name, x) == 0)
        {
            flag = 1;
            printf("学号\t\t姓名\t\t");
            for (k = 0; k < COURSE_NUM; k++)
            {
                printf("课程%d\t\t", k + 1);
            }
            printf("\n%ld\t\t%s\t\t", stu[i].num, stu[i].name);
            for (j = 0; j < COURSE_NUM; j++)
            {
                printf("%s\t\t", stu[i].course[j]);
            }
            printf("\n");
            break;
        }
    }
    if (flag == 0)
    {
        printf("未找到该学生。\n");
    }
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 输出学生信息和选课
int Print_Admin(STU stu[], int n)
{
    int i, j;
    printf("学号\t\t姓名\t\t");
    for (i = 0; i < COURSE_NUM; i++)
    {
        printf("课程%d\t\t", i + 1);
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("%ld\t\t%s\t\t", stu[i].num, stu[i].name);
        for (j = 0; j < COURSE_NUM; j++)
        {
            printf("%s\t\t", stu[i].course[j]);
        }
        printf("\n");
    }
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}

// 文件
int SubFile_Admin()
{
    int func;
    printf("*****************************************\n");
    printf("*                 文件                  *\n");
    printf("*                1.读取                 *\n");
    printf("*                2.保存                 *\n");
    printf("*****************************************\n");
    printf("请输入功能选项: ");
    while (scanf("%d", &func))
    {
        if (func == 1 || func == 2)
            return func;
        else
            printf("无效的数字，请重新输入: ");
    }
    return 0;
}
// 读取文件
int FileLoad_Admin(STU stu[])
{
    FILE *fp;
    int i, j;
    if ((fp = fopen("student.txt", "r")) == NULL)
    {
        printf("打开 student.txt 失败。\n");
        exit(0);
    }
    for (i = 0; !feof(fp); i++)
    {
        fscanf(fp, "%ld", &stu[i].num);
        fscanf(fp, "%s", stu[i].name);
        for (j = 0; j < COURSE_NUM; j++)
            fscanf(fp, "%s", stu[i].course[j]);
        fscanf(fp, "%ld ", &stu[i].password);
        fscanf(fp, "\n");
    }
    n = i;
    fclose(fp);
    printf("文件读取成功。\n");
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}
// 保存到文件
int FileSave_Admin(STU stu[], int n)
{
    FILE *fp;
    int i, j;
    if ((fp = fopen("student.txt", "w")) == NULL)
    {
        printf("打开 student.txt 失败。\n");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%ld ", stu[i].num);
        fprintf(fp, "%s ", stu[i].name);
        for (j = 0; j < COURSE_NUM; j++)
        {
            fprintf(fp, "%s ", stu[i].course[j]);
        }
        fprintf(fp, "%ld ", stu[i].password);
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("文件保存成功。\n");
    getchar();
    printf("按 Enter 回到主菜单。");
    getchar();
    return 0;
}
// 管理员主菜单
int AdminMain(STU stu[])
{
    int main_swch, sub_swch;
    while (1)
    {
        main_swch = MainMenu_Admin();
        if (main_swch == 1)
        {
            printf("请输入学生人数 n (n < %d): ", STU_NUM);
            scanf("%d", &n);
            Read_Admin(stu, n);
            system("clear");
        }
        else if (main_swch == 2)
        {
            sub_swch = SubModify_Admin();
            if (sub_swch == 1)
            {
                n = Add_Admin(stu, n);
                system("clear");
            }
            else if (sub_swch == 2)
            {
                n = Delete_Admin(stu, n);
                system("clear");
            }
            else if (sub_swch == 3)
            {
                Modify_Admin(stu, n);
                system("clear");
            }
        }
        else if (main_swch == 3)
        {
            sub_swch = SubInquire_Admin();
            if (sub_swch == 1)
            {
                SearchNum_Admin(stu, n);
                system("clear");
            }
            else if (sub_swch == 2)
            {
                SearchName_Admin(stu, n);
                system("clear");
            }
        }
        else if (main_swch == 4)
        {
            Print_Admin(stu, n);
            system("clear");
        }
        else if (main_swch == 5)
        {
            sub_swch = SubFile_Admin();
            if (sub_swch == 1)
            {
                FileLoad_Admin(stu);
                system("clear");
            }
            else if (sub_swch == 2)
            {
                FileSave_Admin(stu, n);
                system("clear");
            }
        }
        else if (main_swch == 6)
        {
            printf("退出管理员系统。\n");
            return 0;
        }
    }
}

int main()
{
    while (1)
    {
        long id;
        int flag = 0;
        long pw;
        system("clear");
        printf("请输入账号: ");
        scanf("%ld", &id);
        printf("请输入密码: ");
        scanf("%ld", &pw);
        if (id == 0 && pw == ADMIN_PASSWORD)
        {
            system("clear");
            AdminMain(stu);
            flag = 1;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (stu[i].num == id && pw == stu[i].password)
                {
                    flag = 1;
                    system("clear");
                    StuMain(stu, i);
                    system("clear");
                    break;
                }
            }
        }
        if (flag == 0)
        {
            printf("账号或密码错误。\n");
            getchar();
            printf("按 Enter 重新输入。");
            getchar();
        }
    }
}
