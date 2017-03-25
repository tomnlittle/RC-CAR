// v rough structure of what main flow will look like

int main(int argc, char **argv){

    //Set up car and camera
	Controls car; //car doesn't move until input is here
	Camera cam(CAMERA_ID, NOISE_REDUCTION_LEVEL);   
	Path path;

    // Wait for system to be ready
    while(!car.ready()){};
	Takes into account

	while(car.ready()){
        // Grab the frame
		cam.getFrame(frame);

		prepareImage(frame) {
			/*
			 * Resize it
			 * Convert image to hsv
			 * Convert image to greyscale
			 */
		}

		// Prepare the path
		path.preparePath(frame) {
			/*
			 *	In here would do a lot of magic
			 * 	Includes future decisions
			 *	Path as top priority
			 *	Check for obstacles at end to make sure we not gonna die
			 */
		}

		degree = path.getDegree();
		speed = path.getSpeed();

		car.setDesiredAngle(degree);
		car.setDesiredSpeed(speed);

		std::cout << "Degree : " << car.getCurrentAngle() << std::endl;
		std::cout << "Speed : " << car.getCurrentSpeed() << "%" << std::endl;
	}
	return EXIT_SUCCESS;
}
