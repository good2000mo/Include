//串口命令协议用到的变量定义
Eu8 Chk_Pos;		//检测命令到达的位置
Eu8 Rx_Pos;		//记录命令的位置
Eu8 Rx_Buf[26];		//读取数据的缓冲区，两倍大小
Eu8 NewCmd;		//有新数据到来，重新检测 
Eu8 g_CurMenu;	//记录当前目录
Eu8 g_layer;		//指示触摸屏在哪一层的指令

