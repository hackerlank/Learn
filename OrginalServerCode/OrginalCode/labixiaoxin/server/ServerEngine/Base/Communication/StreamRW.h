#pragma once

#include "ace\ACE.h"

class StreamRW
{
public:
	enum{
		STREAM_START = 0,
		STREAM_CUR,
		STREAM_END
	};

	StreamRW();
	StreamRW(char *buf, int bufSize);

	void reset();
	void reset(char *buf, int bufSize);
	void setCursor(int offset, int type);
	int getCursor();

	int readFloat(float &v);
	int writeFloat(float v);
	int readInt64(ACE_UINT64 &v);
	int writeInt64(ACE_UINT64 v);
	int readSignedInt(int &v);
	int readInt(ACE_UINT32 &v);
	int readInt(ACE_INT32 &v);
	int writeInt(ACE_UINT32 v);
	int readShort(ACE_UINT16 &v);
	int writeShort(ACE_UINT16 v);
	int readUTF8(wchar_t *str, int len);
	int writeUTF8(wchar_t *str, int len);
	int readString(char *str, int len);
	int writeString(char *str, int len);
	int readStringFixLen(char *str, int len);
	int writeStream(char *data, int len);
	int readStream(char *data, int len);
	int left();
	
	int readNumber(char *v, int v_size);
private:
	
	int writeNumber(char *v, int v_size);

	//int readInteger(ACE_UINT64 &v, int v_size);
	//int writeInteger(ACE_UINT64 v, int v_size);

	inline int isEnoughSpace(int nSize);

	char *m_streamBuf;
	int m_bufSize;
	int m_cursor;
	int m_bBigEndian;
};