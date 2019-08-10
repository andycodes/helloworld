//输入一个时间，输出下一秒的时间。
//例如输入2008年2月28日23时59分59秒，
//输出为：2008年2月29日0时0分0秒。
//输入一个时间，输出下一秒的时间。
//例如输入2008年2月28日23时59分59秒，
//输出为：2008年2月29日0时0分0秒。
//#include "stdafx.h"
#include "stdio.h"
#include "iostream"
using namespace std;
// 声明功能函数，输入变量以引用方式存放，这样方便在测试函数main里面打印输出。


void nextsecond(int & year, int & month, int & day, int & hour, int & minute, int & second)
{ 
	//  每个月的分别对应的天数
	int DayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};  
      // 如果输入不正确的时间会报错，请求你重新输入
	if(second >= 60                                                
		|| minute >= 60
		|| hour >= 24
		|| day > 28 && month == 2 && (0 != year % 4 || 0 == year / 400)
		|| day > 29 && month == 2 && (0 == year % 4 && 0 != year /400)
		|| day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)
		|| day > 31 && (month == 1 || month == 3 || month == 5 || month == 7)
		|| month > 12
		|| second <= 0
		|| minute <= 0
		|| hour <= 0
		|| day <= 0
		|| month <= 0)
		{
			cout << "please input correct time:" << endl;
			year = month = day = hour = minute = second = 0;
			return;    //如果输入不正确的日期时间不正确，返回。
		}

	// 如果是闰年的话，2月份是29天，这里修正了数组。
	if(0 == year % 4 && 0 != year / 400)
	{
		DayOfMonth[1] = 29;
	}

	 // 增加一秒之后，完成日期和时间的更新
	second += 1;     
	if(second == 60)                                 
	{
		second = 0;
		minute += 1;
		if(minute == 60)
		{
			minute = 0;
			hour += 1;
			if(hour == 24)
			{
				hour = 0;
				day += 1;
				if(day > DayOfMonth[month-1])
				{
					day = 1;
					month += 1;
					if(month == 13)
					{
						month = 1;
						year += 1;
					}
				}
			}
		}
	}
}

#if 0
int main( void )
{
     // 定义几个变量存放日期和时间。
	int a, b, c, d, e, f;
	cout << "input:year month  day  hour  minute  second" << endl;
	while(1)
		{
			cin >> a;
			cin >> b;
			cin >> c >> d >> e >> f;
			nextsecond(a,b,c,d,e,f); 
			cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
		}
	return 0;
}

#endif

// 输入时间，将该时间加1秒，结果通过参数返回。成功返回0，失败返回-1
int ResetTime(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
    // 检查指针是否有效
    if(NULL == year || NULL == month || NULL == day || NULL == hour || NULL == minute || NULL == second)
    {
        return -1;
    }

    // 检查日期是否合法
    if(*year < 0 || *month < 1 || *month > 12 || *day < 1 || *day > 31 ||
       *hour < 0 || *hour > 23 || *minute < 0 || *minute > 59 || *second < 0 || *second > 59)
    {
       return -1;
    }
	
    if(*month == 2 || *month == 4 || *month == 6 || *month == 9 || *month == 11)
    {
        if(*day > 30)
        {
            return -1;
        }
    }
	
    if(0 == (*year % 400) || (0 == *year %4 && 0 != *year % 100))
    {
        if(*day > 29 && (2 == *month))
        {
            return -1;
        }
    }
    else
    {
        if(*day > 28 && (2 == *month))
        {
            return -1;
        }
    }

    // 每月天数数组，暂时按非闰年
    int dayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // 如果是闰年更新数组
    if(0 == (*year % 400) || (0 == *year %4 && 0 != *year % 100))
    {
        dayOfMonth[1] = 29;
    }

    // 执行秒数加1计算
    *second += 1;
    if(*second >=60)
    {
        *second = 0;
        *minute += 1;
		
        if(*minute >= 60)
        {
            *minute = 0;
            *hour += 1;
			
            if(*hour >= 24)
            {
                *hour = 0;
                *day += 1;
				
                if(*day > dayOfMonth[*month -1])
                {
                    *day = 1;
                    *month += 1;
					
                    if(*month > 12)
                    {
                        *month =1;
                        *year += 1;
                    }
                }
            }
        }
    }

   return 0;
}


int main( void )
{
     // 定义几个变量存放日期和时间。
	int a = 2400, b =2 , c=29, d=23, e=59, f=59;
	int result = -1;
	cout << "input:year month  day  hour  minute  second" << endl;
	result = ResetTime(&a,&b,&c,&d,&e,&f); 
	cout <<result<< endl;
	cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
	
	return 0;
}

