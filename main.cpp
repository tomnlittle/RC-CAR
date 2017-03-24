#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "controls.h"
#include "libs/camera.h"

int main(int argc, char **argv){

	double degree = 0;
	int speed = 0;

	Controls car;

	while(true){
		if(hold_value == 'w'){
			speed += 2.00;
		} else if(hold_value == 's'){
			speed -= 2.00;
		} else if (hold_value == 'x'){
			speed = 0;
		} else if (hold_value == 'a'){
			degree -= 5;
		} else if (hold_value == 'd'){
			degree += 5;
		}

		std::cout << "Degree " << degree << std::endl;
		std::cout << "Speed " << speed << std:endl;

		car.setDesiredAngle(degree);
		car.setDesiredSpeed(speed);

		if(hold_value == 'h'){
			booted = false;
			break;
		}
		cin >> hold_value;
	}
 
	Camera cam(0, 1);   
	printf("CV Version : %s \n", CV_VERSION); //prints the openCV version

	//The first few images are commonly throw away since the camera doesnt expose correctly
	//so give it a couple seconds to boot up and set the right white balance etc.
	cv::Mat3b frame = cam.getNewFrame(); //Grabs a processed frame from the sensor 

	cv::imwrite("img.jpg", frame);
	
	return EXIT_SUCCESS;
}


