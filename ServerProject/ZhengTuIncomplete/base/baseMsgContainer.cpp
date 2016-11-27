#include "baseMsgContainer.h"
template<>
BufferCmdQueue::ByteBuffer():m_maxSize(trunkSize),m_offPtr(0),m_curPtr(0),m_buffer(m_maxSize)
{
}
template<>
StackCmdQueue::ByteBuffer():m_maxSize(PACKET_ZIP_BUFFER),m_offPtr(0),m_curPtr(0)
{
}
template<>
void BufferCmdQueue::wrReserve(const DWORD size)
{
	if(wrSize() < size)
	{
		m_maxSize += trunkSize * trunkCount(size+8);
		m_buffer.resize(m_maxSize);
	}
}

///栈不能动态扩增
template<>
void StackCmdQueue::wrReserve(const DWORD size)
{
	assert(wrSize() >= size);
}

