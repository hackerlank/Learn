/***********************************************
* 文件类型：实现文件
* 文件名称：libev.cpp
* 文件作用：接受和发送命令等函数的实现
**********************************************/
#include<unistd.h>

#include<fcntl.h>
#include "libev.h"
#include "my_memcached.h"

#include"command_return_define_data.h"
#include "GM_communicate.h"
#include"command_user_role_manage.h"
#include "account_communication.h"

using namespace std;
/**	与套接字描述符绑定的消息接收队列 **/
extern map<int, Message_Receive>   message_queue;

extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
extern vector<FUN>command_map;

extern char server_name[10];//服务器名字

extern int flag_registe_type_exit;

extern char cross_domain_str[256];

extern struct event_base *loops;

extern map<int, Role*> fd_to_pRole;

//缓存服务器配置表
extern map<string, Mem_configure> mem_configure_table;

//字符串长度联合体
union BufLen
{
	int l;
	char lstr[4];
};
//added by benliao
int g_msg_len = 0;
Hero* pg_hero = 0;
Role *pg_role = 0;

char g_out_buf[20480];
char cmdbuf[10240];
int logSrvFd;

char log_msg[256];//日志用到的字符串；
int rechargeSrvFd; //充值服务器函数；
int cdKeySrvFd;

void con_log_server();
void msg_process(Message_Receive *);
void event_cb(struct bufferevent *bev, short what, void *arg)
{
    cout << "event_cd called" << endl;
    int fd = (long)arg;
    exit_accident(fd);
    fd_to_pRole.erase(fd);  //added by benliao 2012.12.1
    message_queue.erase(fd);
    bufferevent_disable(bev, EV_READ | EV_WRITE);
    bufferevent_free(bev);
    bev = NULL;
    close(fd);
}

/**
*充值服务器宕机处理函数；
*/
void event_recharge_cb(struct bufferevent *bev, short what, void *arg)
{
    cout << "[XHM WARING] Recharge Server to stop working!" << endl;
    int fd = (long)arg;

    map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
    if (iter == message_queue.end())
    {
		sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,1,"上次链接的IP","上次链接的端口",7,fd);
		write_log(log_msg);//写日志服务器；
	}else{
		sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,1,iter->second.ip_str,"上次链接的端口",0,fd);
		write_log(log_msg);//写日志服务器；
	}

    message_queue.erase(rechargeSrvFd);
    bufferevent_disable(bev, EV_READ | EV_WRITE);
    bufferevent_free(bev);//关闭监听
    bev = NULL;
    close(rechargeSrvFd);
	rechargeSrvFd=-1;
}

/**
 * cdkey服务器宕机处理函数；
 */
void event_cdkey_cb(struct bufferevent *bev, short what, void *arg)
{
    cout << "[XHM WARING] cdkey Server to stop working!" << endl;
    int fd = (long)arg;

    map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
    if (iter == message_queue.end())
    {
		// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,1,"上次链接的IP","上次链接的端口",7,fd);
		// write_log(log_msg);//写日志服务器；
	}else{
		// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,1,iter->second.ip_str,"上次链接的端口",0,fd);
		// write_log(log_msg);//写日志服务器；
	}

    message_queue.erase(cdKeySrvFd);
    bufferevent_disable(bev, EV_READ | EV_WRITE);
    bufferevent_free(bev);//关闭监听
    bev = NULL;
    close(cdKeySrvFd);
	cdKeySrvFd=-1;
}

