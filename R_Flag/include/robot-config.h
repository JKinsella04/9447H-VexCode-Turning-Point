#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
//
vex::brain Brain;
vex::motor DriveRight (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor DriveLeft (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor DriveRighttwo (vex::PORT1, vex::gearSetting::ratio18_1,true);
vex::motor DriveLefttwo (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor BallInput (vex::PORT10, vex::gearSetting::ratio18_1,true);
vex::motor BallOutput (vex::PORT15, vex::gearSetting::ratio6_1,true);
vex::motor BallOutputtwo (vex::PORT7, vex::gearSetting::ratio6_1,false);
vex::motor ClawMotor (vex::PORT20, vex::gearSetting::ratio36_1,true);
vex::motor dscore (vex::PORT5, vex::gearSetting::ratio18_1,false);
vex::controller Controller = vex::controller();