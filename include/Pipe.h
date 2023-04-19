#pragma once
/*
在Linux系统中，常见的进程间通信主要包括管道通信、共享内存通信、信号量通信、消息队列通信、套接口（SOCKET）通信和全双工通信。
Linux系统除了支持信号和管道外，还支持SYSV(System V)子系统中的进程间通信机制。在SYSV的IPC机制中，包括共享内存、信号量、消息队列通信。
*/
namespace quoilam
{
    class SimplexPipe;
    class HalfDuplexPipe;
    class DuplexPipe;

    class SimplexPipe
    {
    public:
    
    };


}