#include "stdafx.h"
#pragma once

class CNalUint
{
public:
	CNalUint(uint8_t *pSODB, uint32_t SODBLength);
	~CNalUint();
private:
	uint8_t    *m_pSODB;
	uint32_t   m_SODBLength;
		   
};

