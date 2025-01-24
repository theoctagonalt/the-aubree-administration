#include "main.h"
#include "lemlib/api.hpp"

#ifndef DEVICES_H_
#define DEVICES_H_

extern pros::Controller master;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::Motor arm_motor;
extern pros::Motor hooks_motor;
extern pros::Motor preroller_motor;

extern pros::adi::DigitalOut mogo;
extern pros::adi::DigitalOut doinker;

extern pros::adi::DigitalIn intake_switch;
extern pros::Rotation arm_sensor;
extern pros::Optical intake_colour;

extern lemlib::ControllerSettings arm_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;

#endif