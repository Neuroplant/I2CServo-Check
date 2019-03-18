

LDFLAGS = -lwiringPi -lm -lpthread -lwiringPiPca9685

Check: ServoCheck.c

	gcc ServoCheck.c -o CheckServo $(LDFLAGS)
