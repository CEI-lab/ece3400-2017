% Bruce Land
% robot simulator
clear all;
figure(1); clf;
clc;

dt = 0.1; % sec
time_end = 100 ;
time = 0:dt:time_end;

%maze structure maze(x,y)
% walls on odd indexs
wall = 1; % zero means no wall
no_wall = 0;
robot = 2;
% start with no walls
maze = zeros(11,11) ;
% wall around the whole maze
maze(:,1) = wall;
maze(:,11) = wall;
maze(1,:) = wall;
maze(11,:) = wall;
% interior walls
maze(1:5,3) = wall;
maze(7:11,3) = wall;
maze(5,3:7) = wall ;
maze(7,3:5) = wall ;
maze(7,6:7) = wall ; %%
maze(9,3:9) = wall ;
maze(9,3:9) = wall ;
maze(4:8,9) = wall ;
maze(1:3,5) = wall ;
maze(1:3,7) = wall ;
% imagesc(maze)
% axis xy
% return
% init state to first intersection 
% inside the lower left corner
robot_x_pos = 2;
robot_y_pos = 2;
maze(robot_y_pos,robot_x_pos) = robot;
%==========================================
% orientation  0--facing +y direction
%            3   1--facing +x direction
%              2
%==========================================
robot_orient = 0;
% first step is always up
x_inc = 0; y_inc = 1;

imagesc(maze)
robot_eyes = text(1.9,2.3,'O');
colormap spring
xlabel 'x'
ylabel 'y'
axis tight
axis xy

%assume distance sensors

for t=time
   %update sensors -- body centered coods
   if (robot_orient==0)
       right_wall_sensor = maze(robot_y_pos, robot_x_pos+1);
       left_wall_sensor = maze(robot_y_pos, robot_x_pos-1);
       front_wall_sensor = maze(robot_y_pos+1, robot_x_pos);
       
   elseif (robot_orient==1)
       right_wall_sensor = maze(robot_y_pos-1, robot_x_pos);
       left_wall_sensor = maze(robot_y_pos+1, robot_x_pos);
       front_wall_sensor = maze(robot_y_pos, robot_x_pos+1);
       
   elseif (robot_orient==2)
       right_wall_sensor = maze(robot_y_pos, robot_x_pos-1);
       left_wall_sensor = maze(robot_y_pos, robot_x_pos+1);
       front_wall_sensor = maze(robot_y_pos-1,robot_x_pos);
       
   elseif (robot_orient==3)  
       right_wall_sensor = maze(robot_y_pos+1, robot_x_pos);
       left_wall_sensor = maze(robot_y_pos-1, robot_x_pos);
       front_wall_sensor = maze(robot_y_pos, robot_x_pos-1);
   end
   
   % erase old robot location
   maze(robot_y_pos,robot_x_pos) = no_wall;
   
   % steering algorithm -- NEEDS WORK
   turning = 0;
   if(right_wall_sensor==no_wall) % turn right
       robot_orient = mod(robot_orient+1,4);
       front_wall_sensor=no_wall;
       turning=0;
   elseif (left_wall_sensor==no_wall) % turn left
       robot_orient = mod(robot_orient+3,4);
       front_wall_sensor=no_wall;
       turning=0;
   elseif (left_wall_sensor==wall && ... %turn around
            right_wall_sensor==wall && ...
            front_wall_sensor==wall) 
       robot_orient = mod(robot_orient+2,4) ; 
       front_wall_sensor=no_wall;
       turning=0;
   end
   
   % motion settings
   if (robot_orient==0)
       x_inc = 0; y_inc = 1;
       eye_x = -.1 ; eye_y=0.3;
   elseif (robot_orient==1)
       x_inc = 1; y_inc = 0;
       eye_x = .3 ; eye_y=0.1;
   elseif (robot_orient==2)
       x_inc = 0; y_inc = -1;
       eye_x = 0 ; eye_y=-0.3;
   elseif (robot_orient==3)
       x_inc = -1; y_inc = 0;
       eye_x = -0.5 ; eye_y=-0.1;
   end
   
  if(front_wall_sensor==no_wall && turning==0) % just advance
       robot_y_pos = robot_y_pos + y_inc
       robot_x_pos = robot_x_pos + x_inc
       maze(robot_y_pos,robot_x_pos) = robot; 
  end
  
   % draw it
   imagesc(maze)
   robot_eyes = text(robot_x_pos+eye_x,robot_y_pos+eye_y,'O');
   colormap spring
xlabel 'x'
ylabel 'y'
axis tight
axis xy
   drawnow
   pause(1.0)
  
end %time



