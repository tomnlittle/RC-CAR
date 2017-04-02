#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "controls.h"
#include "libs/camera.h"

#define CAMERA_ID									0
#define NOISE_REDUCTION_LEVEL 						0

int main(int argc, char **argv){

	double degree = 90;
	int speed = 0;

	Controls car;

	Camera cam(CAMERA_ID, NOISE_REDUCTION_LEVEL);   
	printf("OPENCV Version : %s \n", CV_VERSION); //prints the openCV version
	
	while(true){
		char hold_value = ' ';
		std::cin >> hold_value;
		if(hold_value == 'w'){
			speed += 1.0;
		} else if(hold_value == 's'){
			speed -= 2.00;
		} else if (hold_value == 'x'){
			speed = 0;
		} else if (hold_value == 'a'){
			degree -= 5.00;
		} else if (hold_value == 'd'){
			degree += 5.00;
		} else if(hold_value == 'h'){
			break;
		}
		car.setDesiredAngle(degree);
		car.setDesiredSpeed(speed);

		//std::cout << "Degree : " << car.getCurrentAngle() << std::endl;
		std::cout << "Speed : " << car.getCurrentSpeed() << "%" << std::endl;
	}
 
	

	//The first few images are commonly throw away since the camera doesnt expose correctly
	//so give it a couple seconds to boot up and set the right white balance etc.
	//cv::Mat3b frame = cam.getNewFrame(); //Grabs a processed frame from the sensor 

	//cv::imwrite("img.jpg", frame);
	
	return EXIT_SUCCESS;
}


