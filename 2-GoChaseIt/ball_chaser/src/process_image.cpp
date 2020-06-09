#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z) {

    // Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service safe_move");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img) {

    int white_pixel = 255;
    float lin_x = 0.0, ang_z = 0.0;
    bool white_ball_found = false;
    int row_number = -1;

    // Loop through each pixel in the image and check if there's a bright white one
    for(int i = 0; i < img.height * img.step; i++){
        if(img.data[i] == white_pixel){
            row_number = i % img.step;
	    white_ball_found = true;
	    break;
        }
    }

    // Then, identify if this pixel falls in the left, mid, or right side of the image
    if(row_number <= img.step / 3 && row_number >= 0){
        // Left
        lin_x = 0.0;
        ang_z = 0.2;
    } else if (row_number >= img.step * 2/3){
        // Right
        lin_x = 0.0;
        ang_z = -0.2;
    } else {
        // Center
        lin_x = 0.5;
        ang_z = 0.0;
    }

    // Request a stop when there's no white ball seen by the camera
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    if (white_ball_found) {
	ROS_INFO_STREAM("White Ball FOUND: The bot will move towards it.");
    	drive_robot(lin_x, ang_z);
    } else {
        ROS_INFO_STREAM("White Ball NOT FOUND: The bot will not move.");
	drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv) {
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
