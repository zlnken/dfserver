#dfserver
1. 需要装boost下载网址https://www.boost.org/
2. boost需要编译64位,命令是：b2 --without-python --build-type=complete toolset=msvc-12.0 threading=multi link=static address-model=64
3. 安装MySQL Server 并初始化
4. 安装MySQL Workbench 6.3
5. 安装python2.7 64位
6. 安装Python 插件 MySQLdb
7. 运行tools/restart.py
