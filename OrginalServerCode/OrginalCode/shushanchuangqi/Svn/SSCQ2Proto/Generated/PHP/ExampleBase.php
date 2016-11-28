<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    Example.php
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//枚举类型示例
class EExTest
{
	const eExTest1 = 0; //枚举值1
	const eExTest2 = 10; //枚举值2
	const eExTest3 = 32767; //枚举值3
}

//结构体：SExBase的继承体系类型
class EType_SExBase
{
	const eType_SExBase = 0; //类型：SExBase
	const eType_SExDerived1 = 1; //类型：SExDerived1
	const eType_SExDerived2 = 2; //类型：SExDerived2
	const eType_SExDescend3 = 3; //类型：SExDescend3
	const eType_SExDescend4 = 4; //类型：SExDescend4
}

//前置声明测试
final class STest
{
	public $pBase; //(类类型：SExBase)父类指针
	public $vecBase; //(SExBase的数组)父类指针列表

	//构造函数
	function __construct()
	{
		$this->pBase = new SExBase;
		$this->vecBase = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->pBase = $this->pBase;
		$obj->vecBase = $this->vecBase;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STest;
		$s->pBase = SExBase::superFromStream($data);
		$s->vecBase = SExBase::superVectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STest::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		$this->pBase->superToStream($data);
		SExBase::superVectorToStream($data, $this->vecBase);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//只在客户端生成
final class SClient
{
	public $dwValue; //(UINT32)成员

	//构造函数
	function __construct()
	{
		$this->dwValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwValue = $this->dwValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SClient;
		$s->dwValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SClient::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//按智能指针传递的结构体
final class SPointer
{
	public $dwValue; //(UINT32)成员

	//构造函数
	function __construct()
	{
		$this->dwValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwValue = $this->dwValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPointer;
		$s->dwValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPointer::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//结构体父类型示例
class SExBase
{
	public $member1; //(UINT32)成员1
	public $vecMember2; //(string数组)成员2

	//构造函数
	function __construct()
	{
		$this->member1 = 0;
		$this->vecMember2 = array();
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SExBase::eType_SExBase;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->member1 = $this->member1;
		$obj->vecMember2 = $this->vecMember2;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SExBase;
		$s->member1 = ByteUtil::readUINT32($data);
		$s->vecMember2 = ByteUtil::readVecString($data);
		return $s;
	}

	static function superFromStream(&$data)
	{
		$eType = ByteUtil::readUINT8($data);
		switch($eType)
		{
			case EType_SExBase::eType_SExBase:
				$s = SExBase::fromStream($data);
				break;
			case EType_SExBase::eType_SExDerived1:
				$s = SExDerived1::fromStream($data);
				break;
			case EType_SExBase::eType_SExDerived2:
				$s = SExDerived2::fromStream($data);
				break;
			case EType_SExBase::eType_SExDescend3:
				$s = SExDescend3::fromStream($data);
				break;
			case EType_SExBase::eType_SExDescend4:
				$s = SExDescend4::fromStream($data);
				break;
			default:
				throw new Exception('Unknown value for EType_SExBase:'.eType);
		}
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExBase::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	static function superVectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExBase::superFromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->member1);
		ByteUtil::writeVecString($data, $this->vecMember2);
	}

	public function superToStream(&$data)
	{
		$eType = $this->getClassType();
		ByteUtil::writeUINT8($data, $eType);
		$this->toStream($data);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}

	static function superVectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->superToStream($data);
	}
}

//结构体子类型1示例
class SExDerived1 extends SExBase
{
	public $byMember3; //(UINT16)成员3
	public $qwMember4; //(INT64)成员4

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->byMember3 = 0;
		$this->qwMember4 = new Math_BigInteger;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SExBase::eType_SExDerived1;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->byMember3 = $this->byMember3;
		$obj->qwMember4 = $this->qwMember4;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SExDerived1;
		$base = SExBase::fromStream($data);
		$base->copyTo($s);
		$s->byMember3 = ByteUtil::readUINT16($data);
		$s->qwMember4 = ByteUtil::readINT64($data);
		return $s;
	}

	static function superFromStream(&$data)
	{
		$eType = ByteUtil::readUINT8($data);
		switch($eType)
		{
			case EType_SExBase::eType_SExDerived1:
				$s = SExDerived1::fromStream($data);
				break;
			case EType_SExBase::eType_SExDescend3:
				$s = SExDescend3::fromStream($data);
				break;
			case EType_SExBase::eType_SExDescend4:
				$s = SExDescend4::fromStream($data);
				break;
			default:
				throw new Exception('Unknown value for EType_SExBase:'.eType);
		}
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExDerived1::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	static function superVectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExDerived1::superFromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT16($data, $this->byMember3);
		ByteUtil::writeINT64($data, $this->qwMember4);
	}

	public function superToStream(&$data)
	{
		$eType = $this->getClassType();
		ByteUtil::writeUINT8($data, $eType);
		$this->toStream($data);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}

	static function superVectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->superToStream($data);
	}
}

//结构体子类型3示例
final class SExDescend3 extends SExDerived1
{
	public $base; //(类类型：SExBase)成员5
	public $s; //(类类型：SExDerived1)成员6
	public $vecExDerive; //(SExDerived1的数组)成员7
	public $vecExBase; //(SExBase的数组)成员8

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->base = new SExBase;
		$this->s = new SExDerived1;
		$this->vecExDerive = array();
		$this->vecExBase = array();
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SExBase::eType_SExDescend3;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->base = $this->base;
		$obj->s = $this->s;
		$obj->vecExDerive = $this->vecExDerive;
		$obj->vecExBase = $this->vecExBase;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SExDescend3;
		$base = SExDerived1::fromStream($data);
		$base->copyTo($s);
		$s->base = SExBase::superFromStream($data);
		$s->s = SExDerived1::superFromStream($data);
		$s->vecExDerive = SExDerived1::superVectorFromStream($data);
		$s->vecExBase = SExBase::superVectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExDescend3::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		$this->base->superToStream($data);
		$this->s->superToStream($data);
		SExDerived1::superVectorToStream($data, $this->vecExDerive);
		SExBase::superVectorToStream($data, $this->vecExBase);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//结构体子类型4示例
final class SExDescend4 extends SExDerived1
{
	public $wMember5; //(UINT16)成员5
	public $qwMember6; //(INT64)成员6
	public $vecExDesc; //(SExDescend3的数组)成员7

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->wMember5 = 0;
		$this->qwMember6 = new Math_BigInteger;
		$this->vecExDesc = array();
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SExBase::eType_SExDescend4;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->wMember5 = $this->wMember5;
		$obj->qwMember6 = $this->qwMember6;
		$obj->vecExDesc = $this->vecExDesc;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SExDescend4;
		$base = SExDerived1::fromStream($data);
		$base->copyTo($s);
		$s->wMember5 = ByteUtil::readUINT16($data);
		$s->qwMember6 = ByteUtil::readINT64($data);
		$s->vecExDesc = SExDescend3::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExDescend4::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT16($data, $this->wMember5);
		ByteUtil::writeINT64($data, $this->qwMember6);
		SExDescend3::vectorToStream($data, $this->vecExDesc);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//结构体子类型2示例
final class SExDerived2 extends SExBase
{
	public $dMember3; //(double)成员3
	public $bMember4; //(bool)成员4

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->dMember3 = 0;
		$this->bMember4 = false;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SExBase::eType_SExDerived2;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->dMember3 = $this->dMember3;
		$obj->bMember4 = $this->bMember4;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SExDerived2;
		$base = SExBase::fromStream($data);
		$base->copyTo($s);
		$s->dMember3 = ByteUtil::readDouble($data);
		$s->bMember4 = ByteUtil::readBool($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SExDerived2::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeDouble($data, $this->dMember3);
		ByteUtil::writeBool($data, $this->bMember4);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[SampleRetFunc2:C->S有返回值的示例函数]的原来的参数组成的结构体
class SOrigParam_SampleRetFunc2
{
	public $qwParam2; //(UINT64)参数2，保存
	public $loc_derived; //(类类型：SExDerived2)结构体，本地保存

	//构造函数
	function __construct()
	{
		$this->qwParam2 = new Math_BigInteger;
		$this->derived = new SExDerived2;
	}
};

//函数[SampleRetFunc2:C->S有返回值的示例函数]的返回的参数组成的结构体
class SRetParam_SampleRetFunc2
{
	public $vecExDescend; //(SExDescend3的数组)结构体列表，返回值
	public $strRet; //(string)字符串，返回值

	//构造函数
	function __construct()
	{
		$this->vecExDescend = array();
		$this->strRet = '';
	}
};

////////////////////////////////////////////////////////////
//协议类：通信协议示例
abstract class ExampleBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：C->S示例函数1
	function send_SampleFunc1(
		$byParam1,  //(INT8)8位有符号整数
		$wParam2,  //(INT16)16位有符号整数
		$dwParam3,  //(INT32)32位有符号整数
		$qwParam4,  //(INT64)64位有符号整数
		$byParam5,  //(UINT8)8位无符号整数
		$wParam6,  //(UINT16)16位无符号整数
		$dwParam7,  //(UINT32)32位无符号整数
		$qwParam8,  //(UINT64)64位无符号整数
		$bParam9,  //(bool)布尔值
		$fParam10,  //(float)单精度浮点数
		$dParam11,  //(double)双精度浮点数
		$strParam12,  //(string)字符串
		$strParam13,  //(string)AS字节数组
		$eTest14,  //(枚举类型：EExTest)枚举值
		$vecExDesc15 //(SExDescend4的数组)继承结构体列表
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeINT8($data, $byParam1);
		ByteUtil::writeINT16($data, $wParam2);
		ByteUtil::writeINT32($data, $dwParam3);
		ByteUtil::writeINT64($data, $qwParam4);
		ByteUtil::writeUINT8($data, $byParam5);
		ByteUtil::writeUINT16($data, $wParam6);
		ByteUtil::writeUINT32($data, $dwParam7);
		ByteUtil::writeUINT64($data, $qwParam8);
		ByteUtil::writeBool($data, $bParam9);
		ByteUtil::writeFloat($data, $fParam10);
		ByteUtil::writeDouble($data, $dParam11);
		ByteUtil::writeString($data, $strParam12);
		ByteUtil::writeString($data, $strParam13);
		ByteUtil::writeINT16($data, $eTest14);
		SExDescend4::vectorToStream($data, $vecExDesc15);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：C->S有返回值的示例函数
	function send_SampleRetFunc2(
		$byParam1,  //(UINT8)参数1，不保存
		$qwParam2,  //(UINT64)参数2，保存
		$loc_derived //(类类型：SExDerived2)结构体，本地保存
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$origParam = new SOrigParam_SampleRetFunc2;
		$origParam->qwParam2 = $qwParam2;
		$origParam->loc_derived = $loc_derived;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byParam1);
		ByteUtil::writeUINT64($data, $qwParam2);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：S->C示例函数1
	abstract function onRecv_SampleFuncAck1(
		$byParam1, //(INT8)8位有符号整数
		$wParam2, //(INT16)16位有符号整数
		$dwParam3, //(INT32)32位有符号整数
		$qwParam4, //(INT64)64位有符号整数
		$byParam5, //(UINT8)8位无符号整数
		$wParam6, //(UINT16)16位无符号整数
		$dwParam7, //(UINT32)32位无符号整数
		$qwParam8, //(UINT64)64位无符号整数
		$bParam9, //(bool)布尔值
		$fParam10, //(float)单精度浮点数
		$dParam11, //(double)双精度浮点数
		$strParam12, //(string)字符串
		$strParam13, //(string)AS字节数组
		$eTest14, //(枚举类型：EExTest)枚举值
		$vecExDesc15 //(SExDescend4的数组)继承结构体列表
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：C->S有返回值的示例函数
	abstract function onReturn_SampleRetFunc2(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_SampleRetFunc2)原来的参数
		$retParam //(类类型：SRetParam_SampleRetFunc2)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：S->C示例函数1
	private function _doRecv_SampleFuncAck1($data)
	{
		$byParam1 = ByteUtil::readINT8($data);
		$wParam2 = ByteUtil::readINT16($data);
		$dwParam3 = ByteUtil::readINT32($data);
		$qwParam4 = ByteUtil::readINT64($data);
		$byParam5 = ByteUtil::readUINT8($data);
		$wParam6 = ByteUtil::readUINT16($data);
		$dwParam7 = ByteUtil::readUINT32($data);
		$qwParam8 = ByteUtil::readUINT64($data);
		$bParam9 = ByteUtil::readBool($data);
		$fParam10 = ByteUtil::readFloat($data);
		$dParam11 = ByteUtil::readDouble($data);
		$strParam12 = ByteUtil::readString($data);
		$strParam13 = ByteUtil::readString($data);
		$eTest14 = ByteUtil::readINT16($data);
		$vecExDesc15 = SExDescend4::vectorFromStream($data);
		return $this->onRecv_SampleFuncAck1($byParam1, $wParam2, $dwParam3, $qwParam4, $byParam5, $wParam6, $dwParam7, $qwParam8, $bParam9, $fParam10, $dParam11, $strParam12, $strParam13, $eTest14, $vecExDesc15);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：C->S有返回值的示例函数
	private function _doReturn_SampleRetFunc2($data)
	{
		$retParam = new SRetParam_SampleRetFunc2;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecExDescend = SExDescend3::vectorFromStream($data); //结构体列表，返回值
		$strRet = ByteUtil::readString($data); //字符串，返回值
		$retParam->vecExDescend = $vecExDescend;
		$retParam->strRet = $strRet;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SampleRetFunc2($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：C->S有返回值的示例函数
	private function _onTimeOut_SampleRetFunc2($sessionID)
	{
		$retParam = new SRetParam_SampleRetFunc2;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_SampleRetFunc2(2, $origParam, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 255;
		$this->_recvFuncList[0] = '_doRecv_SampleFuncAck1'; //FuncID: 1

		$this->_retFuncList[0] = '_doReturn_SampleRetFunc2'; //FuncID: 1

		$this->_timeFuncList[0] = '_onTimeOut_SampleRetFunc2'; //FuncID: 1
	}

	function handleMessage($data)
	{
		$funcID = ByteUtil::readINT8($data);
		if($funcID == 0 || $funcID > count($this->_recvFuncList)
			 || $funcID < -count($this->_retFuncList))
			return false;
		if($funcID > 0)
			$func = $this->_recvFuncList[$funcID - 1];
		else
			$func = $this->_retFuncList[-$funcID - 1];
		if($func != null)
			return call_user_func(array($this, $func), $data);
		return false;
	}

	function onTimeOut($funcID, $sessionID)
	{
		if($funcID == 0 || $funcID > count($this->_timeFuncList))
			return;
		$this->_timeFuncList[$funcID - 1]($sessionID);
	}
}

?>