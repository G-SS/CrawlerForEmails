// Download.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mymail.h"
#include "Download.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Download

Download::Download()
{
	
}

Download::~Download()
{
	GetSourceHtml();
}

void Download::SetUrl(const char * Url)
{
	try
	{
		if(strlen(Url)<6)
		{
			theUrl=CString("");
		}
	}
	catch(CException* e)
	{
		theUrl=CString("");
	}
	theUrl=CString(Url);
}

CString Download::Action()
{
	try
	{
		if(theUrl.GetLength()<6 || theUrl.GetLength()>45 ) 
			return CString("");
	}
	catch(CException* e)
	{
		return CString("");
	}

	return GetSourceHtml();	
}
CString Download::GetSourceHtml()
{
    //�������ҳ�ʼ��Internet�Ự
    CInternetSession session;
	//httpЭ����ƶ���
	CHttpConnection* pServer=NULL;
	try
	{
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5������ӳ�ʱ
		session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 1000);           // 1��ķ��ͳ�ʱ
		session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 7000);        // 7��Ľ��ճ�ʱ
		session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 1000);     // 1��ķ��ͳ�ʱ
		session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 7000);       // 7��Ľ��ճ�ʱ
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1������		
	}
	catch(CException* e)
	{
		return CString("");
	}

    //httpЭ���µ��ļ���������
    CHttpFile* pFile=NULL;

    //url��ַ
	CString m_adress;
	try
	{
		m_adress=theUrl; 
	}
	catch(CException* e)
	{
		return CString("");
	}

    CString strServer;
    CString strObject;
    INTERNET_PORT nPort;
    DWORD dwServiceType;

    //ͨ��url��ַ������url����Ķ˿�
	try{
    AfxParseURL(m_adress,dwServiceType,strServer,strObject,nPort);  //����ַ���н���
    pServer=session.GetHttpConnection(strServer,nPort);//��Ҫ����������һ��CHttpConnection�ľ��
    pFile=pServer->OpenRequest(1,strObject,NULL,1,NULL,NULL,INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_AUTO_REDIRECT);
	    	
    pFile->SendRequest();   //��һ�������͵�http������ITPUB���˿ռ�
	}
	catch(CException *e)
	{
		return CString("");
	}
    CString line("");
    CString strConnect("");

	try
	{
		while(pFile->ReadString(line))
		{   
			strConnect+=line;			
		}
	}
	catch(CException* e)
	{
		return CString("");
	}
	return strConnect;
}
