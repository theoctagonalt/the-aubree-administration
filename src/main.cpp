#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

int game_time = 0;
void opcontrol(){
	while(true){
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(throttle, turn, false, 0.6f);

    //intake 
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle();
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
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

    //arm
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2)){
      int current_state = Arm::get_state();
      if(current_state == SCORING){
        Arm::set_state(REST);
      }else{
        Arm::set_state(current_state++);
      }
    }

    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)){
      int current_state = Arm::get_state();
      if(current_state != REST){
        Arm::set_state(current_state++);
      }
    }

    if(master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_UP)){
      Arm::manual_control(0, true);
    }else{
      Arm::manual_control(0, false);
    }

    if(master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_DOWN)){
      Arm::manual_control(1, true);
    }else{
      Arm::manual_control(1, false);
    }

    Arm::arm_pid();

    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
      game_time++;
    } 
    if(game_time == 3750){
      master.rumble("--");
    }
    pros::delay(20);
  }
}