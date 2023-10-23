#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
std::string city="Medina";
std::string file1="cities/Medina.txt";
std::string file2="cities/MedinaLeapYear.txt";

class Sat
{
    int sati, minute, sekunde;
    static const int dan = 86400; // broj sekundi
public:
    Sat();
    Sat(int sati, int minute, int sekunde);
    void PostaviNormalizirano(int sati, int minute, int sekunde);
    int DajSate() const;
    int DajMinute() const;
    int DajSekunde() const;
    friend Sat &operator++(Sat &sat);
    friend Sat operator++(Sat &sat, int);
    friend Sat &operator--(Sat &sat);
    friend Sat operator--(Sat &sat, int);
    friend Sat operator+(Sat &sat, int sek);
    friend Sat operator-(Sat &sat, int sek);
    friend Sat operator+=(Sat &sat, int sek);
    friend Sat operator-=(Sat &sat, int sek);
    friend int operator-(const Sat &sat1, const Sat &sat2);
    friend std::ostream &operator<<(std::ostream &tok, const Sat&sat);
};

void Sat::PostaviNormalizirano(int sati, int minute, int sekunde)
{
    int temp = sati * 3600 + minute * 60 + sekunde;
    if (temp >= dan)
        temp = temp % dan; // ako smo 'prekoracili' dan
    if (temp < 0)
        temp = dan + temp % dan; // u slucaju da imamo negativan pomak (vrijeme)
    this->sati = temp / 3600;
    this->minute = (temp % 3600) / 60;
    this->sekunde = temp % 60;
}
Sat::Sat() : sati(0), minute(0), sekunde(0) {}
Sat::Sat(int sati, int minute, int sekunde)
    : sati(sati), minute(minute), sekunde(sekunde)
{
    PostaviNormalizirano(sati, minute, sekunde);
}

int Sat::DajSate() const
{
    return sati;
}
int Sat::DajMinute() const
{
    return minute;
}
int Sat::DajSekunde() const
{
    return sekunde;
}


int operator-(const Sat &sat1, const Sat &sat2)
{
    int vrijeme1 = sat1.DajSate() * 3600 + sat1.DajMinute() * 60 + sat1.DajSekunde();
    int vrijeme2 = sat2.DajSate() * 3600 + sat2.DajMinute() * 60 + sat2.DajSekunde();
    return vrijeme1 - vrijeme2;
}

Sat operator +(Sat &sat1, int sek)
{
    Sat sat2(sat1.sati, sat1.minute, sat1.sekunde + sek);
    return sat2;
}
Sat operator -(Sat &sat, int sek)
{
    Sat sat2(sat.sati, sat.minute, sat.sekunde - sek);
    return sat2;
}
Sat operator+=(Sat &sat, int sek)
{
    sat.sekunde += sek;
    sat.PostaviNormalizirano(sat.sati, sat.minute, sat.sekunde);
    return sat;
}
Sat operator-=(Sat &sat, int sek)
{
    sat.sekunde -= sek;
    sat.PostaviNormalizirano(sat.sati, sat.minute, sat.sekunde);
    return sat;
}
std::ostream &operator<<(std::ostream &tok, const Sat&sat)
{
    tok << std::setw(2) << std::setfill('0') << sat.sati << ":";
    tok << std::setw(2) << std::setfill('0') << sat.minute ;
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

int main()
{
    /*
    int h, m; char znak;
    std::cout << "Format upisa: sati minute\n";
    std::cout << "Unesite trenutno vrijeme: ";
    std::cin >> h >> m;
    Sat s1(h, m+15, 0);
    std::cout<<"\nPAUZA TRAJE DO: "<<s1<<std::endl;
    std::cout<<"\n----------------------\n";
    std::cin>>h;*/

    // Date
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string s=std::ctime(&start_time);
    std::string monthDay=s.substr(4,6);
    std::string year=s.substr(20,18);
    std::string fullDate=monthDay+" "+year;
    std::string today_date=s.substr(4,6);

    std::cout<<"PRAYER TIMES 14.6 ANGLE"<<std::endl;
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
    std::string fajr,sunrise,dhuhr,asr,magrib,isha;
    Sat half,lastThird;

    out<<city<<" Prayer Times 14.6 Angle "<<year;

    int i=0;
    while (std::getline(in, line))
    {
        date=line.substr(0,6);
        fajr=line.substr(7,5);
        sunrise=(line.substr(9,9)).substr(4,6);
        dhuhr=(line.substr(11,13)).substr(8,10);
        asr=(line.substr(14,16)).substr(11);
        magrib=(line.substr(18,18)).substr(13);
        isha=(line.substr(22,22)).substr(15);
        int h,m;
        h=std::stoi(magrib.substr(0,2));
        m=std::stoi(magrib.substr(3,5));
        Sat ishaUmmulQura(h, m+90, 0);
        // Half, last third
        int h1,h2,m1,m2;
        h1=std::stoi(magrib.substr(0,2));
        m1=std::stoi(magrib.substr(3,5));
        std::string fajrNext=line2.substr(7,5);
        h2=std::stoi(fajrNext.substr(0,2));
        m2=std::stoi(fajrNext.substr(3,5));
        Sat s1(h1, m1, 0);
        Sat s2(h2, m2, 0);
        Sat s(0, 0, 0);
        Sat ss = s2;
        int zbir1 = h1 * 3600 + m1 * 60;
        s -= zbir1;
        int zbir2 = s.DajSate() * 3600 + s.DajMinute() * 60 + s.DajSekunde();
        ss += zbir2;
        int zbir3 = ss.DajSate() * 3600 + ss.DajMinute() * 60 + ss.DajSekunde();
        Sat half = s1, lastThird = s1;
        half += (zbir3 / 2);
        lastThird += 2 * (zbir3 / 3);
        if(date==today_date)
        {
            std::cout<<"Fajr: "<<fajr<<std::endl;
            std::cout<<"Sunrise: "<<sunrise<<std::endl;
            std::cout<<"Dhuhr: "<<dhuhr<<std::endl;
            std::cout<<"Magrib: "<<magrib<<std::endl;
            std::cout<<"Isha: "<<isha<<std::endl;
            std::cout<<"Isha UQ: "<<ishaUmmulQura<<std::endl;
            std::cout<<"Half night: "<<half<<std::endl;
            std::cout<<"Last third: "<<lastThird<<std::endl;
        }
        line2=line;
        out<<date<<" "<<fajr<<" "<<sunrise<<" "<<dhuhr<<" "<<asr<<" "<<magrib<<" "<<isha<<" "<<half<<" "<<lastThird<<"\n";
    }
    in.close();
    out.close();
    std::string c;
    for(;;){
        std::cout<<std::endl<<"Exit program y/n: ";
    std::cin>>c;
           if(c=="y"||c=="Y"||c=="n"||c=="N")
            break;
    }


    return 0;
}
