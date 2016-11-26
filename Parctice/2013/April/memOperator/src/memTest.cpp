#include"memTest.h"
using namespace std; 
int main(void) 
{    
	memcached_st*                 memc_s;    
	memcached_server_list_st     server_list;    
	memcached_return_t             rc;           
	size_t         key_length;     
	size_t         	value_length;    
	time_t         expiration;     
	uint32_t     flags;                       
	memc_s = memcached_create(NULL);     
	server_list = NULL;     
	expiration = 0;     
	flags = 0;     
	char server_ip[] = "localhost";     
	int server_port = 11211;           
	server_list = memcached_server_list_append(server_list,server_ip,server_port,&rc);         
	if(rc == MEMCACHED_FAILURE)     
	{         
		cout<<"adds a server to the memcached_server_list failure"<<endl;       
		exit(1);    
	}   
    //pushes an array of memcached_server_st into the memcached_st struct    
	rc = memcached_server_push(memc_s, server_list);     
	if(rc == MEMCACHED_FAILURE)   
	{       
		cout<<"memcached_server_push failure"<<endl;        
		exit(1);   
	}     
	string key = "key";     
	string value = "value";       
	rc = memcached_set(memc_s,key.c_str(),key.length(),value.c_str(),value.length(),expiration,flags);    
	if(rc == MEMCACHED_SUCCESS) 
    {        
		cout<<"set data :"<<value<<" success"<<endl; 
	}   
	else   
	{    
		cout<<"set data :"<<value<<" failure"<<endl; 
	}       
    char *result = memcached_get(memc_s,key.c_str(),key_length,&value_length,&flags,&rc); 
    if(rc == MEMCACHED_SUCCESS)
	{     
		cout<<"get data :"<<result<<" success"<<endl;    
	}   
    memcached_server_list_free(server_list);      
	memcached_free(memc_s);    
	return 1; 
	
	cout<<"go here:"<<endl;
} 


