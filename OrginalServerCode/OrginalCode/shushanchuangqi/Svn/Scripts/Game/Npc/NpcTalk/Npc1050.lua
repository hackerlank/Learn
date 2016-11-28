Npc1050=
{
	Main = function ()
	   LOG_INF('call Npc1050 Main')
	   local user = GameScript:GetUser()
	   local msg = "主函数不能为空"
	   msg = msg.."[1#CLOSE#关闭！]"
	   return msg
	end,

}
