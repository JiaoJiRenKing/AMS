#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"time.h"

  

time_t StringToTime(char s[]) {
    time_t t;
    struct tm tm1 = { 0 }; // 初始化结构体为0，以避免未初始化字段的问题
    int year, mon, day, hour, min, sec;

    // 解析时间字符串
    sscanf(s, "%4d-%2d-%2d %2d:%2d:%2d", &year, &mon, &day, &hour, &min, &sec);
    tm1.tm_year = year - 1900; // 年份需减去 1900
    tm1.tm_mon = mon - 1; // 月份从0开始计数，需减去1
    tm1.tm_mday = day;
    tm1.tm_hour = hour;
    tm1.tm_min = min;
    tm1.tm_sec = sec;

    t = mktime(&tm1);
    return t;
}


