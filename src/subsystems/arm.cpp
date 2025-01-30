#include "./subsystems/arm.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "initialize.h"

namespace Arm{
  int current_state = REST;
  int target_state;
  int target_pos;

  bool pid_enabled = false;
  int error_timeout = 0;
  double accumulated_error = 0;
  double last_error = 0;

  bool manual_control_up = false;
  bool manual_control_down = false;

  void set_state(int state){
    target_state = state;
    pid_enabled = true;
    target_pos = arm_state_values[target_state];
    for(int i = 0; i<=state; i++){
      master.rumble(".");
    }
  }
  int get_state(){
    return current_state;
  }

  void manual_control(int direction, bool value){
    if(direction == 0 && manual_control_up != value){
      if(value){
        arm_motor.move_velocity(200);
        pid_enabled = false;
        manual_control_up = true;
      }else{
        manual_control_up = false;
        arm_motor.move_velocity(0);
        pid_enabled = true;
        target_pos = arm_sensor.get_angle() / 100.0;
      }
    }else if(direction == 1 && manual_control_down != value){
      if(value){
        arm_motor.move_velocity(200);
        pid_enabled = false;
      }else{
        arm_motor.move_velocity(0);
        pid_enabled = true;
        target_pos = arm_sensor.get_angle() / 100.0;
      }
    }
  }

  void arm_pid(){
    if(pid_enabled){
      double current_pos = arm_sensor.get_angle() / 100.0;
      double error = target_pos - current_pos;

      bool windup = std::abs(error) > arm_controller.largeError;

      error_timeout = 0;
      int p = error;
      int i = windup ? accumulated_error : 0;
      int d = error - last_error;

      int vel = arm_controller.kP * p + arm_controller.kI * i + arm_controller.kD * d;

      arm_motor.move_velocity(vel);

      if(windup) accumulated_error += error;
      last_error = error;

      if(!windup && target_state == REST) pid_enabled = false; 
    }
  }
}