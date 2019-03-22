#include "robot-config.h"
//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
using namespace vex;
    void forward( double count, double speed);
    void fourWheelDrive(double count, double speed);
    void leftturn(double count, double speed);
    void rightTurn(double count, double speed);
    void shootBall();
    void CapAuton();
    void BallAuton();
    void spin();
    void stopSpin();    
    void claw();
    void Aclaw();
    void stop();
    void intake();
    void indexer();
    //int flywheelrpm();

void pre_auton( void ) {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    ClawMotor.resetRotation();
    Intake.resetRotation();
    BallOutput.resetRotation();
    BallOutput.setStopping(vex::brakeType::coast);
    Intake.setStopping(brakeType::coast);
    Indexer.setStopping(brakeType::hold);
}
void autonomous( void ) {
 
    //CapAuton();
    BallAuton();
    
}

void usercontrol( void ) {
    
  while(true){
        //flywheelrpm();
        Controller.Screen.clearLine(3);
        Controller.Screen.setCursor(3,0);
        Controller.Screen.print("RPM:%f",BallOutput.velocity(vex::velocityUnits::rpm));
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(1,40,"RPM:%f",BallOutput.velocity(vex::velocityUnits::rpm));
        Brain.Screen.printAt(1,80,"Temp:%f",BallOutput.temperature(vex::percentUnits::pct));
        Brain.Screen.render();
        vex::task::sleep(20);
        /*
        DriveLeft.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
        DriveRight.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
        DriveLefttwo.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
        DriveRighttwo.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
        */

        float max = 127.0;
        float left_percent = Controller.Axis3.value()/max;
        float right_percent = Controller.Axis2.value()/max;
       
        float left_new_percent = left_percent * left_percent * left_percent;
        float right_new_percent = right_percent * right_percent * right_percent;
       
        float motor_max = 70;
        int left_power = left_new_percent * motor_max;
        int right_power = right_new_percent * motor_max;
       
        DriveLeft.spin(fwd,left_power,vex::velocityUnits::pct);
        DriveLefttwo.spin(fwd,left_power,vex::velocityUnits::pct);
        DriveRight.spin(fwd,right_power,vex::velocityUnits::pct);
        DriveRighttwo.spin(fwd,right_power,vex::velocityUnits::pct);
        spin();
        stopSpin();
        claw();
        stop();
        intake();
        indexer();
        Pwm_outh.state(100,vex::percentUnits::pct);
        }
}



