#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
std::string city="Sarajevo";
std::string file1="cities/Sarajevo.txt";
std::string file2="cities/SarajevoLeapYear.txt";

class Hour
{
    int hours, minutes, seconds;
    static const int dan = 86400; // number of seconds
public:
    Hour();
    Hour(int hours, int minutes, int seconds);
    void SetNormalized(int hours, int minutes, int seconds);
    int GetHours() const;
    int Getminutess() const;
    int GetSeconds() const;
    friend Hour &operator++(Hour &hour);
    friend Hour operator++(Hour &hour, int);
    friend Hour &operator--(Hour &hour);
    friend Hour operator--(Hour &hour, int);
    friend Hour operator+(Hour &hour, int sec);
    friend Hour operator-(Hour &hour, int sec);
    friend Hour operator+=(Hour &hour, int sec);
    friend Hour operator-=(Hour &hour, int sec);
    friend int operator-(const Hour &hour1, const Hour &hour2);
    friend std::ostream &operator<<(std::ostream &tok, const Hour&hour);
};

void Hour::SetNormalized(int hours, int minutes, int seconds)
{
    int temp = hours * 3600 + minutes * 60 + seconds;
    if (temp >= dan)
        temp = temp % dan; // if we 'overshot' the day
    if (temp < 0)
        temp = dan + temp % dan; // in case we have a negative shift (time)
    this->hours = temp / 3600;
    this->minutes = (temp % 3600) / 60;
    this->seconds = temp % 60;
}
Hour::Hour() : hours(0), minutes(0), seconds(0) {}
Hour::Hour(int hours, int minutes, int seconds)
    : hours(hours), minutes(minutes), seconds(seconds)
{
    SetNormalized(hours, minutes, seconds);
}

int Hour::GetHours() const
{
    return hours;
}
int Hour::Getminutess() const
{
    return minutes;
}
int Hour::GetSeconds() const
{
    return seconds;
}


int operator-(const Hour &hour1, const Hour &hour2)
{
    int time1 = hour1.GetHours() * 3600 + hour1.Getminutess() * 60 + hour1.GetSeconds();
    int time2 = hour2.GetHours() * 3600 + hour2.Getminutess() * 60 + hour2.GetSeconds();
    return time1 - time2;
}

Hour operator +(Hour &hour1, int sec)
{
    Hour Hour2(hour1.hours, hour1.minutes, hour1.seconds + sec);
    return Hour2;
}
Hour operator -(Hour &hour, int sec)
{
    Hour hour2(hour.hours, hour.minutes, hour.seconds - sec);
    return hour2;
}
Hour operator+=(Hour &hour, int sec)
{
    hour.seconds += sec;
    hour.SetNormalized(hour.hours, hour.minutes, hour.seconds);
    return hour;
}
Hour operator-=(Hour &hour, int sec)
{
    hour.seconds -= sec;
    hour.SetNormalized(hour.hours, hour.minutes, hour.seconds);
    return hour;
}
std::ostream &operator<<(std::ostream &tok, const Hour&hour)
{
    tok << std::setw(2) << std::setfill('0') << hour.hours << ":";
    tok << std::setw(2) << std::setfill('0') << hour.minutes ;
    return tok;
}

bool checkYear(int year)
{
    // If a year is multiple of 400,
    // then it is a leap year
    if (year % 400 == 0)
        return true;

    // Else If a year is multiple of 100,
    // then it is not a leap year
    if (year % 100 == 0)
        return false;

    // Else If a year is multiple of 4,
    // then it is a leap year
    if (year % 4 == 0)
        return true;
    return false;
}

int mainIZ(int namaz);

int main()
{

    // Date
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string s=std::ctime(&start_time);
    std::string monthDay=s.substr(4,6);
    std::string year=s.substr(20,18);
    std::string fullDate=monthDay+" "+year;
    std::string today_date=s.substr(4,6);

    std::cout<<"PRAYER TIMES 14.6"<<std::endl;
    std::cout<<city<<std::endl;
    std::cout<<fullDate;
    std::cout<<"-----------------------"<<std::endl;

    // Leap year check
    std::string file=file1;
    if(checkYear(std::stoi(year)))
        file=file2;

    std::ifstream in(file);
    std::ofstream out("yearlyPrayer.txt");
    std::string line,date;
    // First line2 is Jan 02, the rest line2 are stored as last line
    std::string line2="Jan 02 06:01 07:06 12:26 15:25 17:45 18:51";
    std::string fajr,sunrise,dhuhr,asr,maghrib,isha;
    Hour half,lastThird;

    out<<city<<" Prayer Times 14.6 Angle "<<year;

    int i=0;
    while (std::getline(in, line))
    {
        date=line.substr(0,6);
        fajr=line.substr(7,5);
        sunrise=(line.substr(9,9)).substr(4,6);
        dhuhr=(line.substr(11,13)).substr(8,10);
        asr=(line.substr(14,16)).substr(11);
        maghrib=(line.substr(18,18)).substr(13);
        isha=(line.substr(22,22)).substr(15);


        // Half, last third
        int h1,h2,m1,m2;
        h1=std::stoi(maghrib.substr(0,2));
        m1=std::stoi(maghrib.substr(3,5));
        std::string fajrNext=line2.substr(7,5);
        h2=std::stoi(fajrNext.substr(0,2));
        m2=std::stoi(fajrNext.substr(3,5));
        Hour s1(h1, m1, 0);
        Hour s2(h2, m2, 0);
        Hour s(0, 0, 0);
        Hour ss = s2;
        int sum1 = h1 * 3600 + m1 * 60;
        s -= sum1;
        int sum2 = s.GetHours() * 3600 + s.Getminutess() * 60 + s.GetSeconds();
        ss += sum2;
        int sum3 = ss.GetHours() * 3600 + ss.Getminutess() * 60 + ss.GetSeconds();
        Hour half = s1, lastThird = s1;
        half += (sum3 / 2);
        lastThird += 2 * (sum3 / 3);
        if(date==today_date)
        {
            std::cout<<"Fajr: "<<fajr<<std::endl;
            std::cout<<"Sunrise: "<<sunrise<<std::endl;
            std::cout<<"Dhuhr: "<<dhuhr<<std::endl;
            std::cout<<"Asr: "<<asr<<std::endl;
            std::cout<<"Maghrib: "<<maghrib<<std::endl;
            std::cout<<"Isha: "<<isha<<std::endl;
            std::cout<<"Midnight: "<<std::setw(16)<<half<<std::endl;
            std::cout<<"Last third: "<<std::setw(16)<<lastThird<<std::endl;
        }
        line2=line;
        out<<date<<" "<<fajr<<" "<<sunrise<<" "<<dhuhr<<" "<<asr<<" "<<maghrib<<" "<<isha<<" "<<half<<" "<<lastThird<<"\n";
    }
    in.close();
    out.close();

    std::string c;
    for(;;){
        std::cout<<std::endl<<"Finish y/n: ";
    std::cin>>c;
           if(c=="y"||c=="Y"||c=="n"||c=="N")
            break;
    }


    return 0;
}


