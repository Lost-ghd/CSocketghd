#pragma once
#include <winsock2.h>
class CSockghd
{
	protected:
	SOCKET m_hSocket;//核心成员变量
public:
	BOOL Create(UINT nSocketPort = 0, int nSocketType = SOCK_STREAM, LPCSTR lpszSocketAddress = NULL);

	int SendTo(const void* lpBuf, int nBufLen, UINT nHostPort, LPCSTR lpszHostAddress);

	int ReceiveFrom(void* lpBuf, int nBufLen, char *rSocketAddress, UINT& rSocketPort, int nFlags=0);

	int Receive(void* lpBuf, int nBufLen, int nFlags = 0)
	{
		return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
	}
	void Close()
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
	CSockghd();
	virtual ~CSockghd();
};