int main() { 
    
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
  //  Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}

//int flywheelrpm() {
//        double rpm = BallOutput.velocity(vex::velocityUnits::rpm);
//        Controller.Screen.print(rpm);
//}

void stop() {
    if(Controller.ButtonA.pressing() == 1) {
        DriveRight.stop(brakeType::hold);
        DriveLeft.stop(brakeType::hold);
        DriveRighttwo.stop(brakeType::hold);
        DriveLefttwo.stop(brakeType::hold);
    }
    
    if(Controller.ButtonB.pressing() == 1) {
        DriveRight.stop(brakeType::coast);
        DriveLeft.stop(brakeType::coast);
        DriveRighttwo.stop(brakeType::coast);
        DriveLefttwo.stop(brakeType::coast);
    }
}

void claw() {
    if(Controller.ButtonR1.pressing() == 1) {
        ClawMotor.startRotateTo(0,rotationUnits::deg,70,velocityUnits::pct);
    }
    if(Controller.ButtonR2.pressing() == 1) {
        ClawMotor.startRotateTo(-180,rotationUnits::deg,100,velocityUnits::pct);
    }
}


void spin() {
    if(Controller.ButtonUp.pressing() == 1) {
        
        Intake.spin(directionType::fwd,175,velocityUnits::rpm);
        BallOutput.spin(directionType::fwd,600,velocityUnits::rpm);
        BallOutputtwo.spin(directionType::fwd,600,velocityUnits::rpm);
        //Controller.Screen.print(flywheelrpm);
    }
}

void stopSpin() {
    if(Controller.ButtonRight.pressing() == 1) {
        Intake.stop();
        BallOutput.stop();
        BallOutputtwo.stop();
    }
}
  
void intake() {
    if(Controller.ButtonL1.pressing() == 1) {
       Intake.spin(directionType::fwd,200,velocityUnits::rpm);
    }
    
    else if(Controller.ButtonL2.pressing() == 1) {
        Intake.spin(directionType::rev,200,velocityUnits::rpm);
    }

    else {
    Intake.stop();
    }
}
void indexer() {
 if(Controller.ButtonLeft.pressing() == 1) {
      Indexer.spin(directionType::fwd, 200,velocityUnits::rpm);
    }

    else {
    Indexer.stop();
    }
}

void setup () {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    ClawMotor.resetRotation();
    Intake.resetRotation();
    BallOutput.resetRotation();
    DriveRighttwo.setStopping(vex::brakeType::coast);
    DriveRight.setStopping(brakeType::coast);
    DriveLeft.setStopping(vex::brakeType::coast);
    DriveLefttwo.setStopping(brakeType::coast);
    BallOutput.setStopping(vex::brakeType::coast);
    Intake.setStopping(brakeType::coast);
    ClawMotor.setStopping(brakeType::hold);
    DriveLeft.setReversed(true);
    
}

void CapAuton() {
    fourWheelDrive(1100, 75);
    Intake.spin(directionType::fwd,200,velocityUnits::rpm);
    fourWheelDrive(200, 75);
    task::sleep(500);
    Intake.stop();
    //ClawMotor.rotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
   // task::sleep(250);
    rightTurn(90, 80);
    Aclaw();
    fourWheelDrive(-400, 75);
    ClawMotor.rotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
    leftturn(90, 75);
    fourWheelDrive(-400, 75);
    leftturn(90, 75);
    fourWheelDrive(-500, 75);
    Aclaw();
    fourWheelDrive(-750, 75);
}
    


void forward( double count, double speed) {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    if(DriveLeft.rotation(vex::rotationUnits::deg) < count){
    DriveLeft.startRotateTo(count,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    DriveRight.rotateTo(count,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    }
    else{
        DriveLeft.stop();
        DriveRight.stop();
    }
}

void fourWheelDrive(double count, double speed) {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    DriveLefttwo.resetRotation();
    DriveRighttwo.resetRotation();
    DriveLeft.startRotateTo(-count,rotationUnits::deg,-speed,velocityUnits::pct);
    DriveLefttwo.startRotateTo(-count,rotationUnits::deg,-speed,velocityUnits::pct);
    DriveRight.startRotateTo(-count,rotationUnits::deg,speed,velocityUnits::pct);
    DriveRighttwo.rotateTo(-count,rotationUnits::deg,speed,velocityUnits::pct);
    
}

void leftturn(double count, double speed) {
   DriveLeft.resetRotation();
    if(DriveLeft.rotation(rotationUnits::deg) < count) {
    DriveLeft.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    DriveRight.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    DriveLefttwo.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    DriveRighttwo.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    task::sleep(1000);
    while(DriveLeft.rotation(rotationUnits::deg) < count) {
        if(DriveLeft.velocity(velocityUnits::dps) < 1) {
            break;
        }
    }
        DriveLeft.stop();
        DriveRight.stop();
        DriveLefttwo.stop();
        DriveRighttwo.stop();
    }
}

void rightTurn(double count, double speed) {
   DriveLeft.resetRotation();
    if(DriveLeft.rotation(rotationUnits::deg) < count) {
    DriveLeft.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    DriveRight.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    DriveLefttwo.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    DriveRighttwo.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    task::sleep(1000);
    while(DriveLeft.rotation(rotationUnits::deg) < count) {
        if(DriveLeft.velocity(velocityUnits::dps) < 1) {
            break;
        }
    }
        DriveLeft.stop();
        DriveRight.stop();
        DriveLefttwo.stop();
        DriveRighttwo.stop();
    }
}

void Aclaw() {
    ClawMotor.rotateFor(-180,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
   // task::sleep(1000);
    //fourWheelDrive(100, 75);
}

void shootBall() {
    BallOutput.setVelocity(600,vex::velocityUnits::rpm);
    BallOutputtwo.setVelocity(600,velocityUnits::rpm);
    BallOutput.spin(directionType::fwd);
    BallOutputtwo.spin(directionType::fwd);
    while(BallOutput.velocity(vex::velocityUnits::rpm) < 580) {
        double velo = BallOutput.velocity(vex::velocityUnits::rpm);
        Controller.Screen.print(velo);
        Brain.Screen.print(velo);
    }
    Intake.spin(directionType::fwd,200,velocityUnits::rpm);
    Indexer.spin(directionType::fwd,200,velocityUnits::rpm);
}
