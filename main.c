#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

void main() {
    HWND consoleWindow = GetConsoleWindow();
    const int window_bounds_x = 0;
    const int window_bounds_y = 0;
    const int window_bounds_w = 240;
    const int window_bounds_h = 240;
    int* buffer = (int*)malloc(window_bounds_w*window_bounds_h*sizeof(int));
    HDC screen = GetDC(consoleWindow);
    float t = 0;
    while (1) {
        for (int i = 0; i < window_bounds_w; i++) {
            for (int j = 0; j < window_bounds_h; j++) {
                int c = 0x000000;
                float x = ((float)i)/((float)window_bounds_w) - 0.5f;
                float y = ((float)j)/((float)window_bounds_h) - 0.5f;
                float r = 1./sqrtf((x*x)+(y*y));
                float p = atan2f(y, x)/3.1415+r+sinf(t);
                if (fmod(r+t, 2) < 1 && fmod(p, 0.5) < .25f) {
                    c = 0xffffff;
                }
                const int u = i+window_bounds_x;
                const int v = j+window_bounds_y;
                if (buffer[u+v*window_bounds_w] != c) {
                    SetPixelV(screen, u, v, c);
                    buffer[u+v*window_bounds_w] = c;
                }
            }
        }
        t += 0.01;
    }
}