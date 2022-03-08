#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

class Date
{
private:
    long long ngay;
    long long thang;
    long long nam;
    long long gio;
    long long phut;
    long long giay;
public:
    Date() //00:00:00 
    {
        gio = 0;
        phut = 0;
        giay = 0;
        ngay = 1;
        thang = 1;
        nam = 1970;
    }
    int getHour(){
        return gio;
    }

    int getMinute(){
        return phut;
    }

    int getSecond(){
        return giay;
    }

    int getDay(){
        return ngay;
    }

    int getMonth(){
        return thang;
    }

    int getYear(){
        return nam;
    }

    void setDate(int day, int month, int year); //Thiet lap ngay thang nam
    void setTime(int hour,int minute, int second);
    void addMinute(int minute); //Chi dung de tang giam phut phuc vu viec dat phong
    void setDateNow(); //Thiet lap gio phut giay ngay thang nam theo dong ho may tinh
    string Now(); //Tra ve thoi gian ngay thang nam hien tai cua dong ho, ho tro cho ham setDateNow()
    string getGeneralDate(); //Tra ve thang ngay gio:phut:giay nam
    string getDate(); //Tra ve thang ngay nam
    string getTime();
    bool isLeapYear(int year); //Ham dung de kiem tra nam nhuan ho, ho tro ham setDate
    int compWithDate(Date date); //so sanh 2 ngay
    int compWith3Month(); // so sánh date thuộc quý nào
};

void Date::setTime(int hour,int minute, int second)
{
    //Viet thiet lap thoi gian khong lam anh huong den thiet lap ngay thang nam
    //Kiem soat du lieu dua vao phai la 1 so nguyen
    if(hour < 0)
        hour = -hour;
    if(minute < 0)
        minute = -minute;
    if(second < 0)
        second = -second;
    
    //Thiet lap thoi gian nham kiem soat du lieu dua vao phai hop le
    //Dong thoi kiem soat du lieu dua vao
    //Gio chi nhan toi da gia tri 23
    //Phut chi nhan toi da gia tri 59 
    //Giay chi nhan toi da gia tri 59
    if(hour > 24) //Neu gia tri hour dua vao la 1 so lon hon 24 thi tu dong thiet lap lai la 23 gio
        gio = 23;
    else if(hour == 24) //24h = 0h
        gio = 0;
    else
        gio = hour;
    
    if(minute > 60)
        phut = 59;
    else if(minute == 60) //60 phut thi thiet lap lai la 0 phut
        phut = 0;
    else
        phut = minute;

    if(second > 60)
        giay = 59;
    else if(second == 60)
        giay = 0;
    else
        giay = second; 
}

void Date::addMinute(int minute) 
{
    //Kiem soat gia tri dua vao  
    if(minute <= 0)
        return;

    //Thuc hien tang so phut
    if(minute > 0)
    {
        minute = minute + phut;
        phut = minute % 60;
        gio = gio + minute / 60;
        ngay = ngay + gio / 24;
        gio = gio % 24;
        bool flag = false; //Kiem soat viec thoat khoi vong lap
        while(true)
        {
            switch(thang)
            {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    if(ngay > 31)
                    {
                        ++thang; //Tang so thang len;
                        ngay = ngay - 31; //Giam bot so ngay bi du di
                    }
                    else
                        flag = true; //Ngay hop le co the thoat khoi vong lap
                    break;
                case 4: case 6: case 9: case 11:
                    if(ngay > 30)
                    {
                        ++thang;
                        ngay = ngay - 30;
                    }
                    else
                        flag = true; //Ngay hop le co the thoat khoi vong lap
                    break;
                case 2:
                    if(isLeapYear(nam)) //kiem tra nam nhuan
                    {
                        if(ngay > 29)
                        {
                            ++thang;
                            ngay = ngay - 29;
                        }
                        else
                            flag = true;
                    }
                    else
                    {
                        if(ngay > 28)
                        {
                            ++thang;
                            ngay = ngay - 28;
                        }
                        else
                            flag = true;
                    }
                    break;
            }
            //sau khi thuc hien viec tang thang len thi phai thay doi cho thang tro nen hop le
            //Dong thoi tang nam len
            if(thang > 12) 
            {
                ++nam;
                thang = thang - 12;
                flag = false; //Thang chua hop le thuc hien kiem soat lai
            }

            if(flag)
                break; //Ngay thang nam da hop le thuc hien break;
        }
    }
}

