#ifndef _STREAM_H_
#define _STREAM_H_

#include <vector>
#include <stdint.h>

class CStreamFile
{
public:
	CStreamFile(TCHAR *m_fileName);
	~CStreamFile();

	// Open API
	int Parse_h264_bitstream();

private:
	FILE   *m_InputFile;
	TCHAR  *m_fileName;

	std::vector<uint8_t> m_nalVec;

	void   file_info();
	void   file_error(int idx);
	int    file_nal_prefix();
	void   ebsp_to_sodb();
};


#endif