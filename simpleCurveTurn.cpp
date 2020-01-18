#define MAX_SPEED 127.0
#define DRIVE_BASE_WIDTH 10.0 // in Inches

void drive(float Left, float Right) {
  // Define driveFunction
  // driveFunction(*args);
}

void simpleCurveTurnLeft(float radius, float t, float v){
	float kA = radius/(radius + DRIVE_BASE_WIDTH);
	float vOuter= v; 
	float vInner=kA*v;
	drive(vInner, vOuter);
	wait(t, sec);
}

void simpleCurveTurnRight(float radius, float t, float v){
        float kA = radius/(radius + DRIVE_BASE_WIDTH);
        float vOuter= v; 
        float vInner=kA*v;
        drive(vOuter, vInner);
        wait(t, sec);
}      
