#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "Sockghd.h"
#include <iostream>
using namespace std;
#pragma comment (lib,"ws2_32.lib")

BOOL CSockghd::Create(UINT nSocketPort, int nSocketType, LPCSTR lpszSocketAddress)
{
	m_hSocket = socket(AF_INET, nSocketType, 0);
	if (m_hSocket == INVALID_SOCKET)//判断用 ==  醉了
	{
		cout <<"创建socket出错：" <<  WSAGetLastError << endl;
		return FALSE;
	}
	sockaddr_in sa = { AF_INET,htons(nSocketPort) };
	if (lpszSocketAddress)
		sa.sin_addr.S_un.S_addr = inet_addr(lpszSocketAddress);
	return 0 == bind(m_hSocket, (sockaddr*)&sa, sizeof(sa));
}

int CSockghd::SendTo(const void * lpBuf, int nBufLen, UINT nHostPort, LPCSTR lpszHostAddress)
{
	sockaddr_in sa = { AF_INET, htons(nHostPort)};
	sa.sin_addr.S_un.S_addr = inet_addr(lpszHostAddress);
	int n = sendto(m_hSocket, (const char*)lpBuf, nBufLen, 0, (sockaddr*)&sa, sizeof(sa));
	if (n == SOCKET_ERROR)
		cout << "发送出错" << WSASetLastError << endl;
	return 0;
}

int CSockghd::ReceiveFrom(void * lpBuf, int nBufLen, char * rSocketAddress, UINT & rSocketPort, int nFlags)
{
	sockaddr_in sa = { AF_INET };
	int nLen = sizeof(sa);
	int nRet = recvfrom(m_hSocket, (char*)lpBuf, nBufLen, 0, (sockaddr*)&sa, &nLen);
	if (nRet > 0)
	{
		rSocketPort = htons(sa.sin_port);
		strcpy(rSocketAddress, inet_ntoa(sa.sin_addr));
	}
	return nRet;
}

CSockghd::CSockghd()
{
	WSADATA wd;
	WSAStartup(0x0202, &wd);
	m_hSocket = INVALID_SOCKET;
}


CSockghd::~CSockghd()
{
	Close();
}