void read_cb(struct bufferevent *bev, void *arg)
{
    int len;
    const char *policy = "<policy-file-request/>";

    int fd = (long)arg;
    sock_fd = fd;

    unsigned char *mem;
    struct evbuffer *in = bufferevent_get_input(bev);
    if (evbuffer_search(in, policy, strlen(policy), 0).pos >= 0)
    {
        bufferevent_write(bev, &cross_domain_str, strlen(cross_domain_str) + 1);
        cout << "policy ok" << endl;
        return;
    }
	if (evbuffer_search(in, "getgs", strlen("getgs"), 0).pos >= 0)
	{
		returnGlobalSize();
		return;
	}
    mem = evbuffer_pullup(in, 8);
    int cmdlen = 0, index = 0;
    while (evbuffer_get_length(in) >= 8)
    {
        mem = evbuffer_pullup(in, 8);

        if (*mem != 0xff)
        {
            evbuffer_drain(in, 1);
            continue;
        }
        if (*(mem + 1) != 0xd8)
        {
            evbuffer_drain(in, 2);
            continue;
        }
        memset(cmdbuf, 0, sizeof(cmdbuf));
        memcpy(&cmdlen, mem + 4, 4);
        cmdlen = ntohl(cmdlen);

        if ((cmdlen < 0) || (cmdlen > 4096))
        {
            evbuffer_drain(in, 8);
            continue;
        }

        if (evbuffer_get_length(in) < cmdlen + 8)
        {
            break;
        }
        index = *(mem + 2) * MAX_EACH_TYPE_COMMAND + *(mem + 3);
        if (((index < 0) || (index >= EFFECT_COMMAND_RANGE)) || (NULL == command_map[index]))
        {
            evbuffer_drain(in, 8);
            continue;
        }
        evbuffer_remove(in, cmdbuf, cmdlen + 8);
        // printf("Read_cb cmdf:%d\tcmds:%d\n", (int)*(mem + 2), (int)*(mem + 3));
		// printf("index1 :",index);
		//test by bison
		//write_log("hello world I'm coming!");
		g_msg_len = cmdlen;

		map<int, Role*> ::iterator iterRole=fd_to_pRole.find(sock_fd);
        if(iterRole==fd_to_pRole.end())
		{
			pg_role = 0;
			pg_hero = 0;
        }
		else
		{
			pg_role=iterRole->second;
			pg_hero=pg_role->getActive_hero();
		}
		if((pg_role == 0) && (pg_hero == 0) && !((index == 1)||(index ==3) || (index ==50) || (index ==52) || (index ==51)))
		{
			event_cb(bev, 0, (void*)fd);
			// printf("read_cb cmdf2:%d\tcmds:%d\n", (int)*(mem + 2), (int)*(mem + 3));
			return;
		}

		map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
		if(iter == message_queue.end())
		{
			cout<<fd<<":this client have no Message object in message_queue"<<endl;
			return;
		}
		Message_Receive *_message_receive = &(iter->second);
		if(_message_receive->io_watcher == NULL)
			return;
		unsigned char c = (unsigned char)*(cmdbuf+8+cmdlen-1);
		// printf("@@Tory: c:%d\n", (int)c);
		// printf("@@Tory: _message_receive->t:%d\n", (int)_message_receive->t);
		if(_message_receive->t == c)
		{
			event_cb(bev, 0, (void*)fd);
			return ;
		}
		_message_receive->t = c;

		int i ;
		for(i = 0; i < cmdlen-1; i++)
		{
			*(cmdbuf+8+i) = *(cmdbuf+8+i)^_message_receive->t;
		}
		*(cmdbuf+8+i) = '\0';
		memset(g_out_buf,0,sizeof(g_out_buf));
		command_map[index](cmdbuf + 2);
    }
}

/**
 * 充值服务器消息处理
 */
