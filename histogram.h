#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <graphics.h>
#include <cstdio>
#include <cmath>   // floor, fabs

// ===== CANVAS / PLOT BOX =====
#define H_LEFT   90
#define H_RIGHT  850
#define H_TOP    70
#define H_BOTTOM 520

#define H_TICKS 5  // Default ticks for large numbers

inline void _hText(int x, int y, const char* s) {
    char buf[128];
    std::snprintf(buf, sizeof(buf), "%s", s);
    outtextxy(x, y, buf);
}

inline void _hTitleAndLabels(const char* title, const char* xlab, const char* ylab)
{
    setcolor(BLACK);
    setbkcolor(WHITE); // Ensure text background is clean

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    _hText((H_LEFT + H_RIGHT)/2 - 60, 20, title);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    _hText((H_LEFT + H_RIGHT)/2 - 25, H_BOTTOM + 35, xlab);

    // Y Label
    _hText(20, (H_TOP + H_BOTTOM)/2, ylab);
}

// Robust bin index calculation (Fixed for Precision)
template <typename T>
inline int _histBinIndex(T v, T minV, T maxV, int bins)
{
    // Safety check
    if (v >= maxV) return bins - 1; // Last bin covers up to maxV
    if (v < minV) return 0;

    double range = (double)maxV - (double)minV;
    if (range == 0.0) return 0;

    // FIX: Add 0.00001 to handle floating point errors (e.g. 8.9999 issue)
    double pos = (((double)v - (double)minV) * bins) / range;
    int idx = (int)(pos + 0.00001);

    if (idx < 0) idx = 0;
    if (idx >= bins) idx = bins - 1;
    return idx;
}

template <typename T>
void drawHistogram(T data[], int n,
                   int bins = 10,
                   const char* title = "Histogram",
                   const char* xLabel = "Value",
                   const char* yLabel = "Frequency",
                   bool showBinRanges = true)
{
    if(n <= 0) return;
    if(bins < 1) bins = 1;

    // White background
    setbkcolor(WHITE);
    cleardevice();

    // Plot box
    setcolor(BLACK);
    rectangle(H_LEFT, H_TOP, H_RIGHT, H_BOTTOM);

    _hTitleAndLabels(title, xLabel, yLabel);

    // ----- Find min/max -----
    T minV = data[0], maxV = data[0];
    for(int i = 1; i < n; i++){
        if(data[i] < minV) minV = data[i];
        if(data[i] > maxV) maxV = data[i];
    }

    // Avoid zero range
    if(maxV == minV) maxV = minV + (T)1;

    // ----- Build Counts -----
    int* count = new int[bins];
    for(int i=0;i<bins;i++) count[i]=0;

    for(int i = 0; i < n; i++)
    {
        int idx = _histBinIndex<T>(data[i], minV, maxV, bins);
        count[idx]++;
    }

    // Max frequency for scaling
    int maxC = count[0];
    for(int i=1;i<bins;i++) if(count[i] > maxC) maxC = count[i];
    if(maxC == 0) maxC = 1;

    // ----- Y Axis Ticks (SMART FIX) -----
    // If max count is small (<= 15), show every integer step. 
    // Otherwise use 5 divisions.
    setcolor(BLACK);
    char buf[80];
    
    int numTicks = (maxC <= 15) ? maxC : H_TICKS;

    for(int i = 0; i <= numTicks; i++) {
        int fv; // The value to display
        
        if (maxC <= 15) {
            fv = i; 
        } else {
            fv = (int)(maxC * (i / (float)numTicks));
        }

        // Calculate Y pixel position based on value ratio
        float ratio = (float)fv / maxC;
        int py = H_BOTTOM - (int)((H_BOTTOM - H_TOP) * ratio);

        line(H_LEFT - 6, py, H_LEFT, py);

        std::snprintf(buf, sizeof(buf), "%d", fv);
        _hText(H_LEFT - 40, py - 6, buf);
    }

    // ----- Draw Bars -----
    int plotW = (H_RIGHT - H_LEFT);
    // Use double for width to avoid gaps
    double barW = (double)plotW / bins; 

    double rangeV = (double)maxV - (double)minV;
    double binWv  = rangeV / bins;

    for(int b = 0; b < bins; b++)
    {
        // Calculate precise coordinates
        int barLeft  = H_LEFT + (int)(b * barW);
        int barRight = H_LEFT + (int)((b + 1) * barW);
        
        // Add small gap
        barLeft += 2; 
        barRight -= 2;

        float hRatio = count[b] / (float)maxC;
        int barTop   = H_BOTTOM - (int)((H_BOTTOM - H_TOP) * hRatio);

        // Draw Bar Fill
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(barLeft, barTop, barRight, H_BOTTOM);
        
        // Draw Outline
        setcolor(BLACK);
        rectangle(barLeft, barTop, barRight, H_BOTTOM);

        // X tick at bin center
        int cx = (barLeft + barRight)/2;
        line(cx, H_BOTTOM, cx, H_BOTTOM+6);

        if(showBinRanges)
        {
            double start = (double)minV + b * binWv;
            double end   = start + binWv;
            // Last bin fix
            if(b == bins - 1) end = (double)maxV; 
            
            std::snprintf(buf, sizeof(buf), "%.1f-%.1f", start, end);
            _hText(cx - 35, H_BOTTOM + 10, buf);
            
            // Show Count on Top of Bar
            if(count[b] > 0) {
                char countBuf[10];
                std::snprintf(countBuf, sizeof(countBuf), "%d", count[b]);
                _hText(cx - 5, barTop - 20, countBuf);
            }
        }
    }

    delete[] count;
}

#endif