%% Milestone 3: Maze mapping simulation for ECE3400, Fall 2017
%  Implements a baseline depth-first-search navigation algorithm
%  Written by Claire Chen for EC3400  
%% Maze initializations

% Initialize current location maze array
% 1 means unvisited
% 0.5 means visited
% 0 is the robot's current location

curr_loc = [...
    1 1 1 1 
    1 1 1 1
    1 1 1 1
    1 1 1 1 
    1 1 1 1];  

% Initialize array that keeps track of which grid spaces have been visited
visited_info = zeros(5,4);

% Set maze walls
% For each grid space, wall locations are represented with 4 bits:
% [bit3 bit2 bit1 bit0] ==> [W E S N]
% N (north wall) = 0001 in binary or 1 in decimal
% S (south wall) = 0010 in binary or 2 in decimal
% E (east wall)  = 0100 in binary or 4 in decimal
% W (west wall)  = 1000 in binary or 8 in decimal
% For example: A grid that has a wall to the north and east would have a
% wall location of 0101 in binary or 5 in decimal

% Some various wall configurations, for testing
% You can uncomment any of the wall_loc arrays or write your own mazes

% wall_loc = [...
%     9 1 3 5
%     8 4 11 4
%     12 10 5 12
%     8 5 14 12
%     10 2 3 6];

% wall_loc = [...
%     9 3 3 5
%     12 1 4 12
%     12 8 4 12
%     12 10 6 12
%     10 3 3 6];

wall_loc = [...
    9 1 3 5
    8 6 13 12
    12 11 6 12
    8 3 7 14
    10 3 3 7];

% User-defined color map
% 0   -> black
% 0.5 -> green
% 1   ->
map = [...
       0, 0, 0 
       0, 1, 0
       1, 1, 1];

% Draw initial grid
colormap(map);
imagesc(curr_loc);
caxis([0 1])
draw_walls(wall_loc);

%% Navigation 

% Create stack
stack = CStack();

% Starting position
start_pos = [5,4];

% Total number of steps
step_num = 0;

% DFS traverse through maze
% First, push starting position onto stack;
stack.push(start_pos);

all_visited = all(all(visited_info,1));
while (~stack.isempty || all_visited)
    step_num = step_num + 1;
    
    % Visit next pos and  mark it as visited
    curr_pos = stack.top();
    curr_r = curr_pos(1);
    curr_c = curr_pos(2);
    curr_loc(curr_r, curr_c) = 0;
    visited_info(curr_r, curr_c) = 1; 
    
    % Look for next position to visit
    % First get wall information at current location
    wall_bin = de2bi(wall_loc(curr_r,curr_c), 4, 'right-msb'); % [N S E W]
    % Next, figure out next position to be visited by: 
    % wall location and if they a lready have been visited
    % Priority: N, E, W, S
    % Don't have to check for index out of bounds errors because existence
    % of walls are always checked first
    if (wall_bin(1) == 0)
        go_north = ~visited_info(curr_r - 1, curr_c);
    else
        go_north = 0;
    end
    
    if (wall_bin(3) == 0)
        go_east  = (~visited_info(curr_r, curr_c + 1) & ~go_north);
    else 
        go_east = 0;
    end
    
    if (wall_bin(4) == 0)
        go_west  = (~visited_info(curr_r, curr_c - 1) & ~go_east);
    else
        go_west = 0; 
    end
   
    if (wall_bin(2) == 0) 
        go_south = (~visited_info(curr_r + 1, curr_c) & ~go_west);
    else
        go_south = 0;
    end
    
    if (go_north)
        next_pos = [curr_r - 1, curr_c];
        stack.push(next_pos);
    elseif (go_east)
        next_pos = [curr_r, curr_c + 1];
        stack.push(next_pos);
    elseif (go_west) 
        next_pos = [curr_r, curr_c - 1];
        stack.push(next_pos);
    elseif (go_south)
        next_pos = [curr_r + 1, curr_c];
        stack.push(next_pos);
    else
        next_pos = stack.pop;
    end

    pause(0.5)

    imagesc(curr_loc);
    caxis([0 1]); % Re-scale colormap to original scale
    draw_walls(wall_loc);
    
    % Make current position previous position
    prev_r = curr_r;
    prev_c = curr_c;
    % Save prev pos in maze array
    curr_loc(prev_r, prev_c) = 0.5;
    
    % Check if all nodes have been visited
    % If they have, stop traversing through maze
    all_visited = all(all(visited_info,1));

end

display('done!');
display(step_num);


 
