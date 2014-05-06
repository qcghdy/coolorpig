coolorpig
=========

个人学习project

这里主要有
一、2014年4月 学习gnu pth
    安装方法：
    1、google [gnu pth]点击进入 http://ftp.gnu.org/gnu/pth/ 并下载最新版本。
    2、解压 tar -zvf pth-2.0.7.tar.gz
    3、执行configure 生成Makefile命令
        zhu@ubuntu:~/Downloads/pth-2.0.7$ ./configure 
    4、执行make生成相应库文件
        zhu@ubuntu:~/Downloads/pth-2.0.7$ make 
    5、安装库文件到系统目录需要sudo系统权限
        zhu@ubuntu:~/Downloads/pth-2.0.7$ sudo make install
        
    6、库可以使用了。命令如下
        zhu@ubuntu:~/workspace$ g++ pth_test.cpp -lpth


二、学习tcp udp 网络通信服务器
