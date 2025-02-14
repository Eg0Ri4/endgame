#include "includs.h"

void draw_info(int w, int m, int f, double s){
    DrawText(TextFormat("Wave: %08i", w), 10, 20, 20, RED);
    DrawText(TextFormat("Money: %08i$", m), 10, 40, 20, YELLOW);
    DrawText(TextFormat("Food: %08i", f), 10, 60, 20, BROWN);
    DrawText(TextFormat("Stone: %08f", s), 10, 80, 20,  GRAY);
}
