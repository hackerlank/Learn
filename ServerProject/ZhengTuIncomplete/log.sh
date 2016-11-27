#!/bin/sh

#日志监视脚本
#监视plateserver   ./log.sh pl
#监视superserver   ./log.sh su
#监视recordserver  ./log.sh re
#监视sessionserver ./log.sh se
#监视sceneserver   ./log.sh sc
#监视npcserver     ./log.sh np
#监视gatewayserver ./log.sh ga
#监视gm指令        ./log.sh gm
#监视所有日志      ./log.sh

PARA=$1
CONFIG="config.xml"

main()
{
	##平台服务器日志
	PLATELOG=`grep plateserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##管理服务器日志
	SUPERLOG=`grep superserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##档案服务器日志
	RECORDLOG=`grep recordserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##会话服务器日志
	SESSIONLOG=`grep sessionserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##场景服务器日志
	SCENELOG=`grep sceneserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##npc服务器日志
	NPCLOG=`grep npcserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##网关服务器日志
	GATEWAYLOG=`grep gateway.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##名字服务器日志
	NAMELOG=`grep nameserver.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##gm日志
	GMLOG=`grep gm.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##异常日志
	EXCEPTIONLOG=`grep exception.log $CONFIG | sed -e 's/<[a-zA-Z]*>//' | sed -e 's/<\/[a-zA-Z]*>//'`
	##所有日志
	ALL=$PLATELOG" "$SUPERLOG" "$RECORDLOG" "$SESSIONLOG" "$SCENELOG" "$GATEWAYLOG" "
	clear
	case $PARA in
		pl)
		tail --follow=name --retry $PLATELOG --max-unchanged-stats=3 -n 40 -q
		;;
		su)
		tail --follow=name --retry $SUPERLOG --max-unchanged-stats=3 -n 40 -q
		;;
		re)
		tail --follow=name --retry $RECORDLOG --max-unchanged-stats=3 -n 40 -q
		;;
		se)
		tail --follow=name --retry $SESSIONLOG --max-unchanged-stats=3 -n 40 -q
		;;
		sc)
		tail --follow=name --retry $SCENELOG --max-unchanged-stats=3 -n 40 -q
		;;
#		np)
#		tail --follow=name --retry $NPCLOG --max-unchanged-stats=3 -n 40 -q
#		;;
		ga)
		tail --follow=name --retry $GATEWAYLOG --max-unchanged-stats=3 -n 40 -q
		;;
#		na)
#		tail --follow=name --retry $NAMELOG --max-unchanged-stats=3 -n 40 -q
#		;;
#		ex)
#		tail --follow=name --retry $EXCEPTIONLOG --max-unchanged-stats=3 -n 40 -q
#		;;
#		gm)
#		tail --follow=name --retry $GMLOG --max-unchanged-stats=3 -n 40 -q
#		;;
		*)
		tail --follow=name --retry $ALL --max-unchanged-stats=3 -n 5 -q
		;;
	esac
}
main










