#ifndef TESTA_H_
#define TESTA_H_

class TestA {
	private:
		int *m_s;
	public:
		TestA(int x,int y);
		int get();
		virtual ~TestA();
		TestA(const TestA&);

};

#endif /* TESTA_H_ */
