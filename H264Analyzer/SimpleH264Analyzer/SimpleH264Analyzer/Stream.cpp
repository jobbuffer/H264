#include "stdafx.h"
#include "Stream.h"
#include "NalUint.h"

#include <iostream>

using namespace std;

CStreamFile::CStreamFile(TCHAR *m_fileName)
{
	this->m_fileName = m_fileName;
	file_info();
	_tfopen_s(&m_InputFile, m_fileName, _T("rb"));
	if (NULL == m_InputFile) 
	{
		file_error(0);
	}
}

CStreamFile::~CStreamFile()
{
	if (NULL != m_InputFile)
	{
		fclose(m_InputFile);
		m_InputFile = NULL;
	}
}

void CStreamFile::file_info()
{
	if (m_fileName)
	{
		wcout << L"File name:" << m_fileName << endl;
	}
}

void CStreamFile::file_error(int idx)
{
	switch (idx)
	{
	case 0:
		wcout << L"Error: opening input file failed." << endl;
		break;
	default:
		break;
	}
}

int CStreamFile::Parse_h264_bitstream()
{
	int ret = 0;
	do
	{
		ret = file_nal_prefix();
		// ½âÎöNAL
		if (m_nalVec.size())
		{
			uint8_t nalType = m_nalVec[0] & 0x1F;
			wcout << L"NAL Uint Type:" << nalType << endl;
			ebsp_to_sodb();
			CNalUint nalUnit(&m_nalVec[1], m_nalVec.size() - 1);
		}
	} while(ret);

	return 0;
}

int CStreamFile::file_nal_prefix()
{
	uint8_t prefix[3] = { 0 };
	uint8_t fileByte;

	m_nalVec.clear();
	int pos = 0, getPrefix = 0;
	for (int idx = 0; idx < 3; ++idx)
	{
		prefix[idx] = getc(m_InputFile);
		m_nalVec.push_back(prefix[idx]);
	}

	while (!feof(m_InputFile))
	{
		if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
		{
			getPrefix = 1;
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			break;
		}
		else if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
		{
			if (1 == getc(m_InputFile))
			{
				getPrefix = 2;
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				break;
			}
		}
		else
		{
			fileByte = getc(m_InputFile);
			prefix[(pos++) % 3] == fileByte;
			m_nalVec.push_back(fileByte);
		}
	}
	return getPrefix;
}

void CStreamFile::ebsp_to_sodb()
{
	if (m_nalVec.size() < 3)
	{
		return;
	}

	for (vector<uint8_t>::iterator itor = m_nalVec.begin() + 2; itor != m_nalVec.end(); )
	{
		if ((3 == *itor) && (0 == *(itor - 1)) && (0 == *(itor - 2)))
		{
			vector<uint8_t>::iterator temp = m_nalVec.erase(itor);
			itor = temp;
		}
		else
		{
			itor++;
		}

	}
}