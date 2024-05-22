#ifndef RETOUCH_COLORIZE_HPP
#define RETOUCH_COLORIZE_HPP

#include <iostream>
#include <string>

class Esc
{
public:
    inline static const char* reset                        = "\x1b[0m"      ;
    inline static const char* normal                       = "\x1b[0m"      ;
    inline static const char* bold                         = "\x1b[1m"      ;
    inline static const char* bright                       = "\x1b[1m"      ;
    inline static const char* dim                          = "\x1b[2m"      ;
    inline static const char* faint                        = "\x1b[2m"      ;
    inline static const char* italic                       = "\x1b[3m"      ;
    inline static const char* underline                    = "\x1b[4m"      ;
    inline static const char* slowBlink                    = "\x1b[5m"      ;
    inline static const char* rapidBlink                   = "\x1b[6m"      ;
    inline static const char* reverseVideo                 = "\x1b[7m"      ;
    inline static const char* conceal                      = "\x1b[8m"      ;
    inline static const char* hidden                       = "\x1b[8m"      ;
    inline static const char* crossedOut                   = "\x1b[9m"      ;
    inline static const char* defaultFont                  = "\x1b[10m"     ;
public:
    //Basic Foreground Colors:
    inline static const char* fgRed                        = "\x1b[31m"   ;
    inline static const char* fgBlack                      = "\x1b[30m"   ;
    inline static const char* fgGreen                      = "\x1b[32m"   ;
    inline static const char* fgYellow                     = "\x1b[33m"   ;
    inline static const char* fgBlue                       = "\x1b[34m"   ;
    inline static const char* fgMagenta                    = "\x1b[35m"   ;
    inline static const char* fgCyan                       = "\x1b[36m"   ;
    inline static const char* fgWhite                      = "\x1b[37m"   ;
    inline static const char* fgDefault                    = "\x1b[39m"   ;
public:
    //Basic Background Colors:
    inline static const char* bgBlack                      = "\x1b[40m"   ;
    inline static const char* bgRed                        = "\x1b[41m"   ;
    inline static const char* bgGreen                      = "\x1b[42m"   ;
    inline static const char* bgYellow                     = "\x1b[43m"   ;
    inline static const char* bgBlue                       = "\x1b[44m"   ;
    inline static const char* bgMagenta                    = "\x1b[45m"   ;
    inline static const char* bgCyan                       = "\x1b[46m"   ;
    inline static const char* bgWhite                      = "\x1b[47m"   ;
    inline static const char* bgDefault                    = "\x1b[49m"   ;
public:
    //Bright Foreground Colors:
    inline static const char* fgBrightBlack                = "\x1b[90m"   ;
    inline static const char* fgBrightRed                  = "\x1b[91m"   ;
    inline static const char* fgBrightGreen                = "\x1b[92m"   ;
    inline static const char* fgBrightYellow               = "\x1b[93m"   ;
    inline static const char* fgBrightBlue                 = "\x1b[94m"   ;
    inline static const char* fgBrightMagenta              = "\x1b[95m"   ;
    inline static const char* fgBrightCyan                 = "\x1b[96m"   ;
    inline static const char* fgBrightWhite                = "\x1b[97m"   ;
public:
    //Bright Background Colors:
    inline static const char* bgBrightBlack                = "\x1b[100m"  ;
    inline static const char* bgBrightRed                  = "\x1b[101m"  ;
    inline static const char* bgBrightGreen                = "\x1b[102m"  ;
    inline static const char* bgBrightYellow               = "\x1b[103m"  ;
    inline static const char* bgBrightBlue                 = "\x1b[104m"  ;
    inline static const char* bgBrightMagenta              = "\x1b[105m"  ;
    inline static const char* bgBrightCyan                 = "\x1b[106m"  ;
    inline static const char* bgBrightWhite                = "\x1b[107m"  ;
public:
    //Alternative Fonts:
    inline static const char* altFont0                     = "\x1b[11m"   ;
    inline static const char* altFont1                     = "\x1b[12m"   ;
    inline static const char* altFont2                     = "\x1b[13m"   ;
    inline static const char* altFont3                     = "\x1b[14m"   ;
    inline static const char* altFont4                     = "\x1b[15m"   ;
    inline static const char* altFont5                     = "\x1b[16m"   ;
    inline static const char* altFont6                     = "\x1b[17m"   ;
    inline static const char* altFont7                     = "\x1b[18m"   ;
    inline static const char* altFont8                     = "\x1b[19m"   ;

    inline static const char* fraktur                      = "\x1b[20m"     ;
    inline static const char* doubleUnderlineOrBoldOff     = "\x1b[21m"     ;
    inline static const char* normalColorOrIntensity       = "\x1b[22m"     ;
    inline static const char* notItalicNotFraktur          = "\x1b[23m"     ;
    inline static const char* underlineOff                 = "\x1b[24m"     ;
    inline static const char* blinkOff                     = "\x1b[25m"     ;
    inline static const char* inverseOff                   = "\x1b[27m"     ;
    inline static const char* reveal                       = "\x1b[28m"     ;
    inline static const char* notCrossedOut                = "\x1b[29m"     ;

public:
    //Boxology:
    inline static const char* framed                       = "\x1b[51m"     ;
    inline static const char* encircled                    = "\x1b[52m"     ;
    inline static const char* overlined                    = "\x1b[53m"     ;
    inline static const char* notFramedOrEncircled         = "\x1b[54m"     ;
    inline static const char* notOverlined                 = "\x1b[55m"     ;
    inline static const char* ideogramUnderline            = "\x1b[60m"     ;
    inline static const char* rightSideLine                = "\x1b[60m"     ;
    inline static const char* ideogramDoubleUnderline      = "\x1b[61m"     ;
    inline static const char* doubleLineOnTheRightSide     = "\x1b[61m"     ;
    inline static const char* ideogramOverline             = "\x1b[62m"     ;
    inline static const char* leftSideLine                 = "\x1b[62m"     ;
    inline static const char* ideogramDoubleOverline       = "\x1b[63m"     ;
    inline static const char* doubleLineOnTheLeftSide      = "\x1b[63m"     ;
    inline static const char* ideogramStressMarking        = "\x1b[64m"     ;
    inline static const char* ideogramAttributesOff        = "\x1b[65m"     ;
public:
    static void printCursorPos(/*int* x, int* y*/) {
        int x;
        int y;
        printf("\033[6n");
        scanf("\033[%d;%dR", &x, &y);
        std::cout << "x: " << x << " , y: " << y << std::endl;
    }
};

#endif
