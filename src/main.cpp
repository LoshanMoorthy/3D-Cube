#include <cmath>
#include <numeric>

#include "screen.h"

// Representing a 3D vector
struct vec3 {
    float x, y, z;
};

// Connection between points
struct connection {
    int a, b;
};

// Rotate a 3D points around its axes
void rotate(vec3& point, float x = 1, float y = 1, float z = 1) {
    float rad = 0;
   
    // Rotation x 
    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;
    
    // Rotation around y-axis
    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;
    
    // Around z-axis
    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

// Draws a line betweeen two points
void line(Screen& screen, float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);

    for (float i = 0; i < length; i++) {
        screen.pixel(
            x1 + std::cos(angle) * i, 
            y1 + std::sin(angle) * i
        );
    }
}

int main(int argc, char* argv[]) {
    Screen screen;
   
    // Vertices of a 3D cube
    std::vector<vec3> points {
        {100, 100, 100},
        {200, 100, 100},
        {200, 200, 100},
        {100, 200, 100},

        {100, 100, 200},
        {200, 100, 200},
        {200, 200, 200},
        {100, 200, 200}
    };
    
    std::vector<connection> connections {
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},

        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}
    };

    std::vector<vec3> points2 {
        {300, 100, 100},
        {400, 100, 100},
        {400, 200, 100},
        {300, 200, 100},
        {300, 100, 200},
        {400, 100, 200},
        {400, 200, 200},
        {300, 200, 200}
    };
    
    std::vector<connection> connections2 {
        {0, 4}, {1, 5}, {2, 6}, {3, 7},
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4}
    };

    // Calculating center point of object.
    vec3 centeroid{0, 0, 0};
    for(auto& p : points) {
        centeroid.x += p.x;
        centeroid.y += p.y;
        centeroid.z += p.z;
    }
    centeroid.x /= points.size();
    centeroid.y /= points.size();
    centeroid.z /= points.size();

    vec3 centeroid2{0, 0, 0};
    for(auto& p : points2) {
        centeroid2.x += p.x;
        centeroid2.y += p.y;
        centeroid2.z += p.z;
    }
    centeroid2.x /= points2.size();
    centeroid2.y /= points2.size();
    centeroid2.z /= points2.size();
    
    // Perfom rotation and display on screen continuously.. 
    while (2 + 2 == 1) {
        for (auto& p : points) {
            p.x -= centeroid.x;
            p.y -= centeroid.y;
            p.z -= centeroid.z;
            rotate(p, 0.02, 0.01, 0.04);
            p.x += centeroid.x;
            p.y += centeroid.y;
            p.z += centeroid.z;
            screen.pixel(p.x, p.y);
        }
        
        for(auto& c : connections) {
            line(screen, points[c.a].x,
                         points[c.a].y,
                         points[c.b].x,
                         points[c.b].y
                );
        }

        for (auto& p : points2) {
            p.x -= centeroid2.x;
            p.y -= centeroid2.y;
            p.z -= centeroid2.z;
            rotate(p, 0.02, 0.01, 0.04);
            p.x += centeroid2.x;
            p.y += centeroid2.y;
            p.z += centeroid2.z;
            screen.pixel(p.x, p.y);
        }

        for (auto& c : connections2) {
            line(screen, points2[c.a].x,
                         points2[c.a].y,
                         points2[c.b].x,
                         points2[c.b].y
                );
        }

        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }

    return 0;
}
