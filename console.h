#include <iostream>
#include <Windows.h>

HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
inline std::ostream& blue(std::ostream &s)
{
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
              |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream &s)
{
    SetConsoleTextAttribute(hStdout,
                FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream &s)
{
    SetConsoleTextAttribute(hStdout,
              FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& yellow(std::ostream &s)
{
    SetConsoleTextAttribute(hStdout,
         FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream &s)
{
    SetConsoleTextAttribute(hStdout,
       FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

struct color {
    color(WORD attribute):m_color(attribute){};
    WORD m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>&
      operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c)
{
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
