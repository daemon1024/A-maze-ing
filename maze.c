#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct coordinates
{
    int x;
    int y;
} coordinates;

typedef struct cell
{
    coordinates coord;
    bool visited;
    bool wall;
} Cell;

int r = 11, c = 11, i, j;
coordinates current;
Cell **grid;
coordinates stack[100];
int avail = 0;
int count = 0;

coordinates checkneigh()
{
    int i = current.y;
    int j = current.x;
    int ncount = 0;
    coordinates neigh[4];
    if (j - 2 > 0)
    {
        Cell top = grid[j - 2][i];
        if (!top.visited)
        {
            neigh[ncount].x = top.coord.x;
            neigh[ncount].y = top.coord.y;
            ncount++;
        }
    }
    if (i + 2 < c - 1)
    {
        Cell right = grid[j][i + 2];
        if (!right.visited)
        {
            neigh[ncount].x = right.coord.x;
            neigh[ncount].y = right.coord.y;
            ncount++;
        }
    }
    if (j + 2 < r - 1)
    {
        Cell bottom = grid[j + 2][i];
        if (!bottom.visited)
        {
            neigh[ncount].x = bottom.coord.x;
            neigh[ncount].y = bottom.coord.y;
            ncount++;
        }
    }
    if (i - 2 > 0)
    {
        Cell left = grid[j][i - 2];
        if (!left.visited)
        {
            neigh[ncount].x = left.coord.x;
            neigh[ncount].y = left.coord.y;
            ncount++;
        }
    }

    if (ncount > 2)
    {
        int r = rand() % ncount;
        printf("found neighbours  \n");
        return neigh[r];
    }
    else
    {
        coordinates a;
        printf("no neighbout \n");
        a.x = -1;
        a.y = -1;
        return a;
    }
}

int generate()
{
    if (avail >= r / 2 * c / 2)
    {
        return 0;
    }
    int i = current.x;
    int j = current.y;
    coordinates next = checkneigh();
    if (next.x >= 0 && next.y >= 0)
    {
        grid[j][i].visited = true;
        // printf("%d,%d pushed to stack\n", current.x, current.y);
        // printf("stack count %d \n", count);
        count++;
        stack[count] = next;
        avail++;
        //remove the walls
        if (j - next.y < 0)
        {
            grid[j + 1][i].wall = false;
        }
        else if (j - next.y > 0)
        {
            grid[j - 1][i].wall = false;
        }
        else if (i - next.x < 0)
        {
            grid[j][i + 1].wall = false;
        }
        else if (i - next.x > 0)
        {
            grid[j][i - 1].wall = false;
        }
        current.x = next.x;
        current.y = next.y;
        generate();
    }
    else if (avail >= 0)
    {
        count--;
        printf("%d,%d popped from stack\n", current.x, current.y);
        current.x = stack[count].x;
        current.y = stack[count].y;
        printf("%d,%d reset to stack\n", current.x, current.y);
        generate();
    }
}

void printmaze()
{
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            (grid[i][j].wall) ? printf("#") : printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    // scanf("%d%d", &r, &c);
    srand(time(0));
    grid = (Cell **)malloc(sizeof(Cell *) * r);
    for (i = 0; i < r; i++)
    {
        grid[i] = (Cell *)malloc(sizeof(Cell) * c);
    }
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            grid[i][j].coord.x = i;
            grid[i][j].coord.y = j;
            if (j % 2 == 1 && i % 2 == 1)
            {
                grid[i][j].visited = false;
                grid[i][j].wall = false;
            }
            else if ((i == 0 && j == 1) || (i == r - 1 && j == c - 2))
            {
                grid[i][j].visited = false;
                grid[i][j].wall = false;
            }
            else
            {
                grid[i][j].wall = true;
            }
        }
    }
    current.x = 1;
    current.y = 1;
    grid[current.x][current.y].visited = true;
    stack[count] = current;
    generate();
    printmaze();
}