#define SIZE 1024
#define TCP 0
#define UDP 1

typedef struct {
	char local_IP[SIZE];
	int local_Port;
	char rem_IP[SIZE];
	int rem_Port;
	int inode;
} Connection_INFO;

void Translate_IPv4_INFO(Connection_INFO* info, const char* line);
void Translate_IPv6_INFO(Connection_INFO* info, const char* line);
void List_Connection_INFO(int protocol, const char* filter);

