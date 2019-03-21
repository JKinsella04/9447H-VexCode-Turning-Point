#include "robot-config.h"
vex::competition    Competition;
using namespace vex;
    void fourWheelDrive(double count, double speed);
    void leftturn(double count, double speed);
    void rightTurn(double count, double speed);
    void shootBall();
    void CapAuton();
    void BallAuton();
    void spin();   
    void claw();
    void Aclaw();
    void stop();
    void intake();
    void stopSpin();

void pre_auton( void ) {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    ClawMotor.resetRotation();
    BallInput.resetRotation();
    BallOutput.resetRotation();
    BallOutput.setStopping(vex::brakeType::coast);
    BallOutputtwo.resetRotation();
    BallOutputtwo.setStopping(vex::brakeType::coast);
    BallInput.setStopping(brakeType::coast);
}
void autonomous( void ) {
 
    //CapAuton();
    BallAuton();
    
}

void usercontrol( void ) {
    
  while(true){
        Controller.Screen.clearLine(3);
        Controller.Screen.setCursor(3,0);
        Controller.Screen.print("RPM:%f",BallOutput.velocity(vex::velocityUnits::rpm));
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(1,40,"RPM:%f",BallOutput.velocity(vex::velocityUnits::rpm));
        Brain.Screen.printAt(1,80,"Temp:%f",BallOutput.temperature(vex::percentUnits::pct));
        Brain.Screen.render();
       // vex::task::sleep(20);
        DriveLeft.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
        DriveLefttwo.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
        DriveRight.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
        DriveRighttwo.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
        spin();
        claw();
        stop();
        intake();
        stopSpin();
        }
}

int main() { 
    
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    //Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}
//FUNCTIONS
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
        ClawMotor.startRotateTo(0,rotationUnits::deg,80,velocityUnits::pct);
    }
    if(Controller.ButtonR2.pressing() == 1) {
        ClawMotor.startRotateTo(-180,rotationUnits::deg,80,velocityUnits::pct);
    }
}

void spin() {
    if(Controller.ButtonUp.pressing() == 1) {
        
        BallInput.spin(directionType::fwd,175,velocityUnits::rpm);
        BallOutput.spin(directionType::fwd,600,velocityUnits::rpm);
        BallOutputtwo.spin(directionType::fwd,600,velocityUnits::rpm);
    }
}

void stopSpin() {
    if(Controller.ButtonRight.pressing() == 1) {
        BallInput.stop();
        BallOutput.stop();
        BallOutputtwo.stop();
    }
}

void intake() {
    if(Controller.ButtonL1.pressing() == 1) {
       BallInput.spin(directionType::fwd,200,velocityUnits::rpm);
    }
    
    else if(Controller.ButtonL2.pressing() == 1) {
        BallInput.spin(directionType::rev,200,velocityUnits::rpm);
    }

    else {
    BallInput.stop();
    }
}

void setup () {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    ClawMotor.resetRotation();
    BallInput.resetRotation();
    BallOutput.resetRotation();
    BallOutput.setStopping(vex::brakeType::coast);
    BallOutputtwo.resetRotation();
    BallOutputtwo.setStopping(vex::brakeType::coast);
    BallInput.setStopping(brakeType::coast);
    ClawMotor.setStopping(brakeType::hold);
    DriveLeft.setReversed(true);
    
}

void CapAuton() {
    //forward(100, 75);
    DriveLeft.stop();
    DriveRight.stop();
    task::sleep(1000);
    //forward(750, 50);
    leftturn(200, 30);
    shootBall(); 
}
    
void BallAuton() {
    fourWheelDrive(1300, 75);
    //task::sleep(100);
    fourWheelDrive(-600, 75);
    BallOutput.setVelocity(600,vex::velocityUnits::rpm);
    BallOutputtwo.setVelocity(600,vex::velocityUnits::rpm);
    BallOutput.spin(directionType::fwd);
    BallOutputtwo.spin(directionType::fwd);
   shootBall();
    task::sleep(250);
    BallOutput.stop();
    BallOutputtwo.stop();
    BallInput.stop();
// TEST WHERE THE ROBOT GOES AND TRIES TO PARK ON ALLIANCE PLATFORM
    fourWheelDrive(-850, 75);
    leftturn(90, 50);
    fourWheelDrive(200, 75);
    Aclaw();
    fourWheelDrive(-1050, 75);
    ClawMotor.rotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
    rightTurn(90, 50);
    fourWheelDrive(-100, 75);
    Aclaw();
    fourWheelDrive(-700, 100);
}

void fourWheelDrive(double count, double speed) {
    DriveLeft.resetRotation();
    DriveRight.resetRotation();
    DriveLefttwo.resetRotation();
    DriveRighttwo.resetRotation();
    DriveLeft.startRotateTo(-count,vex::rotationUnits::deg,-speed,vex::velocityUnits::pct);
    DriveRight.startRotateTo(-count,rotationUnits::deg,speed,velocityUnits::pct);
    DriveLeft.startRotateTo(-count,vex::rotationUnits::deg,-speed,vex::velocityUnits::pct);
    DriveRight.rotateTo(-count,rotationUnits::deg,speed,velocityUnits::pct,true);
}

void leftturn(double count, double speed) {
   DriveLeft.resetRotation();
    if(DriveLeft.rotation(rotationUnits::deg) < count) {
    DriveLeft.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    DriveRight.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
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
}

void shootBall() {
  //  BallOutput.setVelocity(200,vex::velocityUnits::rpm);
  //  BallOutput.spin(directionType::fwd);
    while(BallOutput.velocity(vex::velocityUnits::rpm) < 575) {
        double velo = BallOutput.velocity(vex::velocityUnits::rpm);
        Controller.Screen.print(velo);
        Brain.Screen.print(velo);
    }
    BallInput.spin(directionType::fwd,100,velocityUnits::pct);
}






