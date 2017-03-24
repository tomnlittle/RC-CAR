#include <thread>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <exception>
#include "libs/PCA9685.h"
#include "libs/PID.h"

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
                Controls(double init_speed = 0, double init_angle = 90, 
                                double i_Motor = 0, double d_Motor = 0, double p_Motor = 0,
                                double i_Angle = 0, double d_Angle = 0, double p_Angle = 0);
                /*
                  Destructor module, called automagically when the program closes nicely 
                  If CTRL-C is called it is uncertain whether this will be called
                */
                ~Controls();
                /*
                  Returns the current speed of the car 
                */
                double getCurrentSpeed();

                /*
                  Updates the desired speed of the car 
                  throttle is given as a percentage of the total power of the car 
                  100% being full power and 0% being stationary 

                  The function will instantly return if the given throttle value is not within 
                  0 and 100 - FOR SAFETY REASONS 
                */
                void setDesiredSpeed(double speed);

                /*
                  Argument degrees is a double for sub integer accuracy 
                  when wheel turn duty cycle is calculated this will 
                  yield a more accurate representation of the desired angle 

                  THE INPUT DEGREE WILL LIKELY NEVER BE THE OUTPUT BUT A GOOD ESTIMATE

                  If an angle greater, or less than the minimum is inputted the greatest or least
                  respectively angle will be used 
                */
                void setDesiredAngle(double angle);

        private:
                
                /*
                  Constantly updates the values for the current speed and the current angle 
                  of the wheels for the RC allowing for smoother control
                */
                void controlThread();
                std::thread updateControlThread; 
                bool threadActive;
                /*
                  Manages the dutycycle of the car and the associated PID algorithm 
                */
                void updateSpeed();
                /*
                  Manages the dutycycle of the servo and the associated PID algorithm 
                */
                void updateAngle();

                //The PWM i2c instance
                PCA9685 pwm;

                /*
                  Values for storing the current and desired speed of the car
                  The current values will always approach the desired values
                */
                double desired_speed;  
                double current_speed;

                double desired_angle;
                double current_angle;  

                PID motor_pid;
                PID angle_pid;
};