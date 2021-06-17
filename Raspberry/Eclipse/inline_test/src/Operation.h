/*
 * Operation.h
 *
 *  Created on: 17 juin 2021
 *      Author: lucien
 */

#ifndef OPERATION_H_
#define OPERATION_H_

class Operation {
public:
	Operation();
	virtual ~Operation();
	static inline int add(int a, int b) {
		return a + b;
	}
	;
	static inline int max(int a, int b) {
		return a > b ? a : b;
	}
	;
};

#endif /* OPERATION_H_ */
