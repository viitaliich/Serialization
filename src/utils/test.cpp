#include "test.hpp"

void test() {
    
    int color = 0xAABBCC;
    logHex(color);
    
    int r = (color & 0xFF0000) >> 16;
    int g = (color & 0xFF00) >> 8;
    int b = (color & 0xFF) >> 0;
    logHex(r);
    logHex(g);
    logHex(b);
    
    //    r -= 0xA;
    //    g -= 0xB;
    //    b -= 0xC;
    //    logHex(r);
    //    logHex(g);
    //    logHex(b);
    
    int result = (r << 16) | (g << 8) | (b << 0);
    logHex(result);
    
}
