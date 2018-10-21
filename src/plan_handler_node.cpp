#include "plan_handler.h"

int main(int argc, char** argv){

	try{

		ros::init(argc, argv, "handle_plan");
		PlanHandler handle_plan;
		ros::spin();
		return 0;
	}catch(std::exception& e){

		std::cerr << "Caught std exception " << e.what() << std::endl;
	}catch(ros::Exception& e){

		std::cerr << "Caught ros exception " << e.what() << std::endl;
	}catch(...){

		std::cerr << "Caught unknown exception " << std::endl;
	}
}