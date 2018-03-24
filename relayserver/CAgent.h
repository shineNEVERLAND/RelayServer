#pragma once

#include"global.h"

class CAgent{
	public:
		virtual void vReadOperator(){};
		virtual void vWriteOperator(){};//可以改成返回值为void，因为，如果listen agent里面，返回error，但不能把
									  //listen agent 给delete掉。除非把listen agent和relay agent的返回值设置为不同
									  //但现在可以先不管。第一次改:先把返回值改成void 
		
		CAgent();
	    virtual ~CAgent();

	protected:
		int nMySockFd;
};