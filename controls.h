#include <exception>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>  
#include <thread>
#include "libs/PCA9685.h"

#define PCA9685_ADDRESS					                0x40
#define PCA9685_FREQUENCY   			              60
#define I2C_ADAPTER 			                      1

#define SERVO_PORT                              0
#define MOTOR_PORT                              8

//SERVO DEFINES
#define MIN_ANGLE                               45
#define MAX_ANGLE                               135

#define MIN_DUTY_CYCLE_SERVO                    310
#define MAX_DUTY_CYCLE_SERVO                    490

//MOTOR DEFINES 
#define MIN_DUTY_CYCLE_MOTOR                    400
#define MAX_DUTY_CYCLE_MOTOR                    900


class Controls {
        public:
                /*
                  This is called when the class is initialised
                */
                Controls();
                /*
                  Destructor module, called automagically when the program closes nicely 
                  If CTRL-C is called it is uncertain whether this will be called
                */
                ~Controls();
                /*
                  Returns the current speed of the car 
                */
                int getSpeed();

                /*
                  Changes the current speed of the car 
                  throttle is given as a percentage of the total power of the car 
                  100% being full power and 0% being stationary 

                  The function will instantly return if the given throttle value is not within 
                  0 and 100 - FOR SAFETY REASONS 
                */
                void updateSpeed(double throttle);

                /*
                  Argument degrees is a double for sub integer accuracy 
                  when wheel turn duty cycle is calculated this will 
                  yield a more accurate representation of the desired angle 

                  THE INPUT DEGREE WILL LIKELY NEVER BE THE OUTPUT BUT A GOOD ESTIMATE

                  If an angle greater, or less than the minimum is inputted the greatest or least
                  respectively angle will be used 
                */
                void turnWheels(double degree);
        private:
                PCA9685 pwm;
                double speed;    
};