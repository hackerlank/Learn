//此文件为全服数据的序列化和反序列化函数
#include <stdarg.h>
#include <zlib.h>
#include <bitset>
#include "firMD5.h"
#include "xmlconfig.h"
#include <limits>
#include "json/json.h"
#include "extractProtoMsg.h"
#include "dataManager.h"
#include "tbx.h"
#include "RecordServer.h"
#include "zMetaData.h"
#include "recordserialize.pb.h"

int RecordService::compressSaveData(BYTE *zlib)
{
    BYTE unBuf[MAX_UZLIB_CHAR] = {0};
	// 得到二进制存档
	int uzSize = RecordService::getMe().saveBinaryArchive(unBuf, MAX_UZLIB_CHAR);
	uLongf zsize = zSocket::MAX_DATASIZE;
	
    //数据过大，内存越界
	if (uzSize >= MAX_UZLIB_CHAR)
	{
		Fir::logger->error("[压缩全服数据]超过最大数值MAX_UZLIB_CHAR=%u, uzsize=%d, zsize=%u", MAX_UZLIB_CHAR,uzSize ,(DWORD)zsize);
	    return 0;
    }

	// 压缩数据
	int retcode = compress((BYTE *)zlib , &zsize , (BYTE *)unBuf , (uLongf)uzSize);
	switch(retcode)
	{
		case Z_OK:
			{
				Fir::logger->debug("压缩全服数据成功, uzsize = %d , size = %u)", uzSize , (DWORD)zsize);
				break;
			}
		case Z_MEM_ERROR:
		case Z_BUF_ERROR:
			{
				Fir::logger->debug("压缩全服数据失败");
				zsize = 0;
				break;
			}
		default:
			{
				Fir::logger->debug("压缩全服数据失败,未知原因");
				zsize = 0;
				break;
			}
	}
	return zsize;
}

void RecordService::setupBinaryArchive(const ProtoMsgData::RecordSerialize& recordBinary)
{
}

DWORD RecordService::saveBinaryArchive(BYTE *out , const int maxsize)
{
    //保存二进制数据，千万不要插队
    ProtoMsgData::RecordSerialize recordBinary; 
    recordBinary.SerializeToArray(out,maxsize);
	return recordBinary.ByteSize();
}

bool RecordService::load()
{
    if(!hasDBtable("t_recordbinary"))
    {
        return true;
    }
    return false;
}

bool RecordService::save(const bool updateFlg)
{
    if(!hasDBtable("t_recordbinary"))
    {
        return true;
    }
    return false;
}

bool RecordService::test()
{
    //需要把字符串的结束符'\0'也一并处理
    char text[] = "zlib compress and uncompress test\nturingo@163.com\n2012-11-05\n";
    uLongf tlen = strlen(text) + 1;
    char* buf = NULL;
    uLongf blen = 100;  
    
    /* 计算缓冲区大小，并为其分配内存 */  
    blen = compressBound(tlen);  
    if((buf = (char*)malloc(sizeof(char) * blen)) == NULL) 
    {
        printf("no enough memory!\n");
        return false; 
    }
    /* 压缩 */ 
    if(compress((BYTE*)buf, &blen, (BYTE*)text, tlen) != Z_OK) 
    {
        printf("compress failed!\n"); 
        return false;
    }
    
    /* 解压缩 */  
    if(uncompress((BYTE*)text, &tlen, (Bytef*)buf, blen) != Z_OK) 
    {
        printf("uncompress failed!\n");
        return false; 
    }
    
    /* 打印结果，并释放内存 */  
    printf("%s", text);
    if(buf != NULL)  
    {
        free(buf);  
        buf = NULL;  
    } 
    return true;
}

