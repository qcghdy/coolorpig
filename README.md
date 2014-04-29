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



 User-Space Context


       int pth_uctx_create(pth_uctx_t *uctx);
           This function creates a user-space context and stores it into uctx.  There is still no underlying user-space context configured. You
           still have to do this with pth_uctx_make(3). On success, this function returns "TRUE", else "FALSE".
           该函数创建一个用户空间上下文并保存在指针uctx所指的对象中。此时，并未作任何基本的用户空间上下文配置。你可以通过调用pth_uctx_make(3)接口来做到这一点。成功，函数返回TRUE，否则返回FALSE。

 
           
       int pth_uctx_make(pth_uctx_t uctx, char *sk_addr, size_t sk_size, const sigset_t *sigmask, void (*start_func)(void *), void *start_arg,
       pth_uctx_t uctx_after);
           This function makes a new user-space context in uctx which will operate on the run-time stack sk_addr (which is of maximum size
           sk_size), with the signals in sigmask blocked (if sigmask is not "NULL") and starting to execute with the call start_func(start_arg). If
           sk_addr is "NULL", a stack is dynamically allocated. The stack size sk_size has to be at least 16384 (16KB). If the start function
           start_func returns and uctx_after is not "NULL", an implicit user-space context switch to this context is performed. Else (if uctx_after
           is "NULL") the process is terminated with exit(3). This function is somewhat modeled after POSIX makecontext(3). On success, this func‐
           tion returns "TRUE", else "FALSE".
            该函数

       int pth_uctx_switch(pth_uctx_t uctx_from, pth_uctx_t uctx_to);
           This function saves the current user-space context in uctx_from for later restoring by another call to pth_uctx_switch(3) and restores
           the new user-space context from uctx_to, which previously had to be set with either a previous call to pth_uctx_switch(3) or initially
           by pth_uctx_make(3). This function is somewhat modeled after POSIX swapcontext(3). If uctx_from or uctx_to are "NULL" or if uctx_to con‐
           tains no valid user-space context, "FALSE" is returned instead of "TRUE". These are the only errors possible.

       int pth_uctx_destroy(pth_uctx_t uctx);
           This function destroys the user-space context in uctx. The run-time stack associated with the user-space context is deallocated only if
           it was not given by the application (see sk_addr of pth_uctx_create(3)).  If uctx is "NULL", "FALSE" is returned instead of "TRUE". This
           is the only error possible.

