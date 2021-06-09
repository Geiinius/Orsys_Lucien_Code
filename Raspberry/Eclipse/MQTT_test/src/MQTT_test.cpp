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
#include "mqtt/async_client.h"

using namespace std;

const string SERVER_ADDRESS { "tcp://127.0.0.1:1883" };
const string CLIENT_ID { "user1" };

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);
	cout << "Yo" << endl;
	try {
// Connect to the server
		cout << "Connecting to the MQTT server..." << flush;
		cli.connect()->wait();
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
