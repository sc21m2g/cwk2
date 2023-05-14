#include <stdio.h>
#include <string.h>

// 每行最大长度
#define LINE_MAX 1024

// 截取子字符串
char *substring(char *dst, char *src, int start, int len)
{
    char *p = dst;
    char *q = src;
    int length = strlen(src);
    if (start >= length || start < 0)
        return NULL;
    if (len > length)
        len = length - start;
    q += start;
    while (len--)
    {
        *(p++) = *(q++);
    }
    *(p++) = '\0';
    return dst;
}

/**
 *@para   path 输入文件路径
 *@return 文件行数
 */
int read_line(char *path)
{
    FILE *fp;
    int line_num = 0;         // 文件行数
    int line_len = 0;         // 文件每行的长度
    char buf[LINE_MAX] = {0}; // 行数据缓存

    fp = fopen(path, "r");
    if (NULL == fp)
    {
        printf("open %s failed.\n", path);
        return -1;
    }

    while (fgets(buf, LINE_MAX, fp))
    {
        line_num++;
        line_len = strlen(buf);
        // 排除换行符
        if ('\n' == buf[line_len - 1])
        {
            buf[line_len - 1] = '\0';
            line_len--;
            if (0 == line_len)
            {
                // 空行
                continue;
            }
        }
        // windos文本排除回车符
        if ('\r' == buf[line_len - 1])
        {
            buf[line_len - 1] = '\0';
            line_len--;
            if (0 == line_len)
            {
                // 空行
                continue;
            }
        }
        printf("%s\n", buf);
        // 按空格分隔每行的内容
        char *segment = strtok(buf, " ");
        char *segments[100];
        int i = 0;
        while (segment != NULL)
        {
            printf("%s\n", segment);
            // 解析标签类型
            if (strstr(segment, "<"))
            {
                printf("包含<\n");
                char *type = (char *)malloc((strlen(segment) - 1) * sizeof(char));
                type = substring(type, segment, 1, strlen(segment) - 1);
                printf("type: %s\n", type);
            }
            segment = strtok(NULL, " ");
            segments[i] = segment;
            i++;
        }
        // 处理属性键值对
        // for (int i = 0; i < 100; i++)
        // {
        //     char *segment_origin = segments[i];
        //     if (segment_origin)
        //     {
        //         char *segment = (char *)malloc((strlen(segment_origin)) * sizeof(char));
        //         ;
        //         strcpy(segment, segment_origin);
        //         if (strstr(segment, "="))
        //         {
        //             char *key = strtok(segment, "=");
        //             printf("key:%s\n", key);
        //             char *value = strtok(NULL, "=");
        //             printf("value:%s\n", value);
        //         }
        //     }
        // }
    }

    if (0 == feof)
    {
        // 未读到文件末尾
        printf("fgets error\n");
        return -1;
    }
    fclose(fp);

    return line_num;
}

int main(int argc, char *argv[])
{
    int line_num = read_line("leeds.map");
    // printf("line_num = %d\n", line_num);
    return 0;
}
