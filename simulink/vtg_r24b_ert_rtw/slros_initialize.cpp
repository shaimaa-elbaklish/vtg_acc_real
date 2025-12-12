#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "vtg_r24b";

// For Block vtg_r24b/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_1;

// For Block vtg_r24b/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_2;

// For Block vtg_r24b/Subscribe2
SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_48;

// For Block vtg_r24b/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Pub_vtg_r24b_9;

// For Block vtg_r24b/Publish1
SimulinkPublisher<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Pub_vtg_r24b_75;

// For Block vtg_r24b/Get Parameter
SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_18;

// For Block vtg_r24b/Get Parameter1
SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_19;

// For Block vtg_r24b/Get Parameter2
SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_52;

// For Block vtg_r24b/Get Parameter3
SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_54;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

