#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "initialize.h"

namespace Intake{
  int hooks_state = OFF;
  int preroller_stage = OFF;
  int target_colour;
  int last_colour;
  int timeout;

  void toggle(){
    if(hooks_state == FWD){
      set_hooks(OFF);
      set_preroller(OFF);
    }else{
      set_hooks(FWD);
      set_preroller(FWD);
    }
  }

  void set_preroller(int state){
    if(state == FWD){
      preroller_motor.move_velocity(200);
      preroller_stage = FWD;
    }else if(state == REV){
      preroller_motor.move_velocity(-200);
      preroller_stage = REV;
    }else{
      preroller_motor.move_velocity(0);
      preroller_stage = OFF;
    }
  }

  void set_hooks(int state){
    if(state == FWD){
      hooks_motor.move_velocity(200);
      hooks_state = FWD;
    }else if(state == REV){
      hooks_motor.move_velocity(-200);
      hooks_state = REV;
    }else{
      hooks_motor.move_velocity(0);
      hooks_state = OFF;
    }
  }

  int get_hooks(){
    return hooks_state;
  }
  int get_preroller(){
    return preroller_stage;
  }

  void update_intake(){
    double current_hue = intake_colour.get_hue();
    if(current_hue < RED_HUE_MAX && current_hue > RED_HUE_MIN){
      last_colour = RED;
    }else if(current_hue < BLUE_HUE_MAX && current_hue > BLUE_HUE_MIN){
      last_colour = BLUE;
    }
    //TODO: INSERT CODE FOR COLOUR SORT & AUTO INTAKE TURN OFF
    if(intake_switch.get_value()){
      if(last_colour != target_colour && hooks_state == FWD && timeout == 0 && last_colour != -1){
        master.rumble("...");
        set_hooks(OFF);
        timeout++;
        last_colour = -1;
      }
    }
    if(timeout > 0){
      timeout++;
      if(timeout > 15 && hooks_state == OFF){
        timeout = 0;
        set_hooks(FWD);
      }
    }
  }

  void set_target_colour(int colour){
    target_colour = colour;
  }
  int get_target_colour(){
    return target_colour;
  }
}