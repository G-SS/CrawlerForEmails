// parse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mymail.h"
#include "parse.h"
#include "boost\xpressive\xpressive.hpp"

// parse

parse::parse()
{
	cur_url="";
	cur_folder="";
	cur_point=0;
	file_to_parse="";
	length=0;
}

parse::~parse()
{

}
int parse::parse_email()//��ʼ��email���н���
{	
	if(length<=100)		return 0;//û���ļ�
	//һ��һ����email��ַ��,fuck
	using namespace boost::xpressive;
	string str_all(file_to_parse); //���ļ����з���
	
	cregex reg=cregex::compile("([0-9a-zA-Z_.]+@[0-9a-zA-Z.]+)",icase);
	cmatch what;
	
	int count=0;
	int size=2;
	long int pos=0;
	usesql sql;
	while(size!=0)
	{	
		string str(str_all.begin()+pos,str_all.end());
		regex_search(str.data(),what,reg); //����ƥ��Ľ��
		size=what.size();//�ҵ����ط���Ľ��
		if(size!=0)
		{
			//������
			string h(what[0]);
			//using namespace boost::xpressive;
			//ȥ��һЩ�����׵Ķ�����Ҳ���� @ ��һЩ�����÷�
			cregex reg=cregex::compile(".com|.cn|.net|.cc",icase);
			cmatch what;	
			regex_search(h.data(),what,reg); //����ƥ��Ľ��
			int size=what.size();//�ҵ����ط���Ľ��
			if(size==0)
			{
				pos=pos+str.find(h.data(),0)+h.length();
				if(pos<0) return count;	
				continue;
			}
			sql.insert_a_mail(h);
			//�����ַ���							
			pos=pos+str.find(h.data(),0)+h.length();
			if(pos<0) return count;			
		}			
	}	
}

void parse::parse_url()//��ʼ��url���н���
{
	if(length<=100)	return ;//û���ļ�
	string str_all(file_to_parse); //���ȫ���ı���һ������
	
	//FILE* to=fopen("1.txt","wb");
	long int next_a=2;  //a��ǩ��ʼ
	long int next_a_end=2; //a��ǩ����
	long int pos=0;
	usesql sql;
	
	while(next_a>=0)
	{	
		string str(file_to_parse.begin()+pos,file_to_parse.end()); //��Ҫ���ǵ���ʱ�ı�
		
		next_a=str.find("<a ",0);
		if(next_a<0) return ;//�Ҳ���a��ǩ��
		next_a_end=str.find(">",next_a); //�ӿ�ʼλ�ã�������a��ǩ�Ľ���λ��
		if(next_a_end<0) return ;//�Ҳ�������λ��
		string a_content(str.begin()+next_a,str.begin()+next_a_end+1);
		//a_content �����ݴ�����£�����Ҫ���href��ֵ
		//<a href='http://qzlx.xjtu.edu.cn/' title='Ⱥ��·�߽���' target="_blank">
		int first=a_content.find("href=",0);//����href��λ�� 		
		int end=a_content.find(" ",first);//����href֮����׸��ո�
		if(first<0 || end<0)
		{
			//�����쳣�����
			//����λ�ã�ֱ�ӽ�����һ������Ĵ���
			pos=pos+next_a_end+2;
			if(file_to_parse.begin()+pos > file_to_parse.end()) return;
			if(pos<0) return;
			continue;		
		}
		
		a_content=string(a_content.begin()+first+5,a_content.begin()+end);
		//�������.doc .rar .jpg ֮���pass��
		using namespace boost::xpressive;
		cregex reg=cregex::compile(".lofter|.share|.google.|.baidu.|search|so|javascript|.doc|.docx|.ppt|.pptx|.rar|.z|.jpg|.zip|.tar|.gz|.pdf|.css|.js",icase);
		cmatch what;	
		regex_search(a_content.data(),what,reg); //����ƥ��Ľ��
		int size=what.size();//�ҵ����ط���Ľ��
		if(size!=0 || a_content.length()<6 || a_content.length()>40)
		{
			pos=pos+next_a_end+2;
			if(file_to_parse.begin()+pos > file_to_parse.end()) return;
			if(pos<0) return;
			continue;
		}
		//a_content�����ݴ�������
		//'http://news.xjtu.edu.cn/info/1033/39172.htm'
		//���ڣ���Ҫɾ����ʼ��'����"
		if(a_content.data()[0]=='\'' || a_content.data()[0]=='\"')
		{
			a_content.erase(a_content.begin());
		}
		//���ڣ�ɾ����β��'����"
		if(a_content.at(a_content.length()-1)=='\'' || a_content.at(a_content.length()-1)=='\"')
		{
			a_content.erase(a_content.end()-1);
		}
		//ok,��ʽ�ϴ������,���ż�������Ե�ַ���Ǿ��Ե�ַ
		if(strcmp("http",(const char*)(string(a_content.begin(),a_content.begin()+4)).data()))		
		//if( a_content.find("http:",0)<0 && a_content.find("https:",0)<0 )
		{
			//�����õ���Ե�ַ
			//MessageBox(0,L"",L"",0);
			if(cur_folder.at(cur_folder.length()-1)=='/' && a_content.at(0)=='/') //�����ظ��Ķ���
			{
				a_content.erase(a_content.begin());			
			}
			a_content=cur_folder+a_content;//ƴ�ճ������ĵ�ַ
		}
		//string h(a_content);
		//fwrite((h+"\r\n").data(),h.length()+2,1,to);
		//ok,�����Ѿ�����Ĳ���ˣ��ٿ��������ַ�ǲ���������Ҫ��
		
		
		//string h(a_content);
		//fwrite((h+"\r\n").data(),h.length()+2,1,to);
		//��URL���뵽���ݿ���
		sql.insert_a_url(a_content);

		//�����ַ���
		pos=pos+next_a_end+2;
		if(file_to_parse.begin()+pos > file_to_parse.end()) return;
		if(pos<0) return;				
					
	}	


}

//����������������
void parse::make_clear()
{
	return;
	
	if(length==0)		return ;//û���ļ�
	//ȥ��nbsp
	CString s(file_to_parse.data());
	s.Replace(L"&nbsp;",L"");
	s.Replace(L"&nbsp",L"");
	file_to_parse=string((char*)s.GetString());
	string::iterator p=file_to_parse.begin();
	//ȥ���ո�
	while(p!=file_to_parse.end()) //ȥ����Ч�ַ�
	{
		if(*p == '\n' || *p == '\t' || *p == ' ') file_to_parse.erase(p);	
		p++;
	}
}






