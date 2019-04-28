#include "stdafx.h"
#include "NalUint.h"


CNalUint::CNalUint(uint8_t *pSODB, uint32_t SODBLength)
{
	m_pSODB = pSODB;
	m_SODBLength = SODBLength;
}


CNalUint::~CNalUint()
{
}
