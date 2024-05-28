#ifndef RETOUCH_CONSOLE_CURSOR_HPP
#define RETOUCH_CONSOLE_CURSOR_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <termios.h>

// INTERFACE
namespace Retouch
{

namespace Console
{

class Cursor
{
public:
    static std::pair<int, int> pos() {
        /*
            # Richiedi al terminale la posizione corrente del cursore
            echo -ne "\033[6n"

            # Leggi e scarta la prima parte della risposta (fino a '[')
            read -s -d\[ garbage

            # Leggi il resto della risposta (fino a 'R') e memorizzala in 'foo'
            read -s -d R foo

            # Stampa la posizione corrente
            echo -n "Current position: "
            echo "$foo"
        */

        int row;
        int col;

        // Save old terminal settings

        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // Request cursor position
        std::cout << "\033[6n";
        std::cout.flush();

        // Read response
        char ch;
        std::string response;
        while (std::cin.get(ch)) {
            if (ch == 'R') break;
            response += ch;
        }

        // Restore old terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        // Parse response
        if (response.size() > 2 && response[0] == '\033' && response[1] == '[') {
            sscanf(response.c_str(), "\033[%d;%d", &row, &col);
        } else {
            row = col = -1; // Invalid response
        }

        return std::make_pair(col,row);
    }
    /**
     * Moves the cursor n (default 1) cells in the given direction.
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    static void goUp(unsigned int n = 1)
    {
        //CSI n A 	CUU 	Cursor Up
        std::cout << "\033[" + std::to_string(n) + "A";
        std::cout.flush();
    }

    /**
     * Moves the cursor n (default 1) cells in the given direction.
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    static void goDown(unsigned int n = 1)
    {
        //CSI n B 	CUD 	Cursor Down
        std::cout << "\033[" + std::to_string(n) + "B";
        std::cout.flush();
    }

    /**
     * Moves the cursor n (default 1) cells in the given direction.
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    static void goForward(unsigned int n = 1)
    {
        //CSI n C 	CUF 	Cursor Forward
        std::cout << "\033[" + std::to_string(n) + "C";
        std::cout.flush();
    }

    /**
     * Moves the cursor n (default 1) cells in the given direction.
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    static void goBack(unsigned int n = 1)
    {
        //CSI n D 	CUB 	Cursor Back
        std::cout << "\033[" + std::to_string(n) + "D";
        std::cout.flush();
    }

    /**
     * Moves cursor to beginning of the line n (default 1) lines down. (not ANSI.SYS)
     */
    static void nextLine(unsigned int n = 1){
        //CSI n E 	CNL
        std::cout << "\033[" + std::to_string(n) + "E";
        std::cout.flush();
    }

    /**
     * Moves cursor to beginning of the line n (default 1) lines up. (not ANSI.SYS)
     */
    static void previousLine(unsigned int n = 1)
    {
        //CSI n F 	CPL
        std::cout << "\033[" + std::to_string(n) + "F";
        std::cout.flush();
    }

    /**
     * Moves the cursor to column n (default 1). (not ANSI.SYS)
     */
    static void horizontalAbsolute(unsigned int n = 1)
    {
        //CSI n G 	CHA
        std::cout << "\033[" + std::to_string(n) + "G";
        std::cout.flush();
    }

    /**
     * Moves the cursor to row n, column m.
     * The values are 1-based, and default to 1 (top left corner) if omitted.
     * A sequence such as CSI ;5H is a synonym for CSI 1;5H as
     * well as CSI 17;H is the same as CSI 17H and CSI 17;1H
     */
    static void position(unsigned int col = 1, unsigned int row = 1)
    {
        //CSI n ; m H 	CUP
        std::cout << "\033[" + std::to_string(row) + ";" + std::to_string(col) + "H";
        std::cout.flush();
    }



    /**
     * Clears part of the screen.
     * If n is 0 (or missing), clear from cursor to end of screen.
     * If n is 1, clear from cursor to beginning of the screen.
     * If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS).
     * If n is 3, clear entire screen and delete all lines saved in the scrollback buffer
     * (this feature was added for xterm and is supported by other terminal applications).
     */
    static void eraseInDisplay(unsigned int n = 0)
    {
        //CSI n J 	ED
        std::cout << "\033[" + std::to_string(n) + "J";
        std::cout.flush();
    }

    /**
     * Erases part of the line.
     * If n is 0 (or missing), clear from cursor to the end of the line.
     * If n is 1, clear from cursor to beginning of the line.
     * If n is 2, clear entire line. Cursor position does not change.
     */
    static void eraseInLine(unsigned int n = 0)
    {
        //CSI n K 	EL
        std::cout << "\033[" + std::to_string(n) + "K";
        std::cout.flush();
    }

    /**
     * Scroll whole page up by n (default 1) lines.
     * New lines are added at the bottom. (not ANSI.SYS)
     */
    static void scrollUp(unsigned int n = 1)
    {
        //CSI n S 	SU
        std::cout << "\033[" + std::to_string(n) + "S";
        std::cout.flush();
    }

    /**
     * Scroll whole page down by n (default 1) lines.
     * New lines are added at the top. (not ANSI.SYS)
     */
    static void scrollDown(unsigned int n = 1)
    {
        //CSI n T 	SD
        std::cout << "\033[" + std::to_string(n) + "T";
        std::cout.flush();
    }


    /**
     * Same as CUP,
     * but counts as a format effector function (like CR or LF)
     * rather than an editor function (like CUD or CNL).
     * This can lead to different handling in certain terminal modes.[5]: Annex A
     */
    static void horizontalVerticalPosition(unsigned int col = 1, unsigned int row = 1)
    {
        //CSI n ; m f 	HVP
        std::cout << "\033[" + std::to_string(row) + ";" + std::to_string(col) + "f";
        std::cout.flush();

    }

    /**
     * Sets colors and style of the characters following this code
     */
    static void selectGraphicrRendition()
    {
        //CSI n m 	SGR
    }

    /**
     * Enable aux serial port usually for local serial printer
     */
    static void portOn()
    {
        //CSI 5i 		AUX
    }

    /**
     * Disable aux serial port usually for local serial printer
     */
    static void portOff()
    {
        //CSI 4i 		AUX
    }

    /**
     * Reports the cursor position (CPR) by transmitting ESC[n;mR, where n is the row and m is the column.
     */
    static void deviceStatusReport()
    {
        //CSI 6n 	DSR
    }
};

} // namespace Retouch::Console

} // namespace Retouch

#endif // RETOUCH_TEXTFILE_HPP