void read_recharge_cb(struct bufferevent *bev, void *arg)
{
    int len;
    const char *policy = "<policy-file-request/>";

    int fd = (long)arg;
    sock_fd = fd;
	cout<<"[XHM MSG] read_recharge_cb the read_cb the fd:"<<fd<<"the rechargeSrvFd:"<<rechargeSrvFd<<endl;

    unsigned char *mem;
    struct evbuffer *in = bufferevent_get_input(bev);
    if (evbuffer_search(in, policy, strlen(policy), 0).pos >= 0)
    {
        bufferevent_write(bev, &cross_domain_str, strlen(cross_domain_str) + 1);
        cout << "policy ok" << endl;
        return;
    }

    mem = evbuffer_pullup(in, 8);
    int cmdlen = 0, index = 0;
    while (evbuffer_get_length(in) >= 8)
    {
        mem = evbuffer_pullup(in, 8);

		printf("mem[0]:%d,mem[1]:%d,mem[2]:%d,mem[3]:%d\n",mem[0],mem[1],mem[2],mem[3]);

        if (*mem != 0xff)
        {
            evbuffer_drain(in, 1);
            continue;
        }
        if (*(mem + 1) != 0xd8)
        {
            evbuffer_drain(in, 2);
            continue;
        }
        memset(cmdbuf, 0, sizeof(cmdbuf));
        memcpy(&cmdlen, mem + 4, 4);

		printf("TEST cmdlen %d\n",cmdlen);
        cmdlen = ntohl(cmdlen);
		printf("TEST cmdlen %d\n",cmdlen);


        if ((cmdlen < 0) || (cmdlen > 4096))
        {
            evbuffer_drain(in, 8);
            continue;
        }

        if (evbuffer_get_length(in) < cmdlen + 8)
        {
			cout<<"return from evbuffer_get_length(in) < cmdlen + 8"<<endl;
            break;
        }
        index = *(mem + 2) * MAX_EACH_TYPE_COMMAND + *(mem + 3);
        if (((index < 0) || (index >= EFFECT_COMMAND_RANGE)) || (NULL == command_map[index]))
        {
			cout<<"return index:"<<index<<endl;
            evbuffer_drain(in, 8);
            continue;
        }
        evbuffer_remove(in, cmdbuf, cmdlen + 8);
        printf(" read_recharge_cb Read_cb cmdf:%d\tcmds:%d\n", (int)*(mem + 2), (int)*(mem + 3));
		g_msg_len = cmdlen;

		 printf(" the cmdbuf+8:%d\n",*(cmdbuf+8));
		 printf(" the cmdbuf+10:%d\n",*(cmdbuf+10));
		 printf(" the cmdbuf+15:%d\n",*(cmdbuf+15));
		 printf(" the cmdbuf+20:%d\n",*(cmdbuf+20));

		memset(g_out_buf,0,sizeof(g_out_buf));
		command_map[index](cmdbuf + 2);
    }
}

/**
 * cdkey服务器消息处理
 */
void read_cdkey_cb(struct bufferevent *bev, void *arg)
{
    int len;
    const char *policy = "<policy-file-request/>";

    int fd = (long)arg;
    sock_fd = fd;
	cout<<"[XHM MSG] read_cdkey_cb the read_cb the fd:"<<fd<<"the rechargeSrvFd:"<<rechargeSrvFd<<endl;

    unsigned char *mem;
    struct evbuffer *in = bufferevent_get_input(bev);
    if (evbuffer_search(in, policy, strlen(policy), 0).pos >= 0)
    {
        bufferevent_write(bev, &cross_domain_str, strlen(cross_domain_str) + 1);
        cout << "policy ok" << endl;
        return;
    }

    mem = evbuffer_pullup(in, 8);
    int cmdlen = 0, index = 0;
    while (evbuffer_get_length(in) >= 8)
    {
        mem = evbuffer_pullup(in, 8);

		printf("mem[0]:%d,mem[1]:%d,mem[2]:%d,mem[3]:%d\n",mem[0],mem[1],mem[2],mem[3]);

        if (*mem != 0xff)
        {
            evbuffer_drain(in, 1);
            continue;
        }
        if (*(mem + 1) != 0xd8)
        {
            evbuffer_drain(in, 2);
            continue;
        }
        memset(cmdbuf, 0, sizeof(cmdbuf));
        memcpy(&cmdlen, mem + 4, 4);

		printf("TEST cmdlen %d\n",cmdlen);
        cmdlen = ntohl(cmdlen);
		printf("TEST cmdlen %d\n",cmdlen);


        if ((cmdlen < 0) || (cmdlen > 4096))
        {
            evbuffer_drain(in, 8);
            continue;
        }

        if (evbuffer_get_length(in) < cmdlen + 8)
        {
			cout<<"return from evbuffer_get_length(in) < cmdlen + 8"<<endl;
            break;
        }
        index = *(mem + 2) * MAX_EACH_TYPE_COMMAND + *(mem + 3);
        if (((index < 0) || (index >= EFFECT_COMMAND_RANGE)) || (NULL == command_map[index]))
        {
			cout<<"return index:"<<index<<endl;
            evbuffer_drain(in, 8);
            continue;
        }
        evbuffer_remove(in, cmdbuf, cmdlen + 8);
        printf(" read_cdkey_cb Read_cb cmdf:%d\tcmds:%d\n", (int)*(mem + 2), (int)*(mem + 3));
		g_msg_len = cmdlen;

		 printf(" the cmdbuf+8:%d\n",*(cmdbuf+8));
		 printf(" the cmdbuf+10:%d\n",*(cmdbuf+10));
		 printf(" the cmdbuf+15:%d\n",*(cmdbuf+15));
		 printf(" the cmdbuf+20:%d\n",*(cmdbuf+20));

		memset(g_out_buf,0,sizeof(g_out_buf));
		command_map[index](cmdbuf + 2);
    }
}

