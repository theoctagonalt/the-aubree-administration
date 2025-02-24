#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "lemlib/api.hpp"
#include "devices.h"
#include "autonomous.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./autos/pos.h"
#include "./autos/neg.h"
#include "./autos/skills.h"

void screen() {
	// loop forever
	while (true) {
			lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
			pros::lcd::print(0, "x: %f", pose.x); // print the x position
			pros::lcd::print(1, "y: %f", pose.y); // print the y position
			pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
			pros::delay(50);
	}
}
void update_subsystems() {
	while(pros::competition::is_autonomous()){
		Intake::update_intake();
		Arm::arm_pid();
		pros::delay(5);
	}
}

void autonomous() {
  Intake::set_target_colour(get_colour());
  int routine = get_routine();
	pros::Task screen_task(screen);
	pros::Task subsystems_task(update_subsystems);
	if(routine == POS){
		pos_route();
	}	else if(routine == NEG){
		neg_route();
	}	else if(routine == SKILLS){
		skills_route();
	}else if(routine == DRIVE_FORWARD){
		chassis.setPose(0, 0, 90);
		chassis.moveToPoint(24, 0, 3000);
	}
}