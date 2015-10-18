#include "../include/assignment_3/rw.h"
#define WALL_RANGE_THRESHOLD 2.5
ros::Publisher vel;
bool wall = false;


bool has_wall(vector<float> range){
    float range_avg = avg(range); ROS_INFO("range average = %f", range_avg);   
    return (range_avg >= WALL_RANGE_THRESHOLD) ? false : true;
}

void scan_callback (const sensor_msgs::LaserScan::ConstPtr& scan_msg){        
    wall = has_wall(scan_msg->ranges);
}

void random_walk(){
    while(ros::ok()){
        if(wall){
            ROS_INFO("Turning");
            TURN_RANDOM();
            // RUN(5);
        }else{
            ROS_INFO("Running");
            RUN(2);           
        }                
    }
}


int main(int argc, char **argv){
    string node_name = "RandomWalker";
    string vel_topic_name = "/mobile_base/commands/velocity";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;
    vel = n.advertise<geometry_msgs::Twist>(vel_topic_name, 1000);
    ros::Subscriber scan_sub = n.subscribe("scan", 1, scan_callback);
    random_walk();      
    return 0;
}