void accept_cb(evutil_socket_t listener, short ev, void *arg)
{

	cout<<"[XHM MSG]:in the accept_cb "<<endl;

    struct event *listener_event = (struct event *)arg;
    struct sockaddr_in ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr *)&ss, &slen);

    /*XXX check it */
    event_add(listener_event, NULL);

    if (!loops)
    {
        cout << "BisonWarn: no loops" << endl;
    }
    struct bufferevent *bufEvent = bufferevent_socket_new(loops, fd, BEV_OPT_CLOSE_ON_FREE);

    if (fd < 0)
    {
        perror("accept");
    } else if (fd > FD_SETSIZE)
    {
		perror("fd>FD_SETSIZE");
        close(fd);
    } else
    {
        char buffer[16];
        memset(buffer, 0, 16);
        int port = ntohs(ss.sin_port);
        inet_ntop(AF_INET, &(ss.sin_addr.s_addr), buffer, 16); //INET_ADDRSTRLEN
        printf("addr:%s (%d) connected!\n", buffer, port);

        Message_Receive _message_receive;
        _message_receive.io_watcher = bufEvent;
        strncpy(_message_receive.ip_str, buffer, 16);
		_message_receive.t = 0x0;	//初始化XOR key
        message_queue[fd] = _message_receive;        //只要有新连接，则将之前的fd对应的缓存覆盖掉

        int flags = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);

		cout<<"accept_cb fd:"<<fd<<endl;
        bufferevent_setcb(bufEvent, read_cb, NULL, event_cb, (void *)fd);
        bufferevent_enable(bufEvent, EV_READ);

    }
}

void run_loop(int port)
{
	con_log_server();

	if(!con_recharge_server())//初始化充值服务器函数；
	{
		cout<<"[XHM MSG] con_recharge_server ERROR!"<<endl;
		// return;
	}

	// if(!con_cdkey_server())//初始化cdkey服务器函数；
	// {
		// cout<<"[XHM MSG] con_cdkey_server ERROR!"<<endl;
		// return;
	// }

    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event *listener_event;
    if (!loops) return; /*XXXerr*/

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);
    //设置reuse
    int so_reuseaddr = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(so_reuseaddr));

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        return;
    } else
    {

        int size = sizeof(sin);
        getsockname(listener, (sockaddr *)&sin, (socklen_t *)&size);
        //fprintf(stdout,"IP BIND SUCCESS,address: %s\t port: %d\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
    }

    if (listen(listener, 1024) < 0)
    {
        perror("listen");
        return;
    }

    printf("SOCKET CREATE SUCCESS\n");

    listener_event = event_new(loops, listener, EV_READ, accept_cb, (void *)listener_event);
    event_assign(listener_event, loops, listener, EV_READ, accept_cb, (void *)listener_event);

    /*XXX check it */
    event_add(listener_event, NULL);
    event_base_dispatch(loops);
}

