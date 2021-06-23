//============================================================================
// Name        : Project_POEI.cpp
// Author      : Lucien
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
#include <curl/curl.h>

#define O_LED 17
#define O_LED2 23
#define BUZZER_PWM 18
using namespace std;
uint16_t valeur;
uint nb=0;
const string SERVER_ADDRESS { "tcp://192.168.8.126:1883" };
const string CLIENT_ID { "pi" };
int pwmValue_init =0;
int pwmValue_alert =20;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}
/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

	CURLcode res;
	CURL *curl;
	std::string readBuffer;
	const char *urlTemplate = "https://maker.ifttt.com/trigger/Alarme/with/key/cWz8VKaG25leugptBiPhv";

	if (gpioInitialise() < 0) {
		cout << "Error initializing pigpio library..." << endl;
		exit(-1);
	}

	//init request
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, urlTemplate);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	//MQTT
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);

	//SPI
	uint32_t flags = 0x00;
	int hSpi = spiOpen(0, 100000, flags);
	if (hSpi > 0) {
		cout << "Error SPI initialization..." << endl;
		gpioTerminate();
		exit(-1);
	}


	//Buzzer
	gpioSetMode(BUZZER_PWM, PI_OUTPUT);
	gpioPWM(BUZZER_PWM, pwmValue_init);

	try {
// Connect to the server
		cout << "Connecting to the MQTT server..." << flush;
		cli.start_consuming();
		//cli.connect()->wait();
		//cli.subscribe("Test", 1)->wait();
		auto rsp = cli.connect()->get_connect_response();
		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our subscriptions.
		if (!rsp.is_session_present())
			cli.subscribe("Test", 1)->wait();
		if (!rsp.is_session_present())
			cli.subscribe("Nombre", 1)->wait();
		if (!rsp.is_session_present())
			cli.subscribe("Nombre/add", 1)->wait();
		if (!rsp.is_session_present())
			cli.subscribe("Nombre/sub", 1)->wait();
		if (!rsp.is_session_present())
			cli.subscribe("Alerte", 1)->wait();

		while (1) {

			/* Methode bloquante */

			//auto msg = cli.consume_message();
			/*Methode non bloquante*/

			mqtt::const_message_ptr msg;


			bool verif = cli.try_consume_message(&msg);
			if (verif) {
					if(msg->get_topic()=="Nombre/add"){
							cout << "Nombre: " << msg->to_string() << endl;
							if(nb<6)
								nb=nb+1;
					}
					if(msg->get_topic()=="Nombre/sub"){
							cout << "Nombre: " << msg->to_string() << endl;
							if(nb<6)
								nb=nb-1;
					}
					if(msg->get_topic()=="Alerte"){
						if(msg->to_string()=="ALERTE! INTRUS!")
							gpioPWM(BUZZER_PWM, pwmValue_alert);
						if(msg->to_string()=="STOP")
							gpioPWM(BUZZER_PWM, pwmValue_init);
						if (curl) {
							res = curl_easy_perform(curl);
							cout << "Requete exécutée" <<endl;
									}
						cout << msg->to_string() << endl;
					}

			}
			//sleep(5);
			char rBuffer[100];
			char sBuffer[2];
			sBuffer[0] = (char)('0'+nb);
			sBuffer[1]='!';
			cout << "Nombre :" << nb << endl;
			spiXfer(hSpi, (char*) sBuffer, (char*) rBuffer, strlen(sBuffer));
			//spiXfer(hSpi, (char*) nb, (char*) rBuffer, strlen(sBuffer));
			cout << "Received : "<< (int) rBuffer[0] << endl;
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
		spiClose(hSpi);
		curl_easy_cleanup(curl);
		gpioTerminate();
	} catch (const mqtt::exception &exc) {
		cerr << "\n " << exc << endl;
		return 1;
	}

	return 0;
}
