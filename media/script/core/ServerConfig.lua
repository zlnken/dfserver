-------------------------------------------------------------------------
local P = {}
-------------------------------------------------------------------------
-- 服务器配置
P["172.16.80.23"] = {name="zhenkeluo",id =1, host="localhost", user="root", passwd="root", db_port=3306, server_port=8000, ip="172.16.80.23"}
P["172.16.80.60"] = {name="cyl",id =2, host="localhost", user="root", passwd="root", db_port=3306, server_port=8000, ip="172.16.80.60"}
P["192.168.1.103"] = {name="sword",id =3, host="localhost", user="root", passwd="990529", db_port=3306, server_port=8000, ip="192.168.1.103"}
P["192.168.1.105"] = {name="swordmac",id =4, host="192.168.1.105", user="root", passwd="root", db_port=3306, server_port=8000, ip="192.168.1.105"}
-------------------------------------------------------------------------
-- @brief 获取服务器配置
function P.getServerConfig(ip)
   return P[ip]
end
-------------------------------------------------------------------------
-- @brief 默认服务器
P.defaultIp = DF.LuaSystem:instancePtr():getServer():getIP()
P.default = P.getServerConfig(P.defaultIp)
-------------------------------------------------------------------------
return P

