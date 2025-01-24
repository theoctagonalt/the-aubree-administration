#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"


#include "./subsystems/intake.h"
// #include "./subsystems/arm.h"
// #include "./subsystems/mogo.h"
// #include "./subsystems/doinker.h"

int game_time = 0;
void opcontrol(){
	while(true){
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(throttle, turn, false, 0.75);

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      if(Intake::get_preroller() == OFF){
        Intake::set_preroller(FWD);
      }else{
        Intake::set_preroller(OFF);
      }
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      if(Intake::get_hooks() == REV){
        Intake::set_hooks(FWD);
      }else{
        Intake::set_hooks(OFF);
      }
    }
  }
}