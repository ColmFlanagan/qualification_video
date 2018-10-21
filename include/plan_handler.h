#include "ros/ros.h"
#include "ros/service.h"
#include "ros/service_server_link.h"
#include "ros/service_manager.h"
#include "rosplan_dispatch_msgs/ActionDispatch.h"
#include "rosplan_dispatch_msgs/ActionFeedback.h"
#include "rosplan_dispatch_msgs/EsterelPlan.h"
#include "rosplan_dispatch_msgs/EsterelPlanNode.h"
#include "qualification_video/GoToMarker.h"
#include "vector"
#include "std_msgs/String.h"
#include "iostream"


class PlanHandler{

public:
	PlanHandler();
	~PlanHandler();

private:

	ros::NodeHandle nh_;
	ros::Subscriber action_dispatch, plan, action_status;
	ros::Publisher action_feedback, navigation_pub, pub_action;
	std::vector<rosplan_dispatch_msgs::ActionDispatch> complete_plan;
	ros::ServiceClient map_markers;
	void CompletePlan(const rosplan_dispatch_msgs::EsterelPlanConstPtr& plan);

	void ActionStatus(const std_msgs::StringConstPtr&);
	void HandleAction(const rosplan_dispatch_msgs::ActionDispatchConstPtr&);
};