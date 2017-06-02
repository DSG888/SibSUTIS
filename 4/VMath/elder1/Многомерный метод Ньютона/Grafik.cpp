#include <graphics.h>
#include <math.h>

int main() {
    double xg, y, y2, l2, l1;
    int m = 25;
    initwindow(400, 300);
    moveto(200, 0);
    lineto(200, 400);
    moveto(200, 0);
    lineto(198, 5);
    moveto(200, 0);
    lineto(202, 5);
    moveto(0, 200);
    lineto(400, 200);
    lineto(395, 202);
    moveto(400, 200);
    lineto(395, 198);
    outtextxy(390, 203, "x");
    outtextxy(187, 0, "y");
    for (xg = (-200); xg <= 200; xg+=0.001) {
        l1 = (10 - pow(xg, 3));
        l2 = (0.3333333333);
        y = pow(l1, l2);
        putpixel(200+xg*m, 200-y*m, 4);
        y2 = 2/xg;
        putpixel(200+xg*m, 200-y2*m, 2);
    }
    getch();
}
