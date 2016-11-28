Npc1001 =
{
	Main = function ()
	   LOG_INF('call Npc1001 Main')
	   local user = GameScript:GetUser()
	   local msg = "我必须时刻警惕，魔物随时会攻击路过的旅人！"
	   msg = msg.."[1#Hello2#我要怎么攻击怪物]"
	   msg = msg.."[1#CLOSE#再见，提姆！]"
	   return msg
	end,

	Hello2 = function ()
	    local user = GameScript:GetUser()
	    local msg = "移动到怪物身边，并点击怪物即可进入战斗"
	    msg = msg.."[2#Main#好的，我知道了！]"	  
	    return msg
	end,
}
