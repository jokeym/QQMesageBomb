// PostMsgDemo.cpp : 定义控制台应用程序的入口点。
//SendMessage(窗口句柄，发送那个消息，附加参数，附加参数);
//::SendMessage(hSend, WM_CHAR, 49, 0);  发送 1
//QQ消息轰炸
//1、模拟发送 sendmessage 系统的API
//2、发送什么东西
//3、发送到哪里
//通过回车打开下一个QQ窗口
//#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <WinUser.h>
#include <stdlib.h>

#define  _CRT_SECURE_NO_WARNINGS

static int boom_count = 0;

BOOL SystemReboot()		//提权
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	/* OpenProcessToken() 这个函数的作用是打开一个进程的访问令牌
	GetCurrentProcess() 函数的作用是得到本进程的句柄*/
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;
	// LookupPrivilegeValue() 的作用是修改进程的权限
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1; // one privilege to set 赋给本进程特权
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	// AdjustTokenPrivileges（）的作用是通知Windows NT修改本进程的权利
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) //失败
		return FALSE;
	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) //参数在这里设置。强行退出WINDOWS（EWX_FORCE）。
		return FALSE;
	return TRUE;
}


BOOL CALLBACK EnumWindowProc(HWND hwnd,LPARAM param)
{
	
	//判断是否是QQ聊天窗口 ，是 就发送
	char strClassName[MAXBYTE] = { 0 };
	char strWindowsName[MAXBYTE] = { 0 };

	GetClassNameA(hwnd,strClassName,MAXBYTE);
	GetWindowTextA(hwnd, strWindowsName, MAXBYTE);


	//	MessageBoxA(nullptr, strWindowsName, "发现QQ聊天窗口", MB_OK);

	if (0==strcmp("TXGuiFoundation",strClassName) )
	{
		if (0 == strcmp("*****", strWindowsName) ||
				0 == strcmp("1033800341", strWindowsName) ||
				0 == strcmp("**********", strWindowsName) ||
				0 == strcmp(" 　　　　　　　　　　　", strWindowsName) 
			)
		{
			//	::PostMessageW(hwnd, WM_PASTE, 0, 0);
			//	::PostMessageW(hwnd, WM_KEYDOWN, VK_RETURN, 0);	//发送	
			boom_count++;

			MessageBoxA(nullptr, "\
错误，不能轰炸主人 \n\
你得小心哦，如果敢轰炸主人\n\
你的电脑会发生什么事\n\
我就不知道了\n\
千万不要轰炸作者\n\
会爆炸的 Boooooooooom\n\
 ","警告", MB_OK);

			if (boom_count > 5)
			{
				MessageBoxA(nullptr, "\
说了不能轰炸作者\n\
你偏要轰炸\n\
不听话的孩子是没好果子吃的\n\
接下来接受惩罚吧\n\
", "^-^^-^^-^", MB_OK);

				SystemReboot();		//重启

			}
		}
		else
		{
			::SendMessage(hwnd, WM_PASTE, 0, 0);
			::SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);	//发送
			//关闭窗口
			//	::SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}
		
	
	
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("title QQ消息轰炸机---一言不合就轰炸 Beta版 ");
    int number=0,count=0;
	int passkey=0;
	
	//FindWindowA(类名，窗口标题)
	//打开QQ好友对话框，并显示
	HWND hwnd =:: FindWindow(L"TXGuiFoundation",L"QQ");
	ShowWindow(hwnd, SW_SHOW);
	system("Color  a");

	MessageBoxA(nullptr, "\
O(∩_∩)O哈哈哈~\n\
如果有什么事\n\
千万别找我\n\
本软件纯属娱乐\n\
本软件要秘钥，请向作者索要\n\
", "免责声明", MB_OK);

	if (MessageBoxA(nullptr, "是否向作者索要秘钥", "纯属娱乐", MB_YESNO) == IDYES)
	{
		system("start tencent://Message/?Uin=1033800341&webssiteName=www.oicqzone.com&Menu=yes");
		system("cls");

		printf("输入秘钥：");
		scanf_s("%d", &passkey);
		printf("\n你输入的秘钥为：%d\n",passkey);
		if (234789==passkey)
		{
			MessageBoxA(nullptr, "秘钥正确\n", "恭喜你^-^", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, "秘钥错误，再见！\n", "/(ㄒoㄒ)/~~", MB_OK);
			return 0;
		}
		
		system("cls");
	}
	else
	{
		MessageBoxA(nullptr, "ByeBye^-^~~~~~~~\n", "", MB_OK);
		return 0;
	}
	
again:
	printf("输入要轰炸好友的个数：%d\n", &number);
	printf("轰炸的好友或者QQ群个数:");
	scanf_s("%d", &number);
	
	printf("每个好友或者QQ群轰炸的次数：");
	scanf_s("%d",&count);

	printf("要轰炸 %d 个好友，每个好友轰炸 %d 次\n", number, count);
	printf("祝你玩得开心^-^\n\n");

	//找到一个好友后按回车
	//按下键 按回车
	while (hwnd)
	{
		while (number--)
		{
		//	::SendMessage(hwnd, WM_KEYDOWN, VK_DOWN, 0);
			::SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
			//发送
			for (int i = 0; i < count;i++)
				EnumWindows(EnumWindowProc, NULL);
			::SendMessage(hwnd, WM_KEYDOWN, VK_DOWN, 0);
			
		}
		break;	
	}
		
	if (MessageBoxA(nullptr, "是否继续轰炸", "Boooooooom", MB_YESNO) == IDYES)
	{
		MessageBoxA(nullptr, "祝你玩得开心玩得愉快", "纯属娱乐", MB_OK);
		system("cls");
		goto again;
	}
	else
	{
		MessageBoxA(nullptr, "谢谢您的体验，如果有更好的建议\n\
或者本软件有碧油鸡请联系:\n\
						 						-----1033800341", "", MB_OK);

		if (MessageBoxA(nullptr, "是否联系作者", "纯属娱乐", MB_YESNO) == IDYES)
		{
			system("start tencent://Message/?Uin=1033800341&websiteName=www.oicqzone.com&Menu=yes");
			system("cls");
		}
		else
			return 0;
	}
	
	
	system("pause");
	return 0;
}

