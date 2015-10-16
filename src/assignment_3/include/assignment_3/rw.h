#ifndef CONTROLLER_HEADER_FILE
#define CONTROLLER_HEADER_FILE

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/console.h>
#include "geometry_msgs/Twist.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
static float TICK = 0.1;
#define DEFAULT_VEL 10
#define DEFAULT_ARG_VEL 10
#define RUN(x) run(vel,x);
#define STOP() stop(vel);
#define LEFT(x) left(vel,x);
#define RIGHT(x) right(vel,x);
#define TURN_AROUND() left(vel,30);


void tick(){
    ros::spinOnce();
    ros::Duration duration(TICK);
    duration.sleep();
}

geometry_msgs::Twist get_twist(float v,float a){
    geometry_msgs::Twist t;
    t.linear.x = v;
    t.linear.y = 0;
    t.linear.z = 0;
    t.angular.x = 0;
    t.angular.y = 0;
    t.angular.z = a;
    return t;
};

void run(ros::Publisher vel,int times = 1,float v = DEFAULT_VEL,float a = 0.0){
    int count = 0;
    while(ros::ok()){
        vel.publish(get_twist(v,a));
        tick();
        count++;
        if(count == times){
            return;
        }
    }
};

void stop(ros::Publisher vel,int times = 1){
    run(vel, times, 0.0, 0.0);
};

void left(ros::Publisher vel,int times = 1,float a = DEFAULT_ARG_VEL){
    run(vel,times,0.0, abs(a));
};

void right(ros::Publisher vel,int times = 1,float a = -DEFAULT_ARG_VEL){
    run(vel,times,0.0, -abs(a));
}



#endif /* CONTROLLER_HEADER_FILE */
