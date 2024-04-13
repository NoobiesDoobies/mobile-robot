#include "ros/ros.h"


class WebInterfaceNode{
    public:
        WebInterfaceNode(ros::NodeHandle nh){
            this->nh = nh;
        }
        void run(){
            ROS_INFO("Web Interface Node is running");
        }
    private:
        ros::NodeHandle nh;
};

int main(int argc, char **argv){
    ros::init(argc, argv, "web_interface_node");
    ros::NodeHandle nh;

    WebInterfaceNode web_interface_node(nh);
    web_interface_node.run();
    return 0;
}