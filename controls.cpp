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

    threadActive = false;
    updateControlThread = std::thread(&Controls::controlThread, this);
    
}

Controls::~Controls()
{
    //stops updating the PID values
    threadActive = false;
    if(updateControlThread.joinable()){
        updateControlThread.join();
    }
    //Stops the motor after a safe exit
    pwm.setPWM(MOTOR_PORT, 0, MIN_DUTY_CYCLE_MOTOR);
    pwm.reset();
}

double Controls::getCurrentSpeed()
{
    return current_speed;
}

void Controls::setDesiredSpeed(double speed)
{
    desired_speed = speed;
}
void Controls::setDesiredAngle(double angle)
{
    desired_angle = angle;
}

void Controls::controlThread()
{
    threadActive = true;
    while(threadActive){
        updateSpeed();
        updateAngle();
    }
}

void Controls::updateSpeed()
{
    if (desired_speed > 100.00 || desired_speed < 0.00)
        return;
    motor_pid.updatePID(desired_speed, current_speed);
    double percent = motor_pid.getPID() / 100.00;
    double dutyCycle = MIN_DUTY_CYCLE_MOTOR + (percent * (MAX_DUTY_CYCLE_MOTOR - MIN_DUTY_CYCLE_MOTOR));
    pwm.setPWM(MOTOR_PORT, 0, (int)dutyCycle);
    current_speed = dutyCycle;
}

void Controls::updateAngle()
{
    if (desired_angle > MAX_ANGLE)
    {
        desired_angle = MAX_ANGLE;
    }
    else if (desired_angle < MIN_ANGLE)
    {
        desired_angle = MIN_ANGLE;
    }
    angle_pid.updatePID(desired_angle, current_angle);
    double percent = angle_pid.getPID() / (MAX_ANGLE - MIN_ANGLE);
    double dutyCycle = MIN_DUTY_CYCLE_SERVO + (percent * (MAX_DUTY_CYCLE_SERVO - MIN_DUTY_CYCLE_SERVO));
    pwm.setPWM(SERVO_PORT, 0, (int)dutyCycle);
    current_angle = dutyCycle;
}
