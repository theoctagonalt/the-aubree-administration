#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"


#include "./subsystems/intake.h"
// #include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

int game_time = 0;
void opcontrol(){
	while(true){
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(throttle, turn, false, 0.75);

    //intake 
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle();
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      if(Intake::get_hooks() == REV){
        Intake::set_hooks(OFF);
        Intake::set_preroller(OFF);
      }else{
        Intake::set_hooks(REV);
        Intake::set_preroller(REV);
      }
    }

    Intake::update_intake();

    //mogo
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)){
      Mogo::toggle();
    }

    //doinker
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_Y)){
      Doinker::toggle();
    }

    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
      game_time++;
    } 
    if(game_time == 4500){
      master.rumble("--");
    }
    pros::delay(20);
  }
}