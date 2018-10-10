#include <stdio.h>
#include <stdlib.h>

#include "WifibotClient.h"
#include "FonctionsBasiques.h"

#define IP_ADRESSE "192.168.1.77"
#define PORT	15020

int SharpLUT[]={150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,103,102,101,100,99,
          96,95,90,88,87,86,85,84,83,82,81,80,79,77,75,74,73,72,71,70,69,68,67,66,65,65,64,64,63,62,61,61,60,60,59,59,58,58,57,57,56,56,56,55,55,55,54,54,54,53,
          53,53,52,52,51,51,50,50,49,49,49,48,48,47,47,46,46,46,45,45,44,44,43,43,42,42,41,41,41,40,40,40,39,39,39,39,39,38,38,
                  38,38,37,37,37,37,36,36,36,36,35,35,35,35,34,34,34,34,34,34,33,33,33,33,32,32,32,32,32,31,31,31,31,30,30,30,30,30,30,30,
          30,29,29,29,29,29,29,29,28,28,28,28,28,28,27,27,27,27,27,27,27,26,26,26,26,25,25,25,25,25,25,24,24,24,24,24,23,23,23,
          23,23,23,22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,17,17,17,16,16,15,15};

void main(void)
{

	WifibotClient robot;

	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
		
	bool rep = robot.ConnectToRobot(IP_ADRESSE, PORT);
	if( rep )
	{
		printf("Connection failed...\n");
		getchar();
		return;
	}
	else
	{
		printf("Connection established...\n");
	}


	/*..............*/
	/* Main program */
	/*..............*/
	
	SensorData sensors_data;
	while(1)
	{
		unsigned char flags = 128+32+64+16+1;
		
		//printf("Batterie : %d\n", sensors_data.BatVoltage);
		/*for (int i = 0; i < 100000; i++) {
			for (int j = 0; j < 5000; j++);
		}
			robot.GetSensorData(&sensors_data);
			avancer(&robot, 50, 50);
			//printf("Batterie : %d\n", sensors_data.BatVoltage);
			printf("Capteur IR gauche : %d\n", sensors_data.IRLeft);
			printf("Capteur IR droite : %d\n", sensors_data.IRRight);
			printf("Capteur IR2 gauche : %d\n", sensors_data.IRLeft2);
			printf("Capteur IR2 droite : %d\n", sensors_data.IRRight2);
			printf("Odometrie gauche : %ld\n", sensors_data.OdometryLeft);
			printf("Odometrie droite : %ld\n", sensors_data.OdometryRight);
			printf("Vitesse droite : %d\n", sensors_data.SpeedFrontRight);
			printf("-------------------------------------------------------\n");
			for (int i = 0; i < 100000; i++) {
				for (int j = 0; j < 5000; j++);
			}
			avancer(&robot, 100, 100);
			printf("Vitesse droite : %d\n", sensors_data.SpeedFrontRight);
			printf("-------------------------------------------------------\n");
			*/

		robot.GetSensorData(&sensors_data);
		avancer(&robot, 50, 50);
		printf("Batterie : %d\n", sensors_data.BatVoltage); 
		//robot.SendCommand(84,84,flags);
		printf("Capteur IR gauche : %d\n", sensors_data.IRLeft);
		printf("Capteur IR droit : %d\n", sensors_data.IRRight);
		printf("Vitesse droite : %d\n", sensors_data.SpeedFrontRight);
		if (obstacleGauche(&sensors_data) && obstableDroite(&sensors_data))
			//robot.SendCommand(0, 0, flags);
			avancer(&robot, 0, 0);
		else if (obstableDroite(&sensors_data))
			//robot.SendCommand(84, 0, flags);
			avancer(&robot, 50, 0);
		else if (obstacleGauche(&sensors_data))
			//robot.SendCommand(0, 84, flags);
			avancer(&robot, 0, 50);


		Sleep(100);
	}	
}

