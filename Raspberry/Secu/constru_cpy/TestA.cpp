#include "TestA.h"

TestA::TestA(int x,int y) {
// TODO Auto-generated constructor stub
	m_s =new int;
	*m_s=x+y;

}


//Constructeur pour les copies, alloue un espace 
//pour les attributs du new constructeur
TestA::TestA(const TestA& tA) {

	m_s = new int;
	*m_s = *tA.m_s;

}

int TestA::get() {
	return *m_s;
}

TestA::~TestA() {
	delete m_s;
// TODO Auto-generated destructor stub
}
