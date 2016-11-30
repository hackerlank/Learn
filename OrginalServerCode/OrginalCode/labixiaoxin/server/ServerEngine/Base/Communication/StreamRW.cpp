#include "StreamRW.h"
#include "ace/OS_NS_unistd.h"
#include "ace\OS_NS_string.h"

StreamRW::StreamRW()
{
	reset(NULL, 0);
	m_bBigEndian = 1;
}

StreamRW::StreamRW(char *buf, int bufSize)
{
	reset(buf, bufSize);
	m_bBigEndian = 1;
}

void StreamRW::reset()
{
	m_cursor = 0;
}

void StreamRW::reset(char *buf, int bufSize)
{
	m_streamBuf = buf;
	m_bufSize = bufSize;
	m_cursor = 0;
}

int StreamRW::isEnoughSpace(int nSize)
{
	if((m_bufSize - m_cursor) < nSize)
	{
		return 0;
	}

	return 1;
}

int StreamRW::readFloat(float &v)
{
	return readNumber((char *)&v, 4);
}

int StreamRW::writeFloat(float v)
{
	return writeNumber((char *)&v, 4);
}

int StreamRW::readInt64(ACE_UINT64 &v)
{
	return readNumber((char *)&v, 8);
}

int StreamRW::writeInt64(ACE_UINT64 v)
{
	return writeNumber((char *)&v, 8);
}

int StreamRW::readSignedInt(int &v)
{
	return readNumber((char *)&v, 4);
}

int StreamRW::readInt(ACE_UINT32 &v)
{
	return readNumber((char *)&v, 4);
}

int StreamRW::readInt( ACE_INT32 &v )
{
	return readNumber((char *)&v, 4);
}

int StreamRW::writeInt(ACE_UINT32 v)
{
	return writeNumber((char *)&v, 4);
}

int StreamRW::readShort(ACE_UINT16 &v)
{
	return readNumber((char *)&v, 2);
}

int StreamRW::writeShort(ACE_UINT16 v)
{
	return writeNumber((char *)&v, 2);
}

int StreamRW::readNumber(char *v, int v_size)
{
	if(isEnoughSpace(v_size) == 0)
	{
		return -1;
	}

	//int c;
	//v = 0;

	for(int i = 0;i < v_size;i ++)
	{
		//c = m_streamBuf[m_cursor + i] & 0xff;
		if(m_bBigEndian == 1)
		{
			//v = (c << ((v_size - i - 1) * 8)) | v;
			v[v_size - i - 1] = m_streamBuf[m_cursor + i];
		}
		else
		{
			//v = (c << (i * 8)) | v;
			v[i] = m_streamBuf[m_cursor + i];
		}
	}

	m_cursor += v_size;

	return 0;
}

int StreamRW::writeNumber(char *v, int v_size)
{
	if(isEnoughSpace(v_size) == 0)
	{
		return -1;
	}

	for(int i = 0;i < v_size;i ++)
	{
		if(m_bBigEndian == 1)
		{
			m_streamBuf[m_cursor + i] = v[v_size - i - 1];
		}
		else
		{
			m_streamBuf[m_cursor + i] = v[i];
		}
	}

	m_cursor += v_size;

	return 0;
}

/*
int StreamRW::readInteger(ACE_UINT64 &v, int v_size)
{
	if(isEnoughSpace(v_size) == 0)
	{
		return -1;
	}

	int c;
	v = 0;

	for(int i = 0;i < v_size;i ++)
	{
		c = m_streamBuf[m_cursor + i] & 0xff;
		if(m_bBigEndian == 1)
		{
			v = (c << ((v_size - i - 1) * 8)) | v;
		}
		else
		{
			v = (c << (i * 8)) | v;
		}
	}

	m_cursor += v_size;

	return 0;
}

int StreamRW::writeInteger(ACE_UINT64 v, int v_size)
{
	if(isEnoughSpace(v_size) == 0)
	{
		return -1;
	}

	for(int i = 0;i < v_size;i ++)
	{
		
		if(m_bBigEndian == 1)
		{
			m_streamBuf[m_cursor + i] = (v >> ((v_size - i - 1) * 8)) & 0xff;
		}
		else
		{
			m_streamBuf[m_cursor + i] = (v >> (i * 8)) & 0xff;
		}
	}

	m_cursor += v_size;

	return 0;
}
*/

