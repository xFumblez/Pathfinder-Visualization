// Pathfinder Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <deque>

bool DFS_Traversal(std::vector<std::vector<char>> &map, std::vector<std::vector<bool>> &visited, int x_coord, int y_coord)
{

    if (x_coord >= map[0].size() || y_coord >= map.size()
        || x_coord < 0 || y_coord < 0
        || visited[y_coord][x_coord] || map[y_coord][x_coord] == '#')
    {
        // base case for false return, if out of map range, if tile has been visited already, and if tile has a wall
        return false;
    }

    // sets current tile to visited
    visited[y_coord][x_coord] = true;

    if (map[y_coord][x_coord] == 'G')
    {
        // if goal has been reached start recursive true return
        return true;
    }

    if (DFS_Traversal(map, visited, x_coord + 1, y_coord))
    {
        // unless the starting position, draw the > symbol to indicate path went to the right from here
        if (map[y_coord][x_coord] != 'S')
            map[y_coord][x_coord] = '>';
        return true;
    }
    else if (DFS_Traversal(map, visited, x_coord - 1, y_coord))
    {
        // indicate path went to the left from here
        if (map[y_coord][x_coord] != 'S')
            map[y_coord][x_coord] = '<';
        return true;
    }
    else if (DFS_Traversal(map, visited, x_coord, y_coord + 1))
    {
        // indicate path went down from here
        if (map[y_coord][x_coord] != 'S')
            map[y_coord][x_coord] = 'v';
        return true;
    }
    else if (DFS_Traversal(map, visited, x_coord, y_coord - 1))
    {
        // indicate path went up from here
        if (map[y_coord][x_coord] != 'S')
            map[y_coord][x_coord] = '^';
        return true;
    }

    return false;

}