bool Date::isLeapYear(int year) 
{ 
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) 
        return true;
    return false; 
} 

void Date::setDate(int day, int month, int year)
{
    //Thiet lap ngay thang nam chi nhan gia tri dung, neu gia tri sai se khong nhan
    if(year >= 1900) //Moc thoi gian toi thieu la 1900
        nam = year;
    if(month > 0 && month <= 12)
        thang = month;
    if(day > 0 && day <= 31)
    {
        if(month == 2) //Trong truong hop month = 2 thi kiem tra nam nhuan
        {
            if(isLeapYear(year) && day <= 29)
                ngay = day;
            else if(day <= 28)
                ngay = day;
        }
        else
            ngay = day;
    }
}

void Date::setDateNow() //Thiet lap gio phut giay ngay thang nam theo dong ho may tinh
{
    //Thiet lap lai toan bo thoi gian theo cot moc
    // 1/1/1970 00:00:00 UTC (gio quoc te)
    giay = 0;
    phut = 0;
    gio = 0;
    ngay = 1;
    thang = 1;
    nam = 1970;
    time_t currentTime = time(0); //Lay so giay tinh tu thoi diem 1/1/1970 00:00:00 den hien tai
    giay = currentTime % 60;
    int minute = currentTime / 60;
    addMinute(minute + 420); //Do gio Viet Nam lech gio quoc te +7
}

string Date::getGeneralDate()
{
    string date = getDate() + " ";;
    string time = getTime();
    date += time;
    return date;
}

string Date::getDate()
{
    string date;
    if(ngay < 10)
        date += "0" + to_string(ngay) + "/";
    else
        date += to_string(ngay) + "/";
    if(thang < 10)
        date += "0" + to_string(thang) + "/";
    else
        date += to_string(thang) + "/";
    date += to_string(nam);
    return date;
}

string Date::getTime()
{
    string time;
    if(gio < 10) //Khong co 2 chu so
        time += "0" + to_string(gio) + ":";
    else
        time += to_string(gio) + ":";
    
    if(phut < 10)
        time += "0" + to_string(phut) + ":";
    else
        time += to_string(phut) + ":";

    if(giay < 10)
        time += "0" + to_string(giay);
    else 
        time += to_string(giay);
    return time;
}

int Date::compWithDate(Date date)
{
    //quy doi ngay thang nam thanh giay
    if (this->nam == date.nam)
    {
        if (this->thang == date.thang)
        {
            if (this->ngay == date.ngay)
            {
                return 0; //2 ngày bằng nhau
            }
            else if ((this->ngay - date.ngay) > 0)
            {
                return 1; // this lớn hơn date
            }
            else
            {
                return -1; // this nhỏ hơn date
            }
        }
        else if ((this->thang - date.thang) > 0)
        {
            return 1; // this lớn hơn date
        }
        else
        {
            return -1; //this nhỏ hơn date
        }
    }
    else if ((this->nam - date.nam) > 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int Date::compWith3Month()
{
    if (this->thang == 1 || this->thang == 2 || this->thang == 3)
    {
        return 1;
    }
    if (this->thang == 4 || this->thang == 5 || this->thang == 6)
    {
        return 2;
    }
    if (this->thang == 7 || this->thang == 8 || this->thang == 9)
    {
        return 3;
    }
    if (this->thang == 10 || this->thang == 11 || this->thang == 12)
    {
        return 4;
    }
    return 0;
}