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
vex::motor Indexer (vex::PORT10, vex::gearSetting::ratio18_1,true);
vex::motor BallOutput (vex::PORT15, vex::gearSetting::ratio6_1,true);
vex::motor BallOutputtwo (vex::PORT7, vex::gearSetting::ratio6_1,false);
vex::motor ClawMotor (vex::PORT20, vex::gearSetting::ratio36_1,true);
vex::motor dscore (vex::PORT5, vex::gearSetting::ratio18_1,false);
vex::motor Intake (vex::PORT17, vex::gearSetting::ratio18_1,false);
vex::controller Controller = vex::controller();
vex::pwm_out Pwm_outa = vex::pwm_out(Brain.ThreeWirePort.A);
vex::pwm_out Pwm_outb = vex::pwm_out(Brain.ThreeWirePort.B);
vex::pwm_out Pwm_outc = vex::pwm_out(Brain.ThreeWirePort.C);
vex::pwm_out Pwm_outd = vex::pwm_out(Brain.ThreeWirePort.D);
vex::pwm_out Pwm_oute = vex::pwm_out(Brain.ThreeWirePort.E);
vex::pwm_out Pwm_outf = vex::pwm_out(Brain.ThreeWirePort.F);
vex::pwm_out Pwm_outg = vex::pwm_out(Brain.ThreeWirePort.G);
vex::pwm_out Pwm_outh = vex::pwm_out(Brain.ThreeWirePort.H);