# Console-Gobang
控制台实现五子棋

存储棋盘的功能本来已经写好了，但是没有保存代码，我把保存棋盘用到的使用到的前置代码放到另外一个cpp文件里面，有兴趣的朋友可以去尝试一下保存棋盘到txt文件里面（也可以是其他的文件格式，甚至你能自己创造一个文件格式）

保存棋盘功能的大致思路是下面这样的，下面的函数都是放到客户端类里面，然后使用 LoopRun 函数进行调用

我们还能在main的基础上简化下棋的过程：可以一人一手，每次读取栈顶元素对应的是黑棋或者白棋。如果是黑棋，下次就下白棋；如果是白棋，下次就下黑棋；如果没有棋，下次就下白棋
