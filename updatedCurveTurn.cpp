//ALL DISTANCE MEASUREMENTS SHOULD BE MADE IN INCHES
//You should look though this code and set the values that are blank to the correct values and fill in functions such as drive and getGyro()
#define MAX_PERCENT 80 //UNDER LOAD MOTORS DO NOT RUN AT TRUE SPEED. RESEMBLES A BOUND FUNCTION
#define DRIVE_BASE_WIDTH 10.0 // in Inches
#define TIME_STEP 0.02 //50Hz

#define curveTurnkP 1.0
#define curveTurnkI 0.0
#define curveTurnkD 0.0

#define CURVE_TURN_THRESH 2

float sgn(float num){
	return num > 0 ? 1 : (num < 0 ? -1 : 0);
}

void drive(float Left, float Right) {
  // Define driveFunction
  // driveFunction(*args);
}

float getGyro(){
  return 0; //myGyro.value(deg); // Change GyroGetter Function to get gyro degree 
}

bool gyroThresh(float Target, float thresh=THRESH){
	if(abs(Target-getGyro()) <= thresh){
		return true;
	}
	return false;
}

void curveTurn(float radius, float targetHeading, bool rightSideLead, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  float kA = radius/(radius + driveBaseWidth);

  float pError = 0;
  float error; 

  float integral = 0;
  float derivitive;
  float vOuter, vInner, vRight, vLeft;

  float startHeading = getGyro();

  int count = 0;

  while(count < CURVE_TURN_COUNT){
    
    error = targetHeading - getGyro();
    integral += error*timeStep;
    derivitive = (error-pError)/timeStep;

    vOuter = curveTurnkP*error+curveTurnkI*integral+curveTurnkD*derivitive;

    if (abs(vOuter) > MAX_PERCENT){
	vOuter = sgn(vOuter)*MAX_PERCENT;
    }

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
    pError = error;

    if(gyroThresh(targetHeading)){
    	count++;
	//50msec*2 = tenth a second
    }
    else{
	count = 0;
    }

    wait(timeStep, sec);
  }
}

void curveTurnRight(float radius, float targetHeading, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  curveTurn(radius, targetHeading, true, driveBaseWidth, timeStep);
}

void curveTurnLeft(float radius, float targetHeading, float driveBaseWidth = DRIVE_BASE_WIDTH, float timeStep = TIME_STEP){
  curveTurn(radius, targetHeading, false,  driveBaseWidth, timeStep);
}