int StreamRW::readUTF8(wchar_t *str, int len)
{
	ACE_UINT16 u_len;
	if(readShort(u_len) == -1)
	{
		return -1;
	}

	if(isEnoughSpace(u_len))
	{
		return -1;
	}

	int c;
	int des_len = 0;
	int i, j;

	for(i = 0;i < u_len;)
	{
		c = m_streamBuf[m_cursor + i];

		for(j = 0;j < 8;j ++)
		{
			if(((c << j) & 0x80) == 0)
			{
				break;
			}
		}

		if(des_len >= (len - 1))
		{
			break;
		}

		if(j == 0)
		{
			str[des_len] = c;
		}
		else if(j == 2)
		{
			str[des_len] = ((m_streamBuf[m_cursor + i] << 6) & 0x07c0) | (m_streamBuf[m_cursor + i + 1] & 0x3f);
		}
		else if(j == 3)
		{
			str[des_len] = ((m_streamBuf[m_cursor + i] << 12) & 0xf000) | ((m_streamBuf[m_cursor + i + 1] << 6) & 0x0fc0) | (m_streamBuf[m_cursor + i + 2] & 0x3f);
		}
		else
		{
			return -1;
		}

		i += j;

		des_len ++;
	}

	str[des_len] = '\0';

	m_cursor += u_len;

	return 0;
}

int StreamRW::writeUTF8(wchar_t *str, int len)
{
	if(writeShort(len) == -1)
	{
		return -1;
	}
	
	int t_len = 0;
	ACE_UINT32 c;

	for(int i = 0;i < len;i ++)
	{
		c = str[i];

		if(c < 0x007f)
		{
			if(isEnoughSpace(1) == 0)
			{
				return -1;
			}
			m_streamBuf[m_cursor] = (char)c;
			m_cursor ++;
		}
		else if(c < 0x07ff)
		{
			if(isEnoughSpace(2) == 0)
			{
				return -1;
			}

			m_streamBuf[m_cursor] = (char)(((c >> 6) & 0x1f) | 0xc0);
			m_streamBuf[m_cursor + 1] = (char)((c & 0x3f) | 0x80);
			m_cursor += 2;
		}
		else
		{
			if(isEnoughSpace(3) == 0)
			{
				return -1;
			}

			m_streamBuf[m_cursor] = (char)(((c >> 12) & 0x0f) | 0xe0);
			m_streamBuf[m_cursor + 1] = (char)(((c >> 6) & 0x3f) | 0x80);
			m_streamBuf[m_cursor + 2] = (char)((c & 0x3f) | 0x80);

			m_cursor += 3;
		}
	}

	return 0;
}


int StreamRW::readString(char *str, int len)
{
	char *p = m_streamBuf + m_cursor;

	if(!isEnoughSpace(len + 1))
	{
		return -1;
	}

	//int l = strlen(p);

	/*

	if((m_cursor + l) >= m_bufSize)
	{
		return -1;
	}

	if(l >= len)
	{
		return -1;
	}
	*/

	ACE_OS::strncpy(str, p, len);

	str[len] = '\0';

	m_cursor += (len + 1);

	return 0;
}


int StreamRW::readStringFixLen(char *str, int len)
{
	if((m_cursor + len) > m_bufSize)
	{
		return -1;
	}

	char *p = m_streamBuf + m_cursor;

	ACE_OS::strncpy(str, p, len);

	m_cursor += len;

	return 0;
}


int StreamRW::writeString(char *str, int len)
{
	if((m_cursor + len) >= m_bufSize)
	{
		return -1;
	}

	char *p = m_streamBuf + m_cursor;

	if(str == NULL)
	{
		*p = '\0';
	}
	else
	{
		ACE_OS::strncpy(p, str, len);
	}
	

	p[len] = '\0';

	m_cursor += (len + 1);

	return 0;
}

int StreamRW::writeStream(char *data, int len)
{
	if((m_cursor + len) >= m_bufSize)
	{
		return -1;
	}

	char *p = m_streamBuf + m_cursor;

	ACE_OS::memcpy(p, data, len);

	m_cursor += len;

	return 0;
}

int StreamRW::readStream(char *data, int len)
{
	if(len <= 0)
	{
		return 0;
	}

	if((m_cursor + len) > m_bufSize)
	{
		return -1;
	}

	char *p = m_streamBuf + m_cursor;

	ACE_OS::memcpy(data, p, len);

	m_cursor += len;

	return 0;
}

int StreamRW::left()
{
	int t = (int)(m_bufSize - m_cursor);

	return t;
}


void StreamRW::setCursor(int offset, int type)
{
	int t = 0;
	if(type == STREAM_START)
	{
		t = offset;
	}
	else if(type == STREAM_CUR)
	{
		t = m_cursor + offset;
	}
	else
	{
		t = m_bufSize + offset;
	}

	if(t < 0 || t >= m_bufSize)
	{
		return;
	}

	m_cursor = t;
}

int StreamRW::getCursor()
{
	return m_cursor;
}