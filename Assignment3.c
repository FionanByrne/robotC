#pragma config(Sensor, S1,     Touch,          sensorEV3_Touch)
#pragma config(Sensor, S3,     Light,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          Claw,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          Lift,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          Spin,          tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard!!*//

void resetMotors() {
	motor[Lift]=0;
	motor[Spin]=0;
	motor[Claw]=0;
}

//Calibrate the arm so it's in the correct starting position
void Calibrate() {
	wait1Msec(100);
	while(SensorValue(Light) != 6) {
		motor[Lift] = -10;
	}
	resetMotors();

	wait1Msec(100);
	while(SensorValue(Touch) == 0) {
		motor[Spin] = 20;
	}
	resetMotors();
}

//Turn X degrees
void turnXdegrees(int Angle) {
	//Reset encoders
  nMotorEncoder[Spin] = 0;

  int dist = Angle*3.35;

  wait1Msec(1000);

  //Perform a point turn to the left. We will use lower power values for more accuracy.
  motor[Spin] = -20;

  //Since the wheels may go at slightly different speeds due to manufacturing tolerances, etc.,
  //we need to test both encoders and control both motors separately. This may result in one motor
  //going for longer than another but it will ultimately result in a much more accurate turn.
  while(nMotorEncoder[Spin] > -dist) {
    if(nMotorEncoder[motorC] < -dist) {motor[motorC] = 0;}
	}
	resetMotors();
}

//Lifting the object
void PickUp() {
	motor[Lift] = 10;
	wait1Msec(1900);
	resetMotors();

	motor[Claw] = 10;
	wait1Msec(700);
	resetMotors();

	while(SensorValue(Light) != 6) {
		motor[Lift] = -10;
	}
	resetMotors();
}

void Drop() {
	motor[Lift] = 10;
	wait1Msec(1900);
	resetMotors();

	motor[Claw] = -10;
	wait1Msec(700);
	resetMotors();

	while(SensorValue(Light) != 6) {
		motor[Lift] = -10;
	}
		resetMotors();
}

void CalculateAngle() {
	//TODO
	int OriginToA[2][2] = {{0,6}, {3,0}};
	int AtoB[2][2] = {{3,0}, {-8,0}};
}

task main() {
	Calibrate();

	turnXdegrees(90);

	//Create a 2x2 multidim array
	//Calculating the angle from start to A
	//Calculating the angle from A to B

	PickUp();

	Drop();
}
