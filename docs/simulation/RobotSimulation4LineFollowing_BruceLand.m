
%=============================================
% robot line following simulator
% Bruce Land, BRL4@cornell.edu
% For ECE3400
%
% Assumes binary sensors, but you can change that.
% You can change robot size, sensor spacing, 
clear all
clc
figure(1); clf;

dt = 1e-3; % sec
time_end = 20  ;
time = 0:dt:time_end;
% subscript identifieers
x=1; y=2;


% line structure
line_width = 0.5 ; %cm 1/2 line width, centered along y-axis

% init position off-center on line 
robot_pos = [0.2,0];
robot_direction = [1, 0]; % normal vector to axle: facing positive-y

plot_size = 10;
% the line
rectangle('Position', [-line_width -plot_size line_width*2 plot_size*time_end], ...
    'facecolor', 'k')
hold on
% raw the robot position and axes
robot_handle = plot(robot_pos(x), robot_pos(y), 'gx', 'markersize',10);
set(gca, 'xlim', [-plot_size plot_size])
set(gca, 'ylim', [-plot_size plot_size])
line([0 0], [-plot_size, plot_size]);
line([-plot_size, plot_size], [0 0]);

%wheel positions
axle_length = 5; %cm
left_wheel_pos = [-axle_length+robot_pos(x), 0];
right_wheel_pos = [axle_length+robot_pos(x), 0];
% draw axle
axle_handle = line([left_wheel_pos(x),right_wheel_pos(x)],...
                    [left_wheel_pos(y),right_wheel_pos(y)], 'Color','k') ;

% init sensor position
line_sensor_lateral_dist = 0.55 ;% cm 1/2 dist
line_sensor_lead = 5; % cm ahead of wheels, centered between wheels
sensor_left_position = robot_pos + [-line_sensor_lateral_dist, line_sensor_lead];
sensor_right_position = robot_pos + [line_sensor_lateral_dist, line_sensor_lead];
% draw sensors
left_handle = plot(sensor_left_position(x), sensor_left_position(y),'.r', 'markersize',10);
right_handle = plot(sensor_right_position(x), sensor_right_position(y),'.r', 'markersize',10);

% assume binary line sensors
% on line = one output
% off line = zero output
sensor_left_value = 0 ; %left of path
sensor_right_value = 0 ; %right of path

% init wheel speeds 
% THIS is what you can actually control!
base_wheel_speed = 5.; 
left_wheel_speed = base_wheel_speed; % cm/sec (start with 10% error
right_wheel_speed = base_wheel_speed;

%         s1
%==========>>>motion direction=============================
%         s2

for t=1:length(time)
    
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   % change the following physics at your own risk
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   
   % update wheel position based on current speed and direction
   left_wheel_pos = left_wheel_pos + dt * left_wheel_speed * robot_direction ;
   right_wheel_pos = right_wheel_pos + dt * right_wheel_speed * robot_direction ;
   
   % update robot_pos based on new wheel positions
   % half way between the two wheels
   robot_pos = 0.5 * (left_wheel_pos + right_wheel_pos);
   
   % update normal direction vector
   axle_delta = left_wheel_pos - right_wheel_pos;
   axle_direction = axle_delta/norm(axle_delta);
   robot_direction = [axle_delta(y), -axle_delta(x)]/norm(axle_delta);
   % x' = x cos(t) - y sin(t)
   % y' = x sin(t) + y cos(t)
   %rotate_matrix = [robot_direction; axle_direction];
   rotate_matrix = [-axle_direction; robot_direction ];
   
   % update sensor positions based on new robot_pos and new normal to axle
   sensor_left_position = robot_pos + ...
                [-line_sensor_lateral_dist, line_sensor_lead]*rotate_matrix;
   sensor_right_position = robot_pos + ...
                 [line_sensor_lateral_dist, line_sensor_lead]*rotate_matrix;
   
   %plot
   %plot(robot_pos(x), robot_pos(y),'g.')
   set(robot_handle, 'xdata', robot_pos(x), 'ydata', robot_pos(y))
   %plot(sensor_left_position(x), sensor_left_position(y),'r.')
   set(left_handle, 'xdata', sensor_left_position(x), 'ydata', sensor_left_position(y))
   %plot(sensor_right_position(x), sensor_right_position(y),'.')
   set(right_handle, 'xdata', sensor_right_position(x), 'ydata', sensor_right_position(y))
   set(axle_handle, 'xdata', [left_wheel_pos(x),right_wheel_pos(x)],...
                    'ydata', [left_wheel_pos(y),right_wheel_pos(y)]) ;
   set(gca, 'ylim', [robot_pos(y)-plot_size robot_pos(y)+plot_size])
   drawnow
   %pause(.1)
   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   % Sensor section
   % You can change this for analog sensors
   %
   % read left sensor
   if (sensor_left_position(x) < line_width & ...
       sensor_left_position(x) > -line_width )
    sensor_left_value = 1;
   else sensor_left_value = 0;
   end
   % the sensor color
   if (sensor_left_value == 1)
       set(left_handle, 'color', [0 1 0])
   else
       set(left_handle, 'color', [1 0 0])
   end
   
   % read right sensor 
   if (sensor_right_position(x) < line_width & ...
       sensor_right_position(x) > -line_width )
    sensor_right_value = 1;
   else sensor_right_value = 0;
   end
   % the sensor color
   if (sensor_right_value == 1)
       set(right_handle, 'color', [0 1 0])
   else
       set(right_handle, 'color', [1 0 0])
   end 
   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   % CONTROL SECTION -- MODIFY THIS
   %use sensor input to get new wheel speeds
   % only update every 20 mSec to simulate PWM limitation
   % noise_level simulates irregular motor speed and surface conditions
   
   dv = 0.2; % 
   noise_level = 1.0;
    if (sensor_left_value == 1 & mod(t,20)==0)
        left_wheel_speed = left_wheel_speed - dv;  
    elseif (sensor_left_value == 0 & mod(t,20)==0) 
        left_wheel_speed = base_wheel_speed + randn()*noise_level;
    end
     
    if (sensor_right_value == 1 & mod(t,20)==0) 
        right_wheel_speed = right_wheel_speed - dv;
    elseif (sensor_right_value == 0 & mod(t,20)==0)
        right_wheel_speed = base_wheel_speed + randn()*noise_level;
    end
    
   %%% END CONTROL SECTION %%%%%%%%%%%%%%%%%%%%
   
   sensor_left_value_last = sensor_left_value;
   sensor_right_value_last = sensor_right_value;  
   
end %time



