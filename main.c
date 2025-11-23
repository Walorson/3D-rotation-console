#include <stdio.h>
#include <math.h>
#include <windows.h>

#define SIZE 24
#define CANVAS_X 40
#define CANVAS_Y 40
#define F 240

char cube[SIZE][SIZE][SIZE];
char canvas[CANVAS_Y][CANVAS_X];

void plot(double x, double y, char c)
{
    short X = (short)(x + CANVAS_X / 4);
    short Y = (short)(y + CANVAS_Y / 4);
    //printf("X: %hd\nY: %hd\n\n", X, Y);
    if(X >= 0 && X < CANVAS_X && Y >= 0 && Y < CANVAS_Y)
        canvas[Y][X] = c;
}

void fillCanvas(char c)
{
    for(unsigned char y = 0; y < CANVAS_Y; y++)
    {
        for(unsigned char x = 0; x < CANVAS_X; x++)
        {
            canvas[y][x] = c;
        }
    }
}

void renderCanvas()
{
    for(unsigned char y = 0; y < CANVAS_Y; y++)
    {
        for(unsigned char x = 0; x < CANVAS_X; x++)
        {
            printf("%c ", canvas[y][x]);
        }
        printf("\n");
    }
}

short center_x, center_y, center_z;
void drawCube(char c)
{
    for(unsigned char z = 0; z < SIZE; z++)
    {
        for(unsigned char y = 0; y < SIZE; y++)
        {
            for(unsigned char x = 0; x < SIZE; x++)
            {
                if(z == 0 || z == SIZE - 1)
                {
                    if(y == 0 || y == SIZE - 1)
                        cube[z][y][x] = c;

                    else if(x == 0 || x == SIZE -1)
                        cube[z][y][x] = c;
                }
                else
                {
                    if((y == 0 || y == SIZE - 1) && (x == 0 || x == SIZE -1))
                        cube[z][y][x] = c;
                }
            }
        }
    }
    center_x = SIZE / 2;
    center_y = SIZE / 2;
    center_z = SIZE / 2;
}

void renderSlices()
{
    for(unsigned char z = 0; z < SIZE; z++)
    {
        printf("SLICE %hhu\n", z + 1);
        for(unsigned char y = 0; y < SIZE; y++)
        {
            for(unsigned char x = 0; x < SIZE; x++)
            {
                printf("%c ", cube[z][y][x]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

double px, py, scale;
double yx, zx, xy, zy, xz, yz;
short new_x, new_y, new_z;

void rotate(double deg, char c)
{
    deg = (M_PI * deg) / 180;
    for(unsigned char z = 0; z < SIZE; z++)
    {
        for(unsigned char y = 0; y < SIZE; y++)
        {
            for(unsigned char x = 0; x < SIZE; x++)
            {
                if(cube[z][y][x] == c)
                {
                    new_x = x - center_x;
                    new_y = y - center_y;
                    new_z = z - center_z;

                    //X rotate
                    yx = new_y  * cos(deg) - new_z * sin(deg);
                    zx = new_y * sin(deg) +  new_z * cos(deg);

                    //Y rotate
                    xy =  new_x * cos(deg) + new_z * sin(deg);
                    zy = -new_x * sin(deg) + new_z * cos(deg);

                    //Z rotate
                    xz = new_x * cos(deg) - new_y * sin(deg);
                    yz = new_x * sin(deg) + new_y * cos(deg);

                    xy += center_x;
                    zy += center_z;
                    zx += center_z;
                    yx += center_y;
                    xz += center_x;
                    yz += center_y;

                    //Project
                    px = F * (xy / (zy + F));
                    py = F * (yz / (z + F));

                    //printf("PX: %lf\nPY: %lf\n\n", xy, yx);

                    plot(px, py, c);
                }
            }
        }
    }
}

int main()
{
    fillCanvas(' ');
    drawCube('@');

    for(short i = 5; i <= 1024; i += 5)
    {
        system("cls");
        rotate(i, '@');
        renderCanvas();
        Sleep(42);
        fillCanvas(' ');
    }

    return 0;
}
