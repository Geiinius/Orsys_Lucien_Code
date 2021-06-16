#include <iostream>
#include <pigpio.h>
#include <curl/curl.h>
#define I_PUSH 2 // Using GPIO2
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,void *userp);

int main() {
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	const char *urlTemplate = "https://maker.ifttt.com/trigger/Bouton/with/key/bEqdn0Klzr28Sg0zKggd5c";


	cout << "Running pigpio program" << endl;

	if (gpioInitialise()<0) {
		cout<<"Failure..."<<endl;
		exit(-1);
	}
	gpioSetMode(I_PUSH,PI_INPUT);
	gpioSetPullUpDown(I_PUSH,PI_PUD_UP);

//init request
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, urlTemplate);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	while(1)
	{
		if (gpioRead(I_PUSH)==0) {
			while (gpioRead(I_PUSH)==0);
			if (curl) {
				res = curl_easy_perform(curl);
				cout << "Requete exécutée" <<endl;
			}
		}
	}

	curl_easy_cleanup(curl);
	return 0;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}