void print_map(std::vector<std::vector<char>>& map)
{
    int rows = (int)map.size();
    int columns = (int)map[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

bool BFS_Traversal(std::vector<std::vector<char>> &map, std::vector<std::vector<bool>> &visited, int start_x, int start_y)
{
    bool reached_goal = false;

    std::deque<int> x_queue;
    std::deque<int> y_queue;

    x_queue.push_back(start_x);
    y_queue.push_back(start_y);
    visited[start_y][start_x] = true;

    int cur_x = x_queue.front();
    int cur_y = y_queue.front();
    int x_dir[4] = {1, -1, 0, 0};
    int y_dir[4] = {0, 0, 1, -1};

    while (!x_queue.empty())
    {
        cur_x = x_queue.front();
        cur_y = y_queue.front();
        
        x_queue.pop_front();
        y_queue.pop_front();

        if (map[cur_y][cur_x] == 'G')
        {
            reached_goal = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int new_x = cur_x + x_dir[i];
            int new_y = cur_y + y_dir[i];

            if (new_x < 0 || new_y < 0)
                continue;
            if (new_x >= map[0].size() || new_y >= map.size())
                continue;
            if (visited[new_y][new_x] || map[new_y][new_x] == '#')
                continue;

            x_queue.push_back(new_x);
            y_queue.push_back(new_y);
            visited[new_y][new_x] = true;
        }

    }

    return reached_goal;
}

void generate_walls(std::vector<std::vector<char>>& map)
{
    // randomly generates walls '#' based on a random integer between 0 and 100, puts a '.' for all other spaces

    int rows = (int)map.size();
    int columns = (int)map[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int random_int = rand() % 100 + 1;
            if (random_int % 4 == 0)
            {
                map[i][j] = '#';
            }
            else
            {
                map[i][j] = '.';
            }
        }
    }
}

// Main map function with random map size and locations
void loop(char traversal_choice)
{
    int map_rows = rand() % 50 + 1;
    int map_columns = rand() % 50 + 1;

    printf("Current Map Size: %d X %d\n", map_columns, map_rows);

    std::vector<std::vector<char>> map(map_rows, std::vector<char>(map_columns));
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

    int start_x = rand() % map[0].size();
    int start_y = rand() % map.size();

    generate_walls(map);

    printf("Current Starting Location: (%d, %d)\n", start_x, start_y);

    map[start_y][start_x] = 'S';

    int end_x = rand() % (int)map[0].size();
    int end_y = rand() % (int)map.size();

    while (end_x == start_x && end_y == start_y)
    {
        end_x = rand() % (int)map[0].size();
        end_y = rand() % (int)map.size();
    }

    printf("Current Goal Location: (%d, %d)\n\n", end_x, end_y);

    map[end_y][end_x] = 'G';

    bool result = false;

    if (traversal_choice == '1')
    {
        result = DFS_Traversal(map, visited, start_x, start_y);
    }
    else
    {
        result = BFS_Traversal(map, visited, start_x, start_y);
    }
        

    if (result)
    {
        printf("Map has been successfully traversed.\n");
    }
    else
    {
        printf("Map could not be traversed.\n");
    }
    print_map(map);

    printf("-----------------------------------------------\n");
    printf("-----------------------------------------------\n");
}

// Main map creation and display function with chosen locations
void loop(int start_x, int start_y, int end_x, int end_y, char traversal_choice)
{
    if (start_x < 0 || start_y < 0 || end_x < 0 || end_y < 0)
    {
        printf("A chosen position value was negative. Returning.\n");
        return;
    }
    if (start_x > 50 || start_y > 50 || end_x > 50 || end_y > 50) // to help prevent stack overflow due to map size
    {
        printf("A chosen position was greater than 50. Returning.\n");
        return;
    }

    int map_rows = rand() % 50 + 1;
    int map_columns = rand() % 50 + 1;

    while (map_rows <= start_y || map_rows <= end_y)
    {
        map_rows = rand() % std::max(start_y, end_y) + 10;
    }
    while (map_columns <= start_x || map_columns <= end_x)
    {
        map_columns = rand() % std::max(start_x, end_x) + 10;
    }

    printf("Current Map Size: %d X %d\n", map_columns, map_rows);

    std::vector<std::vector<char>> map(map_rows, std::vector<char>(map_columns));
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

    generate_walls(map);

    printf("Chosen Starting Location: (%d, %d)\n", start_x, start_y);

    map[start_y][start_x] = 'S';

    printf("Chosen Goal Location: (%d, %d)\n\n", end_x, end_y);

    map[end_y][end_x] = 'G';

    bool result = false;

    if (traversal_choice == '1')
    {
        result = DFS_Traversal(map, visited, start_x, start_y);
    }
    else
    {
        result = BFS_Traversal(map, visited, start_x, start_y);
    }


    if (result)
    {
        printf("Map has been successfully traversed.\n");
    }
    else
    {
        printf("Map could not be traversed.\n");
    }
    print_map(map);

    printf("-----------------------------------------------\n");
    printf("-----------------------------------------------\n");

}

// Main map creation and display function with chosen map size and locations
void loop(int mapx_size, int mapy_size, int start_x, int start_y, int end_x, int end_y, char traversal_choice)
{
    if (mapx_size <= start_x || mapx_size <= end_x || mapy_size <= start_y || mapy_size <= end_y ||
        mapx_size <= 0 || mapy_size <= 0 || start_x < 0 || start_y < 0 || end_x < 0 || end_y < 0)
    {
        printf("Chosen map size is smaller than chosen starting and ending positions or a negative number was chosen as an option. Returning.\n");
        return;
    }
    if (mapx_size > 50 || mapy_size > 50 || start_x > 50 || start_y > 50 || end_x > 50 || end_y > 50) // to help prevent stack overflow due to map size
    {
        printf("A chosen position or map size was greater than 50. Returning.\n");
        return;
    }

    printf("Chosen Map Size: %d X %d\n", mapx_size, mapy_size);

    std::vector<std::vector<char>> map(mapy_size, std::vector<char>(mapx_size));
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

    generate_walls(map);

    printf("Chosen Starting Location: (%d, %d)\n", start_x, start_y);

    map[start_y][start_x] = 'S';

    printf("Chosen Goal Location: (%d, %d)\n\n", end_x, end_y);

    map[end_y][end_x] = 'G';

    bool result = false;

    if (traversal_choice == '1')
    {
        result = DFS_Traversal(map, visited, start_x, start_y);
    }
    else
    {
        result = BFS_Traversal(map, visited, start_x, start_y);
    }


    if (result)
    {
        printf("Map has been successfully traversed.\n");
    }
    else
    {
        printf("Map could not be traversed.\n");
    }
    print_map(map);

    printf("-----------------------------------------------\n");
    printf("-----------------------------------------------\n");
}

int main()
{
    char user_choice;
    char traversal_choice;

    do
    {
        printf("Type 1, 2, 3, or 0 and enter to choose one of the following options.\n\n");
        printf("Options:\n");
        printf("1.Randomly generate a map size, starting location, and goal location.\n");
        printf("2.Randomly generate a map size, but choose starting location and goal location.\n");
        printf("3.Choose a map size, starting location, and goal location. Walls will still be randomly generated.\n");
        printf("0.Exit program.\n");
        std::cin >> user_choice;

        if (user_choice != '1' && user_choice != '2' && user_choice != '3' && user_choice != '0')
        {
            printf("Invalid option, please choose 1, 2, 3, or 0.\n\n");
            continue;
        }
        else if (user_choice == '1')
        {
            printf("Type 1 and enter for DFS with path shown. Any other input will use BFS without path shown.\n");
            std::cin >> traversal_choice;
            loop(traversal_choice);
        }
        else if (user_choice == '2')
        {
            int map_choice[4] = {0,0,0,0};

            // Limit choice to 50 or less to help prevent stack overflow
            printf("Choose a starting x-coordinate less than or equal to 50.\n");
            std::cin >> map_choice[0];
            printf("Choose a starting y-coordinate less than or equal to 50.\n");
            std::cin >> map_choice[1];
            printf("Choose a goal x-coordinate less than or equal to 50.\n");
            std::cin >> map_choice[2];
            printf("Choose a goal y-coordinate less than or equal to 50.\n");
            std::cin >> map_choice[3];

            printf("Type 1 and enter for DFS with path shown. Any other input will use BFS without path shown.\n");
            std::cin >> traversal_choice;

            loop(map_choice[0], map_choice[1], map_choice[2], map_choice[3], traversal_choice);
        }
        else if (user_choice == '3')
        {
            int map_choice[6] = {1,1,0,0,0,0};

            // Limit choice to 50 or less to help prevent stack overflow
            printf("Choose a map x-size less than or equal to 50.\n");
            std::cin >> map_choice[0];
            printf("Choose a map y-size less than or equal to 50.\n");
            std::cin >> map_choice[1];
            printf("Choose a starting x-coordinate less than or equal to 49.\n");
            std::cin >> map_choice[2];
            printf("Choose a starting y-coordinate less than or equal to 49.\n");
            std::cin >> map_choice[3];
            printf("Choose a goal x-coordinate less than or equal to 49.\n");
            std::cin >> map_choice[4];
            printf("Choose a goal y-coordinate less than or equal to 49.\n");
            std::cin >> map_choice[5];

            printf("Type 1 and enter for DFS with path shown. Any other input will use BFS without path shown.\n");
            std::cin >> traversal_choice;

            loop(map_choice[0], map_choice[1], map_choice[2], map_choice[3], map_choice[4], map_choice[5], traversal_choice);
        }
        else if (user_choice == '0')
        {
            printf("Exiting Program.\n");
        }

    } while (user_choice != '0');
}
