# CGPlot — Simple Line Graph & Histogram (WinBGIm / graphics.h)

CGPlot is a lightweight **Computer Graphics plotting helper** written in **C++** using **WinBGIm (graphics.h)**.  
It is designed for **Computer Graphics lab projects**, demonstrations, and learning data visualization concepts such as **line graphs** and **histograms**, similar to **Matlab / Matplotlib** (conceptually).

---

## Features

- 📈 Line Graph (auto-scaled X and Y axis)
- 📊 Histogram with correct bin logic  
  - Bins follow **[start, end)** rule  
  - Last bin is **[start, end]** (inclusive)
- Automatic axis scaling
- Axis ticks and labels
- Optional bin-range labels (e.g. `1.0–9.0`)
- Supports `int`, `float`, and `double` data
- Header-only (easy to include and share)

---

## Requirements

- **Windows OS**
- **MinGW-w64 (g++)**
- **WinBGIm / graphics.h installed**
  - `graphics.h` inside MinGW `include` folder
  - `libbgi.a` inside MinGW `lib` folder
  - Required link libraries:
    ```
    -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    ```

> If your `graphics.h` programs already work, CGPlot will work without extra setup.

---

## File Structure (Example)

```
CGPlot/
├── plot.h
├── histogram.h
├── examples/
│   ├── line_graph.cpp
│   └── histogram.cpp
```

---

## Installation

### Option 1: Local Project Include (Recommended)

Keep `plot.h` and `histogram.h` inside your project folder.

```cpp
#include "plot.h"
#include "histogram.h"
```

---

### Option 2: Global Include (graphics.h style)

Copy headers to MinGW include directory:

```
C:\mingw64\include\plot.h
C:\mingw64\include\histogram.h
```

Then use:

```cpp
#include <plot.h>
#include <histogram.h>
```

---

## Compilation (MinGW g++)

### Line Graph

```bash
g++ examples/line_graph.cpp -o line_graph.exe ^
  -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

---

### Histogram

```bash
g++ examples/histogram.cpp -o histogram.exe ^
  -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

---

## Usage Examples

### Line Graph (y = x³)

```cpp
#include <graphics.h>
#include <conio.h>
#include "plot.h"

int main() {
    initwindow(900, 600, "Line Graph");

    double x[] = {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5};
    double y[] = {0, 0.125, 1, 3.375, 8, 15.625, 27, 42.875, 64, 91.125, 125};

    int n = sizeof(x) / sizeof(x[0]);

    drawLineGraph(x, y, n, "y = x^3", "X Axis", "Y Axis", false);

    getch();
    closegraph();
    return 0;
}
```

---

### Histogram Example

```cpp
#include <graphics.h>
#include <conio.h>
#include "histogram.h"

int main() {
    initwindow(900, 600, "Histogram");

    double data[] = {1,2,5,6,7,8,9,10,11,12,20,41};
    int n = sizeof(data) / sizeof(data[0]);

    drawHistogram(data, n, 5, "My Histogram", "Value", "Frequency", true);

    getch();
    closegraph();
    return 0;
}
```

---

## How Histogram Works

1. Find minimum and maximum values
2. Divide the range into equal bins
3. Count how many values fall into each bin
4. Draw bars proportional to frequency
5. X-axis shows bin ranges, Y-axis shows frequency

---

## Common Issues

- **Undefined reference errors**  
  Make sure WinBGIm libraries are linked.

- **Text overlap**  
  Reduce bin count or disable bin labels.

- **Window closes immediately**  
  Add `getch()` before `closegraph()`.

---

## Scalability Notes

- ✔ Suitable for CG lab assignments
- ✔ Easy to understand and modify
- ❌ Not designed for large datasets
- ❌ Depends on legacy `graphics.h`

---

## License

MIT License

---

## Author

Created for educational **Computer Graphics** projects using **WinBGIm (graphics.h)**.
