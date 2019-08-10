//����һ��ʱ�䣬�����һ���ʱ�䡣
//��������2008��2��28��23ʱ59��59�룬
//���Ϊ��2008��2��29��0ʱ0��0�롣
//����һ��ʱ�䣬�����һ���ʱ�䡣
//��������2008��2��28��23ʱ59��59�룬
//���Ϊ��2008��2��29��0ʱ0��0�롣
//#include "stdafx.h"
#include "stdio.h"
#include "iostream"
using namespace std;
// �������ܺ�����������������÷�ʽ��ţ����������ڲ��Ժ���main�����ӡ�����


void nextsecond(int & year, int & month, int & day, int & hour, int & minute, int & second)
{ 
	//  ÿ���µķֱ��Ӧ������
	int DayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};  
      // ������벻��ȷ��ʱ��ᱨ����������������
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
			return;    //������벻��ȷ������ʱ�䲻��ȷ�����ء�
		}

	// ���������Ļ���2�·���29�죬�������������顣
	if(0 == year % 4 && 0 != year / 400)
	{
		DayOfMonth[1] = 29;
	}

	 // ����һ��֮��������ں�ʱ��ĸ���
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
     // ���弸������������ں�ʱ�䡣
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

// ����ʱ�䣬����ʱ���1�룬���ͨ���������ء��ɹ�����0��ʧ�ܷ���-1
int ResetTime(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
    // ���ָ���Ƿ���Ч
    if(NULL == year || NULL == month || NULL == day || NULL == hour || NULL == minute || NULL == second)
    {
        return -1;
    }

    // ��������Ƿ�Ϸ�
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

    // ÿ���������飬��ʱ��������
    int dayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // ����������������
    if(0 == (*year % 400) || (0 == *year %4 && 0 != *year % 100))
    {
        dayOfMonth[1] = 29;
    }

    // ִ��������1����
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
     // ���弸������������ں�ʱ�䡣
	int a = 2400, b =2 , c=29, d=23, e=59, f=59;
	int result = -1;
	cout << "input:year month  day  hour  minute  second" << endl;
	result = ResetTime(&a,&b,&c,&d,&e,&f); 
	cout <<result<< endl;
	cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
	
	return 0;
}

