# Prayer Times Calculator
Prayer Times Calculator which uses 14.6 angle for fajr and isha calculation.

## Prayer times ruling
- Fajr prayer – from the appearance of true dawn, i.e. of light
on the right and left side of the horizon until sunrise
- Dhuhr prayer - when the sun moves from the zenith (5-7
minutes after the zenith) until the shadow of the object
towards the west is the same size as the object, i.e. the
beginning of asr
- Asr prayer – from the moment when the shadow of the
object towards the west is the same size as the object until
sunset
- Maghrib prayer - from sunset to the disappearance of the
redness in the sky, i.e. beginning of isha
- Isha prayer - from the disappearance of the redness in the
sky until the middle of the night (half of the night is
calculated by dividing the time from sunset to true dawn into
two parts)

## Prayer times calculation
All prayer times are calculated according to math-based formulas that use latitute and longitude coordinates,
sun position, date, time zone, dt

[Source code](http://praytimes.org/code/)

I fixed calculation of DST (Daylight Saving Time).
DST happens from last sunday of March to last sunday of October.
Also, I removed all prayer times calculation methods except the most correct method, which is angle based with 14.6 angle.

## Website
[Link](https://amarhusika.github.io/prayer-times-calculator)

## Windows app
- automatic date detection
- generate yearly prayer times table
- change location to any city

## Set-up Windows app
- [download](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe/download) and install CodeBlocks with MinGW
- open index.html and enter all city details
- set year to be non-leap (for example 2023) and copy prayer times to CityName.txt
- set year to be leap (for example 2024) and copy prayer times to CityNameLeapYear.txt
- paste created txt files in cities folder
- change city name in mainVaktija.cpp



