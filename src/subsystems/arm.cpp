#include "./subsystems/arm.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "initialize.h"

namespace Arm{
  int target_state = REST;
  int target_pos;

  int arm_state_values[] = {REST_DEG, LOADING_DEG, READY_DEG, SCORING_DEG, HANGING_DEG};

  bool pid_enabled = false;
  int error_timeout = 0;
  double accumulated_error = 0;
  double last_error = 0;

  void set_state(int state){
    target_state = state;
    pid_enabled = true;
    target_pos = arm_state_values[target_state];
    pros::lcd::clear_line(1);
    pros::lcd::print(1, "target: %i, pos: %i", target_state, target_pos);
  }
  int get_state(){
    return target_state;
  }
  void set_pid(int state){
    pid_enabled = state;
  }

  void arm_pid(){
    if(pid_enabled){
      double current_pos = arm_sensor.get_angle() / 100.0;
      double error = target_pos - current_pos;

      bool windup = std::abs(error) > arm_controller.largeError;

      error_timeout = 0;
      double p = error;
      double i = windup ? accumulated_error : 0;
      double d = error - last_error;

      double vel = arm_controller.kP * p + arm_controller.kI * i + arm_controller.kD * d;

      arm_motor.move_velocity(vel);

      pros::lcd::clear_line(0);
      pros::lcd::print(0, "%f, %f", current_pos, error);

      if(windup) accumulated_error += error;
      last_error = error;

      if(target_state == LOADING &&fabs(error) < 2){
        pid_enabled=false;
        arm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        arm_motor.brake();
      }

      if(target_state == REST && fabs(error) < 2){
        pid_enabled=false;
        arm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_motor.brake();
      }

      if(target_state == HANGING && current_pos > 300){
        pid_enabled=false;
        arm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_motor.brake();
      }
    }
  }
}