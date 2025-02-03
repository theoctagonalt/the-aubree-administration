#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

void skills_route(){
  Intake::set_target_colour(RED);
  chassis.setPose(0, 0, 0);
  Arm::set_state(SCORING);
  pros::delay(500);
  chassis.moveToPoint(0, -5, 1000);
  Arm::set_state(REST);

  //mogo
  chassis.turnToHeading(-90, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(24, -12, 1000, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  pros::delay(500);
  
  //first ring
  chassis.turnToHeading(180, 1000);
  Intake::toggle();
  chassis.waitUntilDone();
  chassis.moveToPoint(24, -45, 1000, {.maxSpeed=50});
  chassis.waitUntilDone();
  chassis.moveToPoint(24, -36, 1000, {.forwards=false});

  //second
  chassis.moveToPoint(50, -36, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(55, -36, 500, {.maxSpeed=100});

  //third, fourth
  chassis.turnToHeading(0, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(48, 3, 2000, {.maxSpeed=50});
  chassis.waitUntilDone();

  //fifth
  chassis.moveToPose(36, -12, 90, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(60, -12, 1000, {.maxSpeed=50});

  //sixth
  chassis.waitUntilDone();
  chassis.moveToPoint(60, -60, 2000, {.maxSpeed=100});
  chassis.waitUntilDone();
  chassis.moveToPoint(57, -70, 1000, {.maxSpeed=50});
  chassis.waitUntilDone();

  //drop mogo
  chassis.moveToPoint(65, 3, 2000, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  Intake::set_hooks(REV);
  Intake::set_preroller(REV);
  pros::delay(500);

  //OTHER HALF

  //pickup mogo
  chassis.moveToPoint(6, -5, 1000);
  chassis.waitUntilDone();
  Intake::set_hooks(OFF);
  Intake::set_preroller(OFF);
  chassis.turnToHeading(90, 1000, {.maxSpeed=100});
  chassis.waitUntilDone();

  chassis.moveToPoint(-24, -12, 1000, {.forwards=false, .maxSpeed=100});
  chassis.waitUntilDone();
  pros::delay(500);
  Mogo::toggle();

  //first ring
  chassis.turnToHeading(180, 1000);
  Intake::toggle();
  chassis.waitUntilDone();
  chassis.moveToPoint(-20, -45, 1000, {.maxSpeed=50});
  chassis.waitUntilDone();
  chassis.moveToPoint(-22, -36, 1000, {.forwards=false});

  //second
  chassis.moveToPoint(-45, -36, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-50, -36, 500, {.maxSpeed=100});
  chassis.waitUntilDone();

  //third, fourth
  chassis.turnToHeading(0, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-45, 3, 2000, {.maxSpeed=50});
  chassis.waitUntilDone();

  //fifth
  chassis.moveToPose(-36, -12, -90, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(-55, -12, 1000, {.maxSpeed=50});

  //sixth
  chassis.waitUntilDone();
  chassis.moveToPoint(-55, -60, 2000, {.maxSpeed=100});
  chassis.waitUntilDone();
  chassis.moveToPoint(-55, -70, 1000, {.maxSpeed=50});
  chassis.waitUntilDone();

  //drop mogo
  chassis.moveToPoint(-65, 3, 2000, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  Intake::set_hooks(REV);
  Intake::set_preroller(REV);
  pros::delay(500);

}