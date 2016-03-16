#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
using namespace std;

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

int open_port(void) {
    int gd;

    gd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if(gd == -1) {
        perror("open_port: Unable to open /dev/ttyS0 - ");
    }
    else
        fcntl(gd, F_SETFL, FNDELAY);

    //printf("In Open port gd = %i\n", gd);

    return (gd);
}

int main(void)
{
    const char *dev = "/dev/input/event0";
    struct input_event ev;
    ssize_t n;
    int fd;
    int code;
    int gd;
    //int m;
    
    gd = open_port();

    struct termios options;
    tcgetattr(gd, &options);

    cfsetispeed(&options, B57600);
    cfsetospeed(&options, B57600);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    options.c_lflag |= ICANON;
    tcsetattr(gd, TCSANOW, &options);

    /*
    if ( tcsetattr( fd, TCSANOW, &options  ) == -1  )
        printf ("Error with tcsetattr = %s\n", strerror ( errno  ) );
    else
        printf ( "%s\n", "tcsetattr succeed"  );
    */

    fcntl(gd, F_SETFL, FNDELAY);

    //m = write(gd, "1", 4);
    /*if (n < 0)
        fputs("write() of 4 bytes failed!\n", stderr);
    else
        printf ("Write succeed n = %i\n", n );
    */

    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }
    while (1) {
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
            if(ev.value == 0)
                write(gd, "0", 1);
            else if(ev.value == 1)
                write(gd, "1", 1);
            else
                continue;

            switch((int)ev.code) {
                case 1:
                    printf("%s ESC\n", evval[ev.value]);
                    break;
                case 2:
                    printf("%s 1\n", evval[ev.value]);
                    break;
                case 3:
                    printf("%s 2\n", evval[ev.value]);
                    break;
                case 4:
                    printf("%s 3\n", evval[ev.value]);
                    break;
                case 5:
                    printf("%s 4\n", evval[ev.value]);
                    break;
                case 6:
                    printf("%s 5\n", evval[ev.value]);
                    break;
                case 7:
                    printf("%s 6\n", evval[ev.value]);
                    break;
                case 8:
                    printf("%s 7\n", evval[ev.value]);
                    break;
                case 9:
                    printf("%s 8\n", evval[ev.value]);
                    break;
                case 10:
                    printf("%s 9\n", evval[ev.value]);
                    break;
                case 11:
                    printf("%s 0\n", evval[ev.value]);
                    break;
                case 12:
                    printf("%s -\n", evval[ev.value]);
                    break;
                case 13:
                    printf("%s =\n", evval[ev.value]);
                    break;
                case 14:
                    printf("%s Backspace\n", evval[ev.value]);
                    break;
                case 15:
                    printf("%s Tab\n", evval[ev.value]);
                    break;
                case 16:
                    printf("%s Q\n", evval[ev.value]);
                    break;
                case 17:
                    printf("%s W\n", evval[ev.value]);
                    break;
                case 18:
                    printf("%s E\n", evval[ev.value]);
                    break;
                case 19:
                    printf("%s R\n", evval[ev.value]);
                    break;
                case 20:
                    printf("%s T\n", evval[ev.value]);
                    break;
                case 21:
                    printf("%s Y\n", evval[ev.value]);
                    break;
                case 22:
                    printf("%s U\n", evval[ev.value]);
                    break;
                case 23:
                    printf("%s I\n", evval[ev.value]);
                    break;
                case 24:
                    printf("%s O\n", evval[ev.value]);
                    break;
                case 25:
                    printf("%s P\n", evval[ev.value]);
                    break;
                case 26:
                    printf("%s [\n", evval[ev.value]);
                    break;
                case 27:
                    printf("%s ]\n", evval[ev.value]);
                    break;
                case 28:
                    printf("%s Enter\n", evval[ev.value]);
                    break;
                case 29:
                    printf("%s L-Ctrl\n", evval[ev.value]);
                    break;
                case 30:
                    printf("%s A\n", evval[ev.value]);
                    break;
                case 31:
                    printf("%s S\n", evval[ev.value]);
                    break;
                case 32:
                    printf("%s D\n", evval[ev.value]);
                    break;
                case 33:
                    printf("%s F\n", evval[ev.value]);
                    break;
                case 34:
                    printf("%s G\n", evval[ev.value]);
                    break;
                case 35:
                    printf("%s H\n", evval[ev.value]);
                    break;
                case 36:
                    printf("%s J\n", evval[ev.value]);
                    break;
                case 37:
                    printf("%s K\n", evval[ev.value]);
                    break;
                case 38:
                    printf("%s L\n", evval[ev.value]);
                    break;
                case 39:
                    printf("%s :\n", evval[ev.value]);
                    break;
                case 40:
                    printf("%s '\n", evval[ev.value]);
                    break;
                case 41:
                    printf("%s `\n", evval[ev.value]);
                    break;
                case 42:
                    printf("%s L-Shift\n", evval[ev.value]);
                    break;
                case 43:
                    printf("%s \\\n", evval[ev.value]);
                    break;
                case 44:
                    printf("%s Z\n", evval[ev.value]);
                    break;
                case 45:
                    printf("%s X\n", evval[ev.value]);
                    break;
                case 46:
                    printf("%s C\n", evval[ev.value]);
                    break;
                case 47:
                    printf("%s V\n", evval[ev.value]);
                    break;
                case 48:
                    printf("%s B\n", evval[ev.value]);
                    break;
                case 49:
                    printf("%s N\n", evval[ev.value]);
                    break;
                case 50:
                    printf("%s M\n", evval[ev.value]);
                    break;
                case 51:
                    printf("%s ,\n", evval[ev.value]);
                    break;
                case 52:
                    printf("%s .\n", evval[ev.value]);
                    break;
                case 53:
                    printf("%s /\n", evval[ev.value]);
                    break;
                case 54:
                    printf("%s R-Shift\n", evval[ev.value]);
                    break;
                case 55:
                    printf("%s *\n", evval[ev.value]);
                    break;
                case 56:
                    printf("%s L-Alt\n", evval[ev.value]);
                    break;
                case 57:
                    printf("%s Space\n", evval[ev.value]);
                    break;
                case 58:
                    printf("%s Caps Lock\n", evval[ev.value]);
                    break;
                case 59:
                    printf("%s F1\n", evval[ev.value]);
                    break;
                case 60:
                    printf("%s F2\n", evval[ev.value]);
                    break;
                case 61:
                    printf("%s F3\n", evval[ev.value]);
                    break;
                case 62:
                    printf("%s F4\n", evval[ev.value]);
                    break;
                case 63:
                    printf("%s F5\n", evval[ev.value]);
                    break;
                case 64:
                    printf("%s F6\n", evval[ev.value]);
                    break;
                case 65:
                    printf("%s F7\n", evval[ev.value]);
                    break;
                case 66:
                    printf("%s F8\n", evval[ev.value]);
                    break;
                case 67:
                    printf("%s F9\n", evval[ev.value]);
                    break;
                case 68:
                    printf("%s F10\n", evval[ev.value]);
                    break;
                case 69:
                    printf("%s Num Lock\n", evval[ev.value]);
                    break;
                case 70:
                    printf("%s Scroll Lock\n", evval[ev.value]);
                    break;
                default:
                    printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
            }
        }

    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
