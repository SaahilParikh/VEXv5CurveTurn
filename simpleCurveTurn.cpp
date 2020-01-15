#define MAX_SPEED 127.0
#define DRIVE_BASE_WIDTH 10.0 // in Inches
#define TIME_STEP 0.002 //50H

void drive(float Left, float Right) {
  // Define driveFunction
  // driveFunction(*args);
}

float simpleCurveTurnLeft(float radius, float targetHeading, float v=MAX_SPEED,float time=TIME_STEP){
	float kA = radius/(radius + DRIVE_BASE_WIDTH);
	float vOuter= v; 
	float vInner=kA*v;
	drive(vInner, vOuter);
	wait(timeStep, sec);
}

float simpleCurveTurnRight(float radius, float targetHeading, float v=MAX_SPEED,float time=TIME_STEP){
        float kA = radius/(radius + DRIVE_BASE_WIDTH);
        float vOuter= v; 
        float vInner=kA*v;
        drive(vOuter, vInner);
        wait(timeStep, sec);
}      