//关闭套接字
void closeConnect(int fd)
{
    map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
    if (iter == message_queue.end())
    {
        cout << fd <<fd<<":  this client have no Message object in message_queue at send" << endl;
        return;
    }
    Message_Receive *_message_receive = &(iter->second);
    if (_message_receive->io_watcher)
    {
        event_cb(_message_receive->io_watcher, BEV_EVENT_READING, (void *)fd);
    }
}

bool write_log(char* buffer)
{
	BufLen len;
	if (buffer == NULL)
	{
		return false;
	}

	sprintf(buffer + strlen(buffer), ",%s", server_name);

	len.l = strlen(buffer);
	if (len.l <= 0 || len.l >= 5500)
	{
		cout<<"write log len is invalid!"<<endl;
		return false;
	}
	char logMsg[5600] = {0};
	logMsg[0] = 0x5E;
	logMsg[1] = 0x5E;
	memcpy(logMsg + 2, len.lstr, 4);
	memcpy(logMsg + 6, buffer, len.l);
	int ret = write(logSrvFd, logMsg, len.l + 6);
	if (ret == -1)
	{
		con_log_server();
		write(logSrvFd, logMsg, len.l + 6);
	}
	// cout<<"[Bison] write one log to log server "<<endl;
	// cout<<"logbuffer is :"<<buffer<<endl;
	// write(logSrvFd, buffer, strlen(buffer));
	return true;
}

void con_log_server()
{
	struct sockaddr_in pin;
	struct hostent *nlp_host;

	map<string, Mem_configure>::iterator it_mem_conf = mem_configure_table.find("log_server");
	if (it_mem_conf == mem_configure_table.end())
	{
		return;
	}
	Mem_configure *p_mem_conf = &it_mem_conf->second;

	//解析域名，如果是IP则不用解析，如果出错，显示错误信息
	while ((nlp_host=gethostbyname(p_mem_conf->server_ip))==0)
	{
		printf("Resolve Error!\n");
	}


	//设置pin变量，包括协议、地址、端口等，此段可直接复制到自己的程序中
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;                 //AF_INET表示使用IPv4
	pin.sin_addr.s_addr=htonl(INADDR_ANY);
	pin.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;
	pin.sin_port=htons(p_mem_conf->server_port);

	//建立socket
	logSrvFd = socket(AF_INET,SOCK_STREAM,0);
	cout<<"[Bison] logSrvFd conn is "<<logSrvFd<<endl;
	//建立连接
	int i = 5;
	while (--i && connect(logSrvFd, (struct sockaddr*)&pin, sizeof(pin))== -1)
	{
	  printf("Connect LogServer Error!\n");
	}
	if (i != 0)
	{
		printf("Connect LogServer SUCCESS!\n");
	}

}

