#pragma once


// Download

#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <afxinet.h>
#define MAXBLOCKSIZE 102400
#pragma comment( lib, "wininet.lib" )


class Download 
{
public:
	Download();
	virtual ~Download();
	void SetUrl(const char *); //������ַ
	CString Action();
	CString GetSourceHtml();	
	CString theUrl; //��󳤶�Ϊ256�ֽڵ���ַ	
};


