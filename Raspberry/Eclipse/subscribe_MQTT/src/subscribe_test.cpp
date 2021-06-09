//============================================================================
// Name        : demo1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include <unistd.h>
#include "mqtt/async_client.h"

#define O_LED 17
#define O_LED2 23
using namespace std;

const string SERVER_ADDRESS { "tcp://192.168.8.140:1883" };
const string CLIENT_ID { "user1" };

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

	if (gpioInitialise() < 0) {
		cout << "Error initializing pigpio library..." << endl;
		exit(-1);
	}
	gpioSetMode(O_LED, PI_OUTPUT);
	gpioSetMode(O_LED2, PI_OUTPUT);
	string topic2 {"Diode/2"};
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);
	cout << "Yo" << endl;
	try {
// Connect to the server
		cout << "Connecting to the MQTT server..." << flush;
		cli.start_consuming();
		cli.connect()->wait();
		cli.subscribe("Test", 1)->wait();

		while (1) {

			/* Methode bloquante */

			//auto msg = cli.consume_message();

			/*Methode non bloquante*/

			mqtt::const_message_ptr msg;
			bool verif = cli.try_consume_message(&msg);
			if (verif) {
				if (msg->to_string() == "On") {
					gpioWrite(O_LED, 1);

				}
				if (msg->to_string() == "Off") {
					gpioWrite(O_LED, 0);
				}
				cout << "LED: " << msg->to_string() << endl;

			}
			gpioWrite(O_LED2, !(gpioRead(O_LED2)));
			if(gpioRead(O_LED2)){
				cli.publish(topic2, "On");
			}
			else{
				cli.publish(topic2, "Off");
			}
			sleep(1);
		}

	} catch (const mqtt::exception &exc) {
		cerr << "\n " << exc << endl;
		return 1;
	}

	cout << "\nNow, the program is connected to the broker" << flush;

	try {
		if (cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..."
					<< flush;
			cli.disconnect()->wait();
			cout << "\nNow it is disconnected..." << flush;
		} else {
			cout << "\nClient was already disconnected" << flush;
		}
	} catch (const mqtt::exception &exc) {
		cerr << "\n " << exc << endl;
		return 1;
	}

	return 0;
}