/**
*初始化充值服务器函数
*/
bool con_recharge_server()
{
	struct sockaddr_in pin;
	struct hostent *nlp_host;

	map<string, Mem_configure>::iterator it_mem_conf = mem_configure_table.find("recharge_server");
	if (it_mem_conf == mem_configure_table.end())
	{
		cout<<"[XHM WARNING] mem_configure_table.find \"recharge_server\" Error!"<<endl;

		sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,"配置未达到IP","配置未找到端口",6,rechargeSrvFd);
		write_log(log_msg);//写日志服务器；

		return false;
	}
	Mem_configure *p_mem_conf = &it_mem_conf->second;

	//解析域名，如果是IP则不用解析，如果出错，显示错误信息
	if((nlp_host=gethostbyname(p_mem_conf->server_ip))==0)
	{
		rechargeSrvFd=-1;
		cout<<"[XHM WARNING] rechargeSrvHost Resolve Error!"<<endl;

		sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,5,rechargeSrvFd);
		write_log(log_msg);//写日志服务器；

		return false;
	}

	//设置pin变量，包括协议、地址、端口等，此段可直接复制到自己的程序中
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;                 //AF_INET表示使用IPv4
	pin.sin_addr.s_addr=htonl(INADDR_ANY);
	pin.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;
	pin.sin_port=htons(p_mem_conf->server_port);


	rechargeSrvFd = socket(AF_INET,SOCK_STREAM,0);
	cout<<"[XHM MSG] rechargeSrvFd connection Fd is "<<rechargeSrvFd<<endl;

	//建立连接
	int i = 5;
	while (--i && connect(rechargeSrvFd, (struct sockaddr*)&pin, sizeof(pin))== -1)
	{
	  cout<<"[XHM WARNING] Connect rechargeSrvServer Error!"<<endl;
	}
	if (i != 0)
	{
		cout<<"[XHM MSG] Connect Recharge Server SUCCESS!"<<endl;

	  //添加到监听序列
		if(!loops){
			cout << "BisonWarn: no loops" << endl;
			rechargeSrvFd=-1;

			sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,4,rechargeSrvFd);
			write_log(log_msg);//写日志服务器；

			return false;
		}
		// struct bufferevent *bufEvent = bufferevent_socket_new(loops, rechargeSrvFd, BEV_OPT_CLOSE_ON_FREE);// move it to 682 avoid memory leak <tory>

		if (rechargeSrvFd < 0)
		{
			perror("accept");
			rechargeSrvFd=-1;

			sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,3,rechargeSrvFd);
			write_log(log_msg);//写日志服务器；

			return false;
		} else if (rechargeSrvFd > FD_SETSIZE)
		{
			close(rechargeSrvFd);
			rechargeSrvFd=-1;

			sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,2,rechargeSrvFd);
			write_log(log_msg);//写日志服务器；

			return false;
		}else{
			char buffer[16];
			memset(buffer, 0, 16);
			int port = ntohs(pin.sin_port);
			inet_ntop(AF_INET, &(pin.sin_addr.s_addr), buffer, 16); //INET_ADDRSTRLEN
			printf("addr:%s (%d) connected!\n", buffer, port);

			sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,0,rechargeSrvFd);
			write_log(log_msg);//写日志服务器；

			Message_Receive _message_receive;
			_message_receive.io_watcher = bufferevent_socket_new(loops, rechargeSrvFd, BEV_OPT_CLOSE_ON_FREE);;
			strncpy(_message_receive.ip_str, buffer, 16);
			message_queue[rechargeSrvFd] = _message_receive;//只要有新连接，则将之前的fd对应的缓存覆盖掉

			int flags = fcntl(rechargeSrvFd, F_GETFL, 0);
			fcntl(rechargeSrvFd, F_SETFL, flags | O_NONBLOCK);

			int err = -1;
			int nZero=0;//设置无缓冲；
			socklen_t len=sizeof(nZero);
			err = setsockopt(rechargeSrvFd,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,len);
			if(err<0){
				printf("设置接收缓冲区大小错误\n");
			}

			// int reuse;
			// len=sizeof(reuse);
			// err = getsockopt(rechargeSrvFd,SOL_SOCKET,SO_SNDBUF,(char *)&reuse,&len);
			// cout<<"[XHM TEST] reuse:"<<reuse<<endl;
			// if(err<0){
				// printf("获取接收缓冲区大小错误\n");
			// }

			cout<<"accept_cb rechargeSrvFd:"<<rechargeSrvFd<<endl;
			bufferevent_setcb(_message_receive.io_watcher, read_recharge_cb, NULL, event_recharge_cb, (void *)rechargeSrvFd);//TODO 有问题；
			bufferevent_enable(_message_receive.io_watcher, EV_READ);
			csd_keepalive();//启动心跳；
			return true;
		}
	}
	rechargeSrvFd=-1;

	sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,1,rechargeSrvFd);
	write_log(log_msg);//写日志服务器；

	return false;
}



/**
 * 初始化cdkey服务器函数
 */
