/*
 * gererBouton.h
 *
 *  Created on: 17 juin 2021
 *      Author: lucien
 */

#ifndef GERERBOUTON_H_
#define GERERBOUTON_H_
#include <mutex>

class GererBouton {
public:
static void lireBouton(int pin_bouton,std::mutex * m,bool *activer);
GererBouton();
virtual ~GererBouton();
};

#endif /* GERERBOUTON_H_ */
