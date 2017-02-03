#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int num_rows, num_columns;
bool grid[25][25];         // 1 = wall, 0 = empty
vector <int> room_sizes;

int find_room_size (int row, int column) {
    // Wall or out of bounds
    if (grid[row][column] ||
        row < 0 || row == num_rows ||
        column < 0 || column == num_columns)
        return 0;

    // This space has been accounted for
    grid[row][column] = true;

    // Search in 4 directions
    return find_room_size(row,column+1) + find_room_size(row+1,column) +
           find_room_size(row,column-1) + find_room_size(row-1,column) + 1;
}

int main()
{
   int flooring, rooms_installed = 0;
   char input;
   scanf("%d%d%d",&flooring,&num_rows,&num_columns);

   // Input
   for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            scanf(" %c",&input);
            if (input == 'I')
                grid[i][j] = true;
        }
   }

   // Find rooms and add to vector
   for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            // Room is found
            if (grid[i][j] == false)
                room_sizes.push_back(find_room_size(i,j));
        }
   }

   // Sort in decreasing order
   sort (room_sizes.begin(), room_sizes.end(), greater<int>());

   // Subtract area of largest rooms
   for (int i = 0; i < room_sizes.size(); i++) {
        if (room_sizes[i] > flooring)
            break;
        flooring -= room_sizes[i];
        rooms_installed++;
   }

   if (rooms_installed == 1)
        printf("%d room, %d square metre(s) left over", rooms_installed, flooring);
   else
        printf("%d rooms, %d square metre(s) left over", rooms_installed, flooring);
}
