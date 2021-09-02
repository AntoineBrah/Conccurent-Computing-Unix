// TEXT RESET
#define ANSI_RESET   "\x1b[0m"  // reset

// TEXT COLOR
#define ANSI_COLOR_WHITE "\u001b[37;1m" // text color white
#define ANSI_COLOR_RED     "\x1b[31m" // text color red
#define ANSI_COLOR_GREEN   "\x1b[32m" // text color green
#define ANSI_COLOR_YELLOW  "\x1b[33m" // text color yellow
#define ANSI_COLOR_BLUE    "\x1b[34m" // text color blue
#define ANSI_COLOR_MAGENTA "\x1b[35m" // text color magenta
#define ANSI_COLOR_CYAN    "\x1b[36m" // text color cyan

// TEXT BOLD COLOR
#define BHWHT "\e[1;97m"

// BACKGROUND COLOR
#define WHTB "\e[47m"

// BOLD
#define ANSI_BOLD "\e[1m" // text bold

// UNDERLINE
#define ANSI_UNDERLINE "\033[4m" // text underline

// STRIKE
#define ANSI_STRIKE "\033[9m" // text strike

// BLINK
#define ANSI_BLINK "\033[5m" // text blink

// HIGH SPACE UNDERLINE
#define ANSI_UNDERLINE_H "\033[52m" // text blink

// HIGHLIGHT COLOR
#define ANSI_COLOR_WHITE_H     "\x1b[7m" // text highlight color white
#define ANSI_COLOR_RED_H     "\x1b[41m" // text highlight color red
#define ANSI_COLOR_GREEN_H   "\x1b[42m" // text highlight color green
#define ANSI_COLOR_YELLOW_H  "\x1b[43m" // text highlight color yellow
#define ANSI_COLOR_BLUE_H    "\x1b[44m" // text highlight color blue
#define ANSI_COLOR_MAGENTA_H "\x1b[45m" // text highlight color magenta
#define ANSI_COLOR_CYAN_H    "\x1b[46m" // text highlight color cyan

// CLEAR SCREEN
#define clearScreen() printf("\033[2J")