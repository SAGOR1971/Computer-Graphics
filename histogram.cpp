#include <graphics.h>
#include <conio.h>
#include "histogram.h"

int main()
{
    initwindow(900, 600, "Histogram");

    // Example data (test)
    double data[] = {1,2,5,6,7,8,9,10,11,12,20,41};
    int n = sizeof(data) / sizeof(data[0]);

    drawHistogram(data, n, 5, "My Histogram", "Value", "Frequency", true);

    getch();
    closegraph();
    return 0;
}
