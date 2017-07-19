%DRAW_WALLS
%   Takes in an array with wall locations for each grid space:
%   For each grid space, wall locations are represented with 4 bits:
%   [bit3 bit2 bit1 bit0] ==> [W E S N]
%   N (north wall) = 0001 in binary or 1 in decimal
%   S (south wall) = 0010 in binary or 2 in decimal
%   E (east wall)  = 0100 in binary or 4 in decimal
%   W (west wall)  = 1000 in binary or 8 in decimal
%   For example: A grid that has a wall to the north and east would have a
%   wall location of 0101 in binary or 5 in decimal
%   Draws walls in the specified locations
%   Written by ECE3400 staff for Fall 2017

function draw_walls( wall_loc )

    [num_row, num_col] = size(wall_loc);

    % Draw all walls on image
    for r = 1:num_row
        for c = 1:num_col
            wall_bin = de2bi(wall_loc(r,c), 4, 'right-msb');

            % Draw all grid lines in thin dashed black  
            line([c-0.5,c+0.5],[r-0.5,r-0.5],'color','b','linestyle', '--');
            line([c-0.5,c+0.5],[r+0.5,r+0.5],'color','b','linestyle', '--');
            line([c+0.5,c+0.5],[r-0.5,r+0.5],'color','b','linestyle', '--');
            line([c-0.5,c-0.5],[r-0.5,r+0.5],'color','b','linestyle', '--');

            % Draw all walls
            if (wall_bin(1) == 1) % NORTH wall
                line([c-0.5,c+0.5],[r-0.5,r-0.5],'color','r','linewidth', 3);
            end
            if (wall_bin(2) == 1) % SOUTH wall
                line([c-0.5,c+0.5],[r+0.5,r+0.5],'color','r','linewidth', 3);
            end
            if (wall_bin(3) == 1) % EAST wall
                line([c+0.5,c+0.5],[r-0.5,r+0.5],'color','r','linewidth', 3);
            end
            if (wall_bin(4) == 1) % WEST wall
                line([c-0.5,c-0.5],[r-0.5,r+0.5],'color','r','linewidth', 3);
            end
        end
    end
end

