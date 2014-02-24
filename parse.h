#pragma once



#include "stdio.h"

#include <string.h>
#include <string>
#include <iterator>
#include "sql.h"
#include <cstring>

using namespace std;
// parse
// ��string�����н������õ��µ����ӵ�ַ�Լ�ҳ���ڵ������ַ

class parse
{


public:
	parse();
	virtual ~parse();
	string cur_url; //��ǰҳ�����ַ������Ϊ����ʹ�����URL��ʹ�õ�
	string cur_folder;//��ǰҳ���Ŀ¼����������ʱ����Ҫʹ��replace�����ܴ��ڵ� // �滻��/
	long int cur_point; //��ǰ�������ļ���λ����
	long int length;  
	string file_to_parse;

	void set_file(string file)
	{
		try
		{
			file_to_parse=file;
			length=file_to_parse.length();
		}
		catch(CException* e)
		{
			file_to_parse=string("");
			length=0;
		}
	} //������Ҫ�������ļ�

	void set_url(string url)
	{
		try
		{
			cur_url=url;
			get_folder();
		}
		catch(CException* e)
		{
			cur_url=string("");
			cur_folder=string("");
		}
	}
	void get_folder()
	{
		cur_folder=cur_url;
		string::iterator p=cur_folder.end();
		try
		{
			while(*--p!='/')
			{
				cur_folder.erase(p);//ɾ����Ԫ��
			}
		}
		catch(CException* e)
		{
			cur_folder=string("");
		}
	}
	void reset_point(){cur_point=0;}
	int parse_email();//��ʼ��email���н���	
	void parse_url();//��ʼ��email���н���	
	void make_clear();//ɾ���ո��е�

};




