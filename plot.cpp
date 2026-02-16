#include <graphics.h>
#include <conio.h>
#include "plot.h"

int main()
{
    // WinBGIm এ এটা ব্যবহার করলে window সুন্দর আসে
    initwindow(900, 600, "Graph");

    double x[] = {0, 1, 2, 3, 4, 5};
    double y[] = {0, 1, 4,9,16,25}; // still x^3 but sparse

    int n = 6;


    // point label OFF করে দাও (false)
    drawLineGraph(x, y, n, "This is Plot", "X Axis", "Y Axis", false);

    getch();
    closegraph();
    return 0;
}
