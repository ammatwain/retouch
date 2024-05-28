#ifndef RETOUCH_CONSOLE_ESCAPE_HPP
#define RETOUCH_CONSOLE_ESCAPE_HPP

#include <string>

namespace Retouch
{

namespace Console
{

namespace Escape
{
/**
 * @brief reset
 * All attributes become turned off
 */
inline static const std::string &reset                        = "\x1b[0m"    ;
inline static const std::string &normal                       = "\x1b[0m"    ;
inline static const std::string &bold                         = "\x1b[1m"    ;
inline static const std::string &bright                       = "\x1b[1m"    ;
inline static const std::string &dim                          = "\x1b[2m"    ;
inline static const std::string &faint                        = "\x1b[2m"    ;
inline static const std::string &italic                       = "\x1b[3m"    ;
inline static const std::string &underline                    = "\x1b[4m"    ;
inline static const std::string &slowBlink                    = "\x1b[5m"    ;
inline static const std::string &rapidBlink                   = "\x1b[6m"    ;
inline static const std::string &reverseVideo                 = "\x1b[7m"    ;
inline static const std::string &conceal                      = "\x1b[8m"    ;
inline static const std::string &hidden                       = "\x1b[8m"    ;
inline static const std::string &crossedOut                   = "\x1b[9m"    ;
inline static const std::string &defaultFont                  = "\x1b[10m"   ;

//Basic Foreground Colors:
inline static const std::string &fgRed                        = "\x1b[31m"   ;
inline static const std::string &fgBlack                      = "\x1b[30m"   ;
inline static const std::string &fgGreen                      = "\x1b[32m"   ;
inline static const std::string &fgYellow                     = "\x1b[33m"   ;
inline static const std::string &fgBlue                       = "\x1b[34m"   ;
inline static const std::string &fgMagenta                    = "\x1b[35m"   ;
inline static const std::string &fgCyan                       = "\x1b[36m"   ;
inline static const std::string &fgWhite                      = "\x1b[37m"   ;
inline static const std::string &fgDefault                    = "\x1b[39m"   ;

//Basic Background Colors:
inline static const std::string &bgBlack                      = "\x1b[40m"   ;
inline static const std::string &bgRed                        = "\x1b[41m"   ;
inline static const std::string &bgGreen                      = "\x1b[42m"   ;
inline static const std::string &bgYellow                     = "\x1b[43m"   ;
inline static const std::string &bgBlue                       = "\x1b[44m"   ;
inline static const std::string &bgMagenta                    = "\x1b[45m"   ;
inline static const std::string &bgCyan                       = "\x1b[46m"   ;
inline static const std::string &bgWhite                      = "\x1b[47m"   ;
inline static const std::string &bgDefault                    = "\x1b[49m"   ;

//Bright Foreground Colors:
inline static const std::string &fgBrightBlack                = "\x1b[90m"   ;
inline static const std::string &fgBrightRed                  = "\x1b[91m"   ;
inline static const std::string &fgBrightGreen                = "\x1b[92m"   ;
inline static const std::string &fgBrightYellow               = "\x1b[93m"   ;
inline static const std::string &fgBrightBlue                 = "\x1b[94m"   ;
inline static const std::string &fgBrightMagenta              = "\x1b[95m"   ;
inline static const std::string &fgBrightCyan                 = "\x1b[96m"   ;
inline static const std::string &fgBrightWhite                = "\x1b[97m"   ;

//Bright Background Colors:
inline static const std::string &bgBrightBlack                = "\x1b[100m"  ;
inline static const std::string &bgBrightRed                  = "\x1b[101m"  ;
inline static const std::string &bgBrightGreen                = "\x1b[102m"  ;
inline static const std::string &bgBrightYellow               = "\x1b[103m"  ;
inline static const std::string &bgBrightBlue                 = "\x1b[104m"  ;
inline static const std::string &bgBrightMagenta              = "\x1b[105m"  ;
inline static const std::string &bgBrightCyan                 = "\x1b[106m"  ;
inline static const std::string &bgBrightWhite                = "\x1b[107m"  ;

//Alternative Fonts:
inline static const std::string &altFont0                     = "\x1b[11m"   ;
inline static const std::string &altFont1                     = "\x1b[12m"   ;
inline static const std::string &altFont2                     = "\x1b[13m"   ;
inline static const std::string &altFont3                     = "\x1b[14m"   ;
inline static const std::string &altFont4                     = "\x1b[15m"   ;
inline static const std::string &altFont5                     = "\x1b[16m"   ;
inline static const std::string &altFont6                     = "\x1b[17m"   ;
inline static const std::string &altFont7                     = "\x1b[18m"   ;
inline static const std::string &altFont8                     = "\x1b[19m"   ;

inline static const std::string &fraktur                      = "\x1b[20m"   ;
inline static const std::string &doubleUnderlineOrBoldOff     = "\x1b[21m"   ;
inline static const std::string &normalColorOrIntensity       = "\x1b[22m"   ;
inline static const std::string &notItalicNotFraktur          = "\x1b[23m"   ;
inline static const std::string &underlineOff                 = "\x1b[24m"   ;
inline static const std::string &blinkOff                     = "\x1b[25m"   ;
inline static const std::string &inverseOff                   = "\x1b[27m"   ;
inline static const std::string &reveal                       = "\x1b[28m"   ;
inline static const std::string &notCrossedOut                = "\x1b[29m"   ;

//Boxology:
inline static const std::string &framed                       = "\x1b[51m"   ;
inline static const std::string &encircled                    = "\x1b[52m"   ;
inline static const std::string &overlined                    = "\x1b[53m"   ;
inline static const std::string &notFramedOrEncircled         = "\x1b[54m"   ;
inline static const std::string &notOverlined                 = "\x1b[55m"   ;
inline static const std::string &ideogramUnderline            = "\x1b[60m"   ;
inline static const std::string &rightSideLine                = "\x1b[60m"   ;
inline static const std::string &ideogramDoubleUnderline      = "\x1b[61m"   ;
inline static const std::string &doubleLineOnTheRightSide     = "\x1b[61m"   ;
inline static const std::string &ideogramOverline             = "\x1b[62m"   ;
inline static const std::string &leftSideLine                 = "\x1b[62m"   ;
inline static const std::string &ideogramDoubleOverline       = "\x1b[63m"   ;
inline static const std::string &doubleLineOnTheLeftSide      = "\x1b[63m"   ;
inline static const std::string &ideogramStressMarking        = "\x1b[64m"   ;
inline static const std::string &ideogramAttributesOff        = "\x1b[65m"   ;

} // namespace Retouch::Escape

} // namespace Retouch::Console

} // namespace Retouch

#endif // RETOUCH_CONSOLE_ESCAPE_HPP