bool con_cdkey_server()
{
	struct sockaddr_in pin;
	struct hostent *nlp_host;

	map<string, Mem_configure>::iterator it_mem_conf = mem_configure_table.find("cdkey_server");
	if (it_mem_conf == mem_configure_table.end())
	{
		cout<<"[XHM WARNING] mem_configure_table.find \"cdkey_server\" Error!"<<endl;

		// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%s,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,"配置未达到IP","配置未找到端口",6,cdKeySrvFd);
		// write_log(log_msg);//写日志服务器；

		return false;
	}
	Mem_configure *p_mem_conf = &it_mem_conf->second;

	//解析域名，如果是IP则不用解析，如果出错，显示错误信息
	if((nlp_host=gethostbyname(p_mem_conf->server_ip))==0)
	{
		cdKeySrvFd=-1;
		cout<<"[XHM WARNING] cdkeyServerHost Resolve Error!"<<endl;

		// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,5,cdKeySrvFd);
		// write_log(log_msg);//写日志服务器；

		return false;
	}

	//设置pin变量，包括协议、地址、端口等，此段可直接复制到自己的程序中
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;                 //AF_INET表示使用IPv4
	pin.sin_addr.s_addr=htonl(INADDR_ANY);
	pin.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;
	pin.sin_port=htons(p_mem_conf->server_port);


	cdKeySrvFd = socket(AF_INET,SOCK_STREAM,0);
	cout<<"[XHM MSG] cdKeySrvFd connection Fd is "<<cdKeySrvFd<<endl;

	//建立连接
	int i = 5;
	while (--i && connect(cdKeySrvFd, (struct sockaddr*)&pin, sizeof(pin))== -1)
	{
	  cout<<"[XHM WARNING] Connect cdKeySrvServer Error!"<<endl;
	}
	if (i != 0)
	{
		cout<<"[XHM MSG] Connect cdKeySrvServer Server SUCCESS!"<<endl;

	  //添加到监听序列
		if(!loops){
			cout << "BisonWarn: no loops" << endl;
			cdKeySrvFd=-1;

			// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,4,cdKeySrvFd);
			// write_log(log_msg);//写日志服务器；

			return false;
		}
		// struct bufferevent *bufEvent = bufferevent_socket_new(loops, cdKeySrvFd, BEV_OPT_CLOSE_ON_FREE);// move it to 801 avoid memory leak <tory>

		if (cdKeySrvFd < 0)
		{
			perror("accept");
			cdKeySrvFd=-1;

			// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,3,cdKeySrvFd);
			// write_log(log_msg);//写日志服务器；

			return false;
		} else if (cdKeySrvFd > FD_SETSIZE)
		{
			close(cdKeySrvFd);
			cdKeySrvFd=-1;

			// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,2,cdKeySrvFd);
			// write_log(log_msg);//写日志服务器；

			return false;
		}else{
			char buffer[16];
			memset(buffer, 0, 16);
			int port = ntohs(pin.sin_port);
			inet_ntop(AF_INET, &(pin.sin_addr.s_addr), buffer, 16); //INET_ADDRSTRLEN
			printf("addr:%s (%d) connected!\n", buffer, port);

			// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,0,cdKeySrvFd);
			// write_log(log_msg);//写日志服务器；

			Message_Receive _message_receive;
			_message_receive.io_watcher = bufferevent_socket_new(loops, cdKeySrvFd, BEV_OPT_CLOSE_ON_FREE);;
			strncpy(_message_receive.ip_str, buffer, 16);
			message_queue[cdKeySrvFd] = _message_receive;//只要有新连接，则将之前的fd对应的缓存覆盖掉

			int flags = fcntl(cdKeySrvFd, F_GETFL, 0);
			fcntl(cdKeySrvFd, F_SETFL, flags | O_NONBLOCK);
			cout<<"accept_cb cdKeySrvFd:"<<cdKeySrvFd<<endl;
			bufferevent_setcb(_message_receive.io_watcher, read_cdkey_cb, NULL, event_cdkey_cb, (void *)cdKeySrvFd);//TODO 有问题；
			bufferevent_enable(_message_receive.io_watcher, EV_READ);

			return true;
		}
	}
	cdKeySrvFd=-1;

	// sprintf(log_msg,"%d,%d,%s,%d,%d,%s,%d,%d,%d",10,2,server_name,(int)myTime.tv_sec,0,p_mem_conf->server_ip,p_mem_conf->server_port,1,cdKeySrvFd);
	// write_log(log_msg);//写日志服务器；

	return false;
}


