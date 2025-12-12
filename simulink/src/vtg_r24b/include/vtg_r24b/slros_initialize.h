#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "vtg_r24b_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block vtg_r24b/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_1;

// For Block vtg_r24b/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_2;

// For Block vtg_r24b/Subscribe2
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Sub_vtg_r24b_48;

// For Block vtg_r24b/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Pub_vtg_r24b_9;

// For Block vtg_r24b/Publish1
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_vtg_r24b_std_msgs_Float64> Pub_vtg_r24b_75;

// For Block vtg_r24b/Get Parameter
extern SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_18;

// For Block vtg_r24b/Get Parameter1
extern SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_19;

// For Block vtg_r24b/Get Parameter2
extern SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_52;

// For Block vtg_r24b/Get Parameter3
extern SimulinkParameterGetter<real64_T, double> ParamGet_vtg_r24b_54;

void slros_node_init(int argc, char** argv);

#endif
