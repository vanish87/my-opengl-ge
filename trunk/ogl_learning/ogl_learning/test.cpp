#include "StdAfx.h"
#include "test.h"


test::test(void)
{
	a=100;
	b=false;
}


test::~test(void)
{
}

void test::test1()
{
	a++;
	if(!b)
		a++;
}
