//ALL DISTANCE MEASUREMENTS SHOULD BE MADE IN INCHES
//You should look though this code and set the values that are blank to the correct values and fill in functions such as drive and getGyro()
#define MAX_SPEED 127.0
#define DRIVE_BASE_WIDTH 10.0 // in Inches
#define TIME_STEP 0.002 //50Hz

void drive(float Left, float Right) {
  // Define driveFunction
  // driveFunction(*args);
}

float getGyro(){
  return 0; //myGyro.value(deg); // Change GyroGetter Function to get gyro degree 
}

bool gyroReached(float start, float Target){
  if(start <= Target){
    return (getGyro() <= Target);
  }
  else{
    return (getGyro() >= Target);
  }
}

float vPID(float error, float integral, float derititive, float kP = 1.0, float kI = 0.0, float kD = 0.0, float timeStep = TIME_STEP){
  return kP*error+kI*integral-kD*derititive;
}

void curveTurn(float radius, float targetHeading, bool rightSideLead, float kP = 1.0, float kI = 0.0, float kD = 0.0, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  float kA = radius/(radius + driveBaseWidth);
  
  float pError = 0;
  float error; 
  float integral = 0;
  float derivitive;
  float vOuter, vInner, vRight, vLeft;

  float startHeading = getGyro();

  while(gyroReached(startHeading, targetHeading)){
    
    error = targetHeading - getGyro();
    integral += error*timeStep;
    derivitive = (error-pError)/timeStep;

    vOuter = vPID(error, integral, derivitive, kP, kI, kD, timeStep);
    vInner = kA*vOuter;

    if(rightSideLead){
      vRight = vOuter;
      vLeft = vInner;
    }
    else{
      vRight = vInner;
      vLeft = vOuter;
    }

    drive(vLeft, vRight);
    //wait(timeStep*1000);
    pError = error;
  }
}

void curveTurnRight(float radius, float targetHeading, float vOuter = MAX_SPEED, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  curveTurn(radius, targetHeading, true, vOuter, driveBaseWidth, timeStep);
}

void curveTurnLeft(float radius, float targetHeading, float vOuter = MAX_SPEED, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  curveTurn(radius, targetHeading, false, vOuter, driveBaseWidth, timeStep);
}
