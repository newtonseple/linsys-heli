/*
 * joystick.h
 *
 * Created: 09.09.2016 18:56:22
 *  Author: berntjd
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define JOYSTICK_X 0
#define JOYSTICK_Y 1

uint8_t joystick_get_axis(const uint8_t axis);
void joystick_test();

#endif /* JOYSTICK_H_ */