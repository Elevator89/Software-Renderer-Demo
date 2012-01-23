#ifndef INITIALIZABLE_H
#define INITIALIZABLE_H

#include "Common.h"

class Initializable {
protected:
	bool initialized;
public:
	Initializable(): initialized( false ) {};

	void Init() {
		if( !initialized ){ 
			InitSelf();
			initialized = true;
		}
	}

	void Dispose() {
		if( initialized ){
			DisposeSelf();
			initialized = false;
		}
	}

protected:
	virtual void InitSelf() = 0;
	virtual void DisposeSelf() = 0;

};

#endif