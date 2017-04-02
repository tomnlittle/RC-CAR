#include "controls.h"

Controls::Controls(double init_speed, double init_angle, 
                    double i_Motor, double d_Motor, double p_Motor,
                    double i_Angle, double d_Angle, double p_Angle)
{
    desired_speed = init_speed;
    desired_angle = init_angle;
    current_angle = 0;
    current_speed = 0;

    PCA9685 new_PWM;
    new_PWM.init(I2C_ADAPTER, PCA9685_ADDRESS);
    new_PWM.setPWMFreq(PCA9685_FREQUENCY);
    pwm = new_PWM;

    motor_pid.init(0, p_Motor, i_Motor, d_Motor);
    angle_pid.init(0, p_Angle, i_Angle, d_Angle);

    motor_pid.updatePID(desired_speed, current_speed);
    angle_pid.updatePID(desired_angle, current_angle);

    pwmCalibration();

    threadActive = false;
    //updateControlThread = std::thread(&Controls::controlThread, this);
}

Controls::~Controls()
{
    //stops updating the PID values
    threadActive = false;
    if(updateControlThread.joinable()){
        updateControlThread.join();
    }
    //Stops the motor after a safe exit
    pwm.setPWM(MOTOR_PORT, 0, NEUTRAL_DUTY_CYCLE_MOTOR);
    pwm.reset();
}

double Controls::getCurrentSpeed()
{
    return current_speed;
}

double Controls::getCurrentAngle()
{
    return current_angle;
}

void Controls::setDesiredSpeed(double speed)
{
    if (speed > 100.00 || speed < 0.00)
        return;
    desired_speed = speed;
}
void Controls::setDesiredAngle(double angle)
{
    if (angle > MAX_ANGLE)
    {
        desired_angle = MAX_ANGLE;
    }
    else if (angle < MIN_ANGLE)
    {
        desired_angle = MIN_ANGLE;
    } else {
        desired_angle = angle;
    }
}

void Controls::pwmCalibration(){
    //Motor Calibration
    pwm.setPWM(MOTOR_PORT, 0, NEUTRAL_DUTY_CYCLE_MOTOR);
    std::cout << "Calibrating..." << std::endl;
    sleep(5);
    std::cout << "done" << std::endl;
    pwm.setPWM(MOTOR_PORT, 0, MIN_DUTY_CYCLE_MOTOR);
}

void Controls::controlThread()
{
    threadActive = true;
    while(threadActive){
        updateSpeed();
        updateAngle();
        sleep(2);
    }
}

void Controls::updateSpeed()
{
    motor_pid.updatePID(desired_speed, current_speed);
    double pid_value = motor_pid.getPID();
    double percent = (desired_speed + pid_value) / 100.00;
    double dutyCycle = NEUTRAL_DUTY_CYCLE_MOTOR + (percent * (MAX_DUTY_CYCLE_MOTOR - NEUTRAL_DUTY_CYCLE_MOTOR));
    pwm.setPWM(MOTOR_PORT, 0, (int)dutyCycle);
    current_speed = desired_speed + pid_value;
    std::cout << dutyCycle << std::endl;
}

void Controls::updateAngle()
{
    angle_pid.updatePID(desired_angle, current_angle);
    double pid_value = angle_pid.getPID();
    double new_value = pid_value + desired_angle;
    double degree_range = MAX_ANGLE - MIN_ANGLE;
    double percent = (new_value - degree_range/2.00) / degree_range;
    double dutyCycle = MIN_DUTY_CYCLE_SERVO + (percent * (MAX_DUTY_CYCLE_SERVO - MIN_DUTY_CYCLE_SERVO));
    pwm.setPWM(SERVO_PORT, 0, (int)dutyCycle);
    current_angle = pid_value + desired_angle; 
}
