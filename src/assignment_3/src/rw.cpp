#include "../include/assignment_3/rw.h"

ros::Publisher vel;

void scan_callback (const sensor_msgs::LaserScan::ConstPtr& scan_msg){
    
}

void random_walk(){
    while(ros::ok()){
        RUN(randomInt(1,10));
        TURN_RANDOM();
    }
}


int main(int argc, char **argv){
    string node_name = "RandomWalker";
    string vel_topic_name = "/mobile_base/commands/velocity";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;
    vel = n.advertise<geometry_msgs::Twist>(vel_topic_name, 1000);
    // ros::Subscriber scan_sub = n.subscribe("scan", 1, random_walk);
    random_walk();
    
    
    return 0;
}
