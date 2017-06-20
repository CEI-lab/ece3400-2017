//=======================================================
// ECE3400 Fall 2017
// Lab 3: VGA Driver
//
// THIS PROJECT DEVELOPED BY CORNELL ECE 3400 STAFF. PLEASE
// DO NOT REUSE OR DISTRIBUTE THIS CODE WITHOUT PERMISSION

//=======================================================
`define TOTAL_SCREEN_WIDTH 795
`define TOTAL_SCREEN_HEIGHT 525
`define VISIBLE_SCREEN_WIDTH 640
`define VISIBLE_SCREEN_HEIGHT 480

module VGA_DRIVER (
	RESET,
	CLOCK,
	PIXEL_COLOR_IN,
	PIXEL_X,
	PIXEL_Y,
	PIXEL_COLOR_OUT,
	H_SYNC_NEG,
	V_SYNC_NEG
);

/******
* I/O *
******/

input CLOCK; //PIXEL CLOCK - DRIVE AT 25MHZ for 60 Hz 640 x 480 VGA
input RESET;
input  [7:0] PIXEL_COLOR_IN; //COLOR GIVEN TO THE VGA DRIVER


output [9:0] PIXEL_X; //HORIZONTAL POSITION OF THE NEXT PIXEL;
output [9:0] PIXEL_Y; //VERTICLE POSITION OF THE NEXT PIXEL;
output [7:0] PIXEL_COLOR_OUT; //COLOR TO BE DISPLAYED
output       H_SYNC_NEG; //THE REVERSE POLARITY HORIZONTAL SYNC SIGNAL
output       V_SYNC_NEG; //THE REVERSE POLARITY VERTICAL SYNC SIGNAL

/****************************
* MEMORY AND INTERNAL WIRES *
*****************************/

reg  [9:0] pixel_count;
reg  [9:0] line_count;

/************************
* LOGIC AND CONNECTIONS *
************************/
assign PIXEL_X    = pixel_count;
assign PIXEL_Y    = line_count;

assign PIXEL_COLOR_OUT = (pixel_count<(`VISIBLE_SCREEN_WIDTH) /*&& (line_count<`VISIBLE_SCREEN_HEIGHT)*/)
									? (PIXEL_COLOR_IN) : (8'b00000000) ; //ROUTE THE INPUT COLOR TO OUTPUT IF WITHIN VISIBLE BOUNDS
									
assign H_SYNC_NEG = (pixel_count>=656 && pixel_count<752) ? (1'b0) : (1'b1); //ACTIVATE THE H SYNC PULSE AFTER FRONT PORCH

assign V_SYNC_NEG = (line_count>=490 && line_count<492) ? (1'b0) : (1'b1); //ACTIVATE THE V SYNC PULSE AFTER FRONT PORCH

always @(posedge CLOCK) begin
	if (RESET) begin
		pixel_count <= 10'b0;
		line_count <= 10'b0;
	end
	else if (pixel_count == (`TOTAL_SCREEN_WIDTH-1)) begin
		pixel_count <= 0;
		if (line_count == (`TOTAL_SCREEN_HEIGHT-1)) begin
		line_count <= 0;
		end 
		else begin
		line_count <= line_count + 1;
		end
	end 
	else begin
		pixel_count <= pixel_count + 1;
		line_count <= line_count;
	end
end

endmodule
