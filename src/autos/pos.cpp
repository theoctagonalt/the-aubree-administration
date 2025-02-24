#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

void pos_route(){
  int colour = get_colour();
  int n = colour == RED ? 1 : -1;
  int match = get_match();

  chassis.setPose(0, 0, n*-90);

  chassis.moveToPoint(n*43, 0, 1000, {.forwards=false});
  chassis.waitUntilDone();

  chassis.turnToHeading(n*-135, 500);
  chassis.waitUntilDone();

  int mogo_x = colour == RED ? 51 : -49;

  chassis.moveToPoint(mogo_x, 9, 1000, {.forwards=false});
  chassis.waitUntilDone();

  Mogo::toggle();
  pros::delay(250);

  bool won_mogo = mogo_distance.get() < 12;

  if(won_mogo) {
    Intake::toggle();
  }else{
    Intake::set_preroller(FWD);
  }

  chassis.moveToPoint(n*25, 15, 1000);
  chassis.waitUntilDone();
  pros::delay(100);

  if(won_mogo){
    Intake::toggle();
  }else{
    Intake::set_preroller(OFF);
  }
  Mogo::toggle();

  chassis.moveToPoint(n*33, 37, 1000, {.forwards=false});
  chassis.waitUntilDone();

  Mogo::toggle();
  pros::delay(500);
  Intake::toggle();

}