#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "controls.h"
#include "libs/camera.h"

int main(int argc, char **argv){

	double degree;
	int speed;
	sscanf(argv[1], "%lf", &degree);
	sscanf(argv[2], "%d", &speed);

	Controls car;
	car.setDesiredAngle(degree);
	car.setDesiredSpeed(speed);
 
	Camera cam(0, 1);   
	printf("CV Version : %s \n", CV_VERSION); //prints the openCV version

	//The first few images are commonly throw away since the camera doesnt expose correctly
	//so give it a couple seconds to boot up and set the right white balance etc.
	sleep(2);  
	cv::Mat3b frame = cam.getNewFrame(); //Grabs a processed frame from the sensor 

	cv::imwrite("img.jpg", frame);
	
	return EXIT_SUCCESS;
}


