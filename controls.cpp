#include "controls.h"

Controls::Controls()
{
    speed = 0;

    PCA9685 new_PWM;
    new_PWM.init(I2C_ADAPTER, PCA9685_ADDRESS);
    new_PWM.setPWMFreq(PCA9685_FREQUENCY);
    pwm = new_PWM;
    printf("INITIALISED\n");
}

Controls::~Controls()
{
    pwm.reset();
}

int Controls::getSpeed()
{
    return speed;
}

void Controls::updateSpeed(double throttle)
{
    if (throttle > 100.00 || throttle < 0.00)
        return;
    double percent = throttle / 100.00;
    double dutyCycle = MIN_DUTY_CYCLE_MOTOR + (percent * (MAX_DUTY_CYCLE_MOTOR - MIN_DUTY_CYCLE_MOTOR));
    pwm.setPWM(MOTOR_PORT, 0, (int)dutyCycle);
    speed = dutyCycle;
}

void Controls::turnWheels(double degree)
{
    if (degree > MAX_ANGLE)
    {
        degree = MAX_ANGLE;
    }
    else if (degree < MIN_ANGLE)
    {
        degree = MIN_ANGLE;
    }
    double percent = degree / (MAX_ANGLE - MIN_ANGLE);
    double dutyCycle = MIN_DUTY_CYCLE_SERVO + (percent * (MAX_DUTY_CYCLE_SERVO - MIN_DUTY_CYCLE_SERVO));
    pwm.setPWM(SERVO_PORT, 0, (int)dutyCycle);
}
