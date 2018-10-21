#include "plan_handler.h"

PlanHandler::PlanHandler(){

	this->action_feedback = nh_.advertise<rosplan_dispatch_msgs::ActionFeedback>("/rosplan_plan_dispatcher/action_feedback", 1);
	this->pub_action = nh_.advertise<rosplan_dispatch_msgs::ActionDispatch>("/rosplan_plan_dispatcher/action_dispatch", 1);
	this->plan = nh_.subscribe<rosplan_dispatch_msgs::EsterelPlan>("/rosplan_parsing_interface/complete_plan", 1, &PlanHandler::CompletePlan, this);
	this->action_status = nh_.subscribe<std_msgs::String>("/action_status", 1, &PlanHandler::ActionStatus, this);
	this->action_dispatch = nh_.subscribe<rosplan_dispatch_msgs::ActionDispatch>("/rosplan_plan_dispatcher/action_dispatch", 1, &PlanHandler::HandleAction, this);
	this->map_markers = nh_.serviceClient<qualification_video::GoToMarker>("/map_marker/go_to_marker");
}

PlanHandler::~PlanHandler(){}


void PlanHandler::CompletePlan(const rosplan_dispatch_msgs::EsterelPlanConstPtr& plan){

	rosplan_dispatch_msgs::ActionDispatch action;
	rosplan_dispatch_msgs::EsterelPlan plan_holder = *plan;
	plan_holder.nodes.erase(plan_holder.nodes.begin());
	this->complete_plan.push_back(plan_holder.nodes[0].action);

	std::vector<rosplan_dispatch_msgs::EsterelPlanNode>::iterator it = plan_holder.nodes.begin();
	std::vector<rosplan_dispatch_msgs::EsterelPlanNode>::iterator end = plan_holder.nodes.end();
	int current_action = 0;
	while(it != end){

		if(it->action.action_id == (current_action + 1)){
			this->complete_plan.push_back(it->action);
			current_action = current_action + 1;
		}
		it++;
	}
	std::vector<rosplan_dispatch_msgs::ActionDispatch>::iterator it_ = this->complete_plan.begin();
	std::vector<rosplan_dispatch_msgs::ActionDispatch>::iterator end_ = this->complete_plan.end();
	this->complete_plan.erase(this->complete_plan.begin());

}

void PlanHandler::ActionStatus(const std_msgs::StringConstPtr& str){


	if(str->data == "action achieved") {

		if(!this->complete_plan.empty()){
			rosplan_dispatch_msgs::ActionDispatch action = *this->complete_plan.begin();
			this->pub_action.publish(action);
			this->complete_plan.erase(this->complete_plan.begin());

		}
	}
}

void PlanHandler::HandleAction(const rosplan_dispatch_msgs::ActionDispatchConstPtr& action){

	if(action->name == "goto_waypoint"){

		std_msgs::String destination; 
		destination.data = action->parameters[2].value;
		std::cout << destination << " ROOM " << std::endl;
		qualification_video::GoToMarker nav_point;
		nav_point.request.marker = destination.data;
		ros::service::waitForService("/map_marker/go_to_marker", ros::Duration(2));
		this->map_markers.call(nav_point);
		
	}

	else if(action->name == "grasp"){

		std::cout << "GRASP RECEIVED " << std::endl;
		//Call grasp function here
	}
	else if(action->name == "speech"){

		std::cout << "SPEECH RECEIVED " << std::endl;
		//Call output speech here
	}

	else{

		ROS_ERROR("That is not a command that I recognise");
	}
}