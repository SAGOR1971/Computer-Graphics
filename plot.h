#ifndef PLOT_H
#define PLOT_H

#include <graphics.h>
#include <cstdio>

#define LEFT   90
#define RIGHT  850
#define TOP    70
#define BOTTOM 520

#define TICKS 5

inline void _drawText(int x, int y, const char* s) {
    // winbgim এ outtextxy char* চায়
    char buf[128];
    std::snprintf(buf, sizeof(buf), "%s", s);
    outtextxy(x, y, buf);
}

inline void _drawTitleAndLabels(const char* title, const char* xlab, const char* ylab)
{
    setcolor(BLACK);

    // Title
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    _drawText((LEFT + RIGHT)/2 - 40, 20, title);

    // X label
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    _drawText((LEFT + RIGHT)/2 - 25, BOTTOM + 35, xlab);

    // Y label (vertical text BGI তে কঠিন, তাই পাশে লিখে দিচ্ছি)
    _drawText(20, (TOP + BOTTOM)/2, ylab);
}

template <typename T>
void drawLineGraph(T x[], T y[], int n,
                   const char* title = "Graph",
                   const char* xLabel = "X",
                   const char* yLabel = "Y",
                   bool showPointValues = false)
{
    // ----- Background white like matplotlib -----
    setbkcolor(WHITE);
    cleardevice();

    // ----- Plot box -----
    setcolor(BLACK);
    rectangle(LEFT, TOP, RIGHT, BOTTOM);

    _drawTitleAndLabels(title, xLabel, yLabel);

    // ----- min/max -----
    T minX = x[0], maxX = x[0];
    T minY = y[0], maxY = y[0];

    for(int i=1;i<n;i++){
        if(x[i] < minX) minX = x[i];
        if(x[i] > maxX) maxX = x[i];
        if(y[i] < minY) minY = y[i];
        if(y[i] > maxY) maxY = y[i];
    }
    if(maxX == minX) maxX = minX + 1;
    if(maxY == minY) maxY = minY + 1;

    float xScale = (float)(RIGHT - LEFT) / (float)(maxX - minX);
    float yScale = (float)(BOTTOM - TOP) / (float)(maxY - minY);

    // ----- Ticks and tick labels (0..5 and 0..125 style) -----
    setcolor(BLACK);
    char buf[64];

    // X ticks
    for(int i=0;i<=TICKS;i++){
        int px = LEFT + (int)((RIGHT-LEFT) * (i/(float)TICKS));
        line(px, BOTTOM, px, BOTTOM+6);

        float xv = (float)minX + (float)(maxX-minX) * (i/(float)TICKS);
        std::snprintf(buf, sizeof(buf), "%.1f", xv);
        _drawText(px-12, BOTTOM+10, buf);
    }

    // Y ticks
    for(int i=0;i<=TICKS;i++){
        int py = BOTTOM - (int)((BOTTOM-TOP) * (i/(float)TICKS));
        line(LEFT-6, py, LEFT, py);

        float yv = (float)minY + (float)(maxY-minY) * (i/(float)TICKS);
        std::snprintf(buf, sizeof(buf), "%.0f", yv);
        _drawText(LEFT-55, py-6, buf);
    }

    // ----- Draw line (blue-ish like matplotlib) -----
    setcolor(BLUE);

    for(int i=0;i<n-1;i++){
        int x1 = LEFT + (int)(((float)x[i]   - (float)minX) * xScale);
        int y1 = BOTTOM - (int)(((float)y[i] - (float)minY) * yScale);

        int x2 = LEFT + (int)(((float)x[i+1]   - (float)minX) * xScale);
        int y2 = BOTTOM - (int)(((float)y[i+1] - (float)minY) * yScale);

        line(x1,y1,x2,y2);

        if(showPointValues){
            setcolor(BLACK);
            std::snprintf(buf, sizeof(buf), "(%.2f, %.2f)", (float)x[i], (float)y[i]);
            _drawText(x1+6, y1-12, buf);
            setcolor(BLUE);
        }
    }
}

#endif
