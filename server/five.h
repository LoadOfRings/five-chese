//#include<windows.h>
#include<conio.h>
#include<winsock2.h>
#include<stdio.h>
#include <Mmsystem.h> 
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "winmm.lib") 
#define SINGLE 1
#define DOUBLE 2
#define NETWORK 3
#define AI 4
#define EASY 1
#define MIDDLE 2
void single_player();
void double_player();
void network_player();
void ai_player();
void single_game();
void double_game();
void betwork_game();
void aie_game();
void choose_diffculty_loadin();
void choose_diffculty_easy();
void choose_diffculty_middle();
int sytle=0;
int diffculty=0;
//确定输赢
#define WHITE -1
#define BLACK 1
#define NULL 0
int black_win;
int white_win;//确定胜负变量，5黑胜，-5白胜
int xy[20+1][20+1]={0};//棋盘，1黑子，-1白子，0空
int check_right(int x_i,int y_i);
int check_right_down(int x_i,int y_i);
int check_down(int x_i,int y_i);
int check_left_down(int x_i,int y_i);
int check();
//五子棋AI
struct priority_array {
	int value;
	int priority;
	int priority_vertical;
	int priority_horizontal;
	int priority_left_slanting;
	int priority_right_slanting;
};
struct priority_array p_xy[20+1][20+1];
int black_number=0;
int white_number=0;
int times=0;
int return_number(int a,int b);
int check_priority_right(int x_i,int y_i);
int check_priority_right_down(int x_i,int y_i);
int check_priority_down(int x_i,int y_i);
int check_priority_left_down(int x_i,int y_i);
int check_priority_left(int x_i,int y_i);
int check_priority_left_up(int x_i,int y_i);
int check_priority_up(int x_i,int y_i);
int check_priority_right_up(int x_i,int y_i);
void check_priority();
void if_usable_vertical(int x_i,int y_i);
void if_usable_horizontal(int x_i,int y_i);
void if_usable_left_slanting(int x_i,int y_i);
void if_usable_right_slanting(int x_i,int y_i);
void check_usable();
void check_with_blank();
void check_with_blank_vertical(int x_i,int y_i);
void check_with_blank_horizontal(int x_i,int y_i);
void check_with_blank_left_slanting(int x_i,int y_i);
void check_with_blank_right_slanting(int x_i,int y_i);
//cheeseboard
void chessboard(int cur_x,int cur_y);
//begin_game
//void begin_game(int sytle);
void single_game();
void double_game();
void ai_game();
void single_glisten_have();
void single_glisten_no();
void double_glisten_have();
void double_glisten_no();
void network_glisten_have();
void network_glisten_no();
void ai_glisten_have();
void ai_glisten_no();
int choose_diffculty(int diffculty);
int chars_to_int(char buffer[],int len);
//小鳖的AI
int go(int qp[][21],int color);
#define white -1
#define black 1
#define blank 0
#define live 1
#define dead 0
//服务端
WSADATA wsaData;
SOCKET ServerSocket;
SOCKET NewSocket=-1;
SOCKADDR_IN ServerAddr;
SOCKADDR_IN ClientAddr;
void Set_ReceiveBuffer(int data,char buffer[]);
int ServerPort=4000;
char ReceiveBuffer[1024];
int Result;
int ReceiveLen;

int ClientAddrLen=sizeof(SOCKADDR);
int SendLength;





/*void main(){
	single_player();
}*/




//确定输赢
int check_right(int x_i,int y_i){
	if(5==black_win)
		return 1;
	if(-5==white_win)
		return -1;
	if(x_i<=20 && y_i<=20)
	{
		if(black_win>=0){
			if(xy[x_i][y_i]==1){//为黑
				black_win++;
				check_right(x_i,y_i+1);
			}
			else{//为白或空
				black_win=0;
			}
		}
		if(white_win<=0){
			if(xy[x_i][y_i]==-1){//为白
				white_win--;
				check_right(x_i,y_i+1);
			}
			else{//为黑或空
				white_win=0;
			}
		}
	}
	return 0;
}
int check_right_down(int x_i,int y_i){
	if(5==black_win)
		return 1;
	if(-5==white_win)
		return -1;
	if(x_i<=20 && y_i<=20)
	{
		if(black_win>=0){
			if(xy[x_i][y_i]==1){//为黑
				black_win++;
				check_right_down(x_i+1,y_i+1);
			}
			else{//为白或空
				black_win=0;
			}
		}
		if(white_win<=0){
			if(xy[x_i][y_i]==-1){//为白
				white_win--;
				check_right_down(x_i+1,y_i+1);
			}
			else{//为黑或空
				white_win=0;
			}
		}
	}
	return 0;
}
int check_down(int x_i,int y_i){
	if(5==black_win)
		return 1;
	if(-5==white_win)
		return -1;
	if(x_i<=20 && y_i<=20)
	{
		if(black_win>=0){
			if(xy[x_i][y_i]==1){//为黑
				black_win++;
				check_down(x_i+1,y_i);
			}
			else{//为白或空
				black_win=0;
			}
		}
		if(white_win<=0){
			if(xy[x_i][y_i]==-1){//为白
				white_win--;
				check_down(x_i+1,y_i);
			}
			else{//为黑或空
				white_win=0;
			}
		}
	}
	return 0;
}
int check_left_down(int x_i,int y_i){
	if(5==black_win)
		return 1;
	if(-5==white_win)
		return -1;
	if(x_i<=20 && y_i>=0)
	{
		if(black_win>=0){
			if(xy[x_i][y_i]==1){//为黑
				black_win++;
				check_left_down(x_i+1,y_i-1);
			}
			else{//为白或空
				black_win=0;
			}
		}
		if(white_win<=0){
			if(xy[x_i][y_i]==-1){//为白
				white_win--;
				check_left_down(x_i+1,y_i-1);
			}
			else{//为黑或空
				white_win=0;
			}
		}
	}
	return 0;
}
int check(){
	int flag=0;
	black_win=0;
	white_win=0;
	for(int i=0;i<=20;i++){
		for(int j=0;j<=20;j++){
			flag=check_right(i,j);//返回1黑胜，返回-1白胜
			if(0!=flag){
				return flag;//
			}
		}
	}
	black_win=0;
	white_win=0;
	for(int i=0;i<=20;i++){
		for(int j=0;j<=20;j++){
			flag=check_right_down(i,j);
			if(0!=flag){
				return flag;
			}
		}
	}
	black_win=0;
	white_win=0;
	for(int i=0;i<=20;i++){
		for(int j=0;j<=20;j++){
			flag=check_down(i,j);
			if(0!=flag){
				return flag;
			}
		}
	}
	black_win=0;
	white_win=0;
	for(int i=0;i<=20;i++){
		for(int j=20;j>=0;j--){
			flag=check_left_down(i,j);
			if(0!=flag){
				return flag;
			}
		}
	}
	return 0;
}
//五子棋AI
int computer_input(int c_xy[][20+1]){
	int i,j;
	int biggest_i=0;
	int biggest_j=0;
	int biggest_priority;
	for(i=0;i<=20;i++)//初始化带优先级的数组
		for(j=0;j<=20;j++){
			p_xy[i][j].value=c_xy[i][j];
			p_xy[i][j].priority=0;
			p_xy[i][j].priority_vertical=0;
			p_xy[i][j].priority_horizontal=0;
			p_xy[i][j].priority_left_slanting=0;
			p_xy[i][j].priority_right_slanting=0;
		}
	check_with_blank();
	check_priority();
	check_usable();
	biggest_priority=0;
	for(i=0;i<=20;i++)//综合优先级
		for(j=0;j<=20;j++){
			p_xy[i][j].priority=p_xy[i][j].priority_vertical+
								p_xy[i][j].priority_horizontal+	
								p_xy[i][j].priority_left_slanting+
								p_xy[i][j].priority_right_slanting;
		}
	for(i=0;i<=20;i++){
		for(j=0;j<=20;j++){
			if(0==p_xy[i][j].value){
				if(p_xy[i][j].priority>biggest_priority){
					biggest_i=i;
					biggest_j=j;
					biggest_priority=p_xy[i][j].priority;
				}
			}
		}
	}
	int m=biggest_i*100+biggest_j;
	return m;
}
void check_priority(){
	black_number=0;
	white_number=0;
	int i,j,flag;
	//right
	for(i=0;i<=20;i++){
		for(j=0;j<=20;j++){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_right(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
						
						
						case 1:p_xy[i][j].priority_horizontal+=2;break;
						case -1:p_xy[i][j].priority_horizontal+=1;break;
						case 2:p_xy[i][j].priority_horizontal+=57;break;
						case -2:p_xy[i][j].priority_horizontal+=10;break;
						case 3:p_xy[i][j].priority_horizontal+=955;break;
						case -3:p_xy[i][j].priority_horizontal+=244;break;
						case -4:p_xy[i][j].priority_horizontal+=3996;break;
						case 4:p_xy[i][j].priority_horizontal+=16000;break;
						
						default:break;
					}
				}
			}
			else{
				p_xy[i][j].priority_horizontal=0;
			}
		}
	}
	black_number=0;
	white_number=0;
	//right_down
	for(i=0;i<=20;i++){
		for(j=0;j<=20;j++){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_right_down(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
												
						
						case 1:p_xy[i][j].priority_left_slanting+=2;break;
						case -1:p_xy[i][j].priority_left_slanting+=1;break;
						case 2:p_xy[i][j].priority_left_slanting+=57;break;
						case -2:p_xy[i][j].priority_left_slanting+=10;break;
						case 3:p_xy[i][j].priority_left_slanting+=955;break;
						case -3:p_xy[i][j].priority_left_slanting+=244;break;
						case -4:p_xy[i][j].priority_left_slanting+=3996;break;
						case 4:p_xy[i][j].priority_left_slanting+=16000;break;
						
						default:break;
					}
				}
			}
		}
	}
	black_number=0;
	white_number=0;
	//down
	for(i=0;i<=20;i++){
		for(j=0;j<=20;j++){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_down(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
												
						
						case 1:p_xy[i][j].priority_vertical+=2;break;
						case -1:p_xy[i][j].priority_vertical+=1;break;
						case 2:p_xy[i][j].priority_vertical+=57;break;
						case -2:p_xy[i][j].priority_vertical+=10;break;
						case 3:p_xy[i][j].priority_vertical+=955;break;
						case -3:p_xy[i][j].priority_vertical+=244;break;
						case -4:p_xy[i][j].priority_vertical+=3996;break;
						case 4:p_xy[i][j].priority_vertical+=16000;break;
					
						default:break;
					}
				}
			}
		}
	}
	black_number=0;
	white_number=0;
	//left_down
	for(i=0;i<=20;i++){
		for(j=20;j>=0;j--){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_left_down(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
												
						
						case 1:p_xy[i][j].priority_right_slanting+=2;break;
						case -1:p_xy[i][j].priority_right_slanting+=1;break;
						case 2:p_xy[i][j].priority_right_slanting+=57;break;
						case -2:p_xy[i][j].priority_right_slanting+=10;break;
						case 3:p_xy[i][j].priority_right_slanting+=955;break;
						case -3:p_xy[i][j].priority_right_slanting+=244;break;
						case -4:p_xy[i][j].priority_right_slanting+=3996;break;
						case 4:p_xy[i][j].priority_right_slanting+=16000;break;
						
						default:break;
					}
				}
			}
		}
	}
	black_number=0;
	white_number=0;
	//left
	for(i=0;i<=20;i++){
		for(j=20;j>=0;j--){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_left(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
												
						
						case 1:p_xy[i][j].priority_horizontal+=2;break;
						case -1:p_xy[i][j].priority_horizontal+=1;break;
						case 2:p_xy[i][j].priority_horizontal+=57;break;
						case -2:p_xy[i][j].priority_horizontal+=10;break;
						case 3:p_xy[i][j].priority_horizontal+=955;break;
						case -3:p_xy[i][j].priority_horizontal+=244;break;
						case -4:p_xy[i][j].priority_horizontal+=3996;break;
						case 4:p_xy[i][j].priority_horizontal+=16000;break;
						
						default:break;
					}
				}
			}
		}
	}
	//up
	black_number=0;
	white_number=0;
	for(i=20;i>=0;i--){
		for(j=0;j<=20;j++){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_up(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
												
						
						case 1:p_xy[i][j].priority_vertical+=2;break;
						case -1:p_xy[i][j].priority_vertical+=1;break;
						case 2:p_xy[i][j].priority_vertical+=57;break;
						case -2:p_xy[i][j].priority_vertical+=10;break;
						case 3:p_xy[i][j].priority_vertical+=955;break;
						case -3:p_xy[i][j].priority_vertical+=244;break;
						case -4:p_xy[i][j].priority_vertical+=3996;break;
						case 4:p_xy[i][j].priority_vertical+=16000;break;
						
						default:break;
					}
				}
			}
		}
	}
	//right_up
	black_number=0;
	white_number=0;
	for(i=20;i>=0;i--){
		for(j=20;j>=0;j--){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_right_up(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
											
						
						case 1:p_xy[i][j].priority_right_slanting+=2;break;
						case -1:p_xy[i][j].priority_right_slanting+=1;break;
						case 2:p_xy[i][j].priority_right_slanting+=57;break;
						case -2:p_xy[i][j].priority_right_slanting+=10;break;
						case 3:p_xy[i][j].priority_right_slanting+=955;break;
						case -3:p_xy[i][j].priority_right_slanting+=244;break;
						case -4:p_xy[i][j].priority_right_slanting+=3996;break;
						case 4:p_xy[i][j].priority_right_slanting+=16000;break;
					
						default:break;
					}
				}
			}
		}
	}
	black_number=0;
	white_number=0;
	//left_up
	for(i=20;i>=0;i--){
		for(j=0;j<=20;j++){
			if(xy[i][j]==0){
				black_number=0;
				white_number=0;
				flag=check_priority_left_up(i,j);
				if(flag!=0){
					switch(flag){
						/*
						case -4:p_xy[i][j].priority+=10000;break;
						case 4:p_xy[i][j].priority+=500;break;
						case 1:p_xy[i][j].priority+=1;break;
						case -1:p_xy[i][j].priority+=2;break;
						case 2:p_xy[i][j].priority+=20;break;
						case -2:p_xy[i][j].priority+=10;break;
						case 3:p_xy[i][j].priority+=40;break;
						case -3:p_xy[i][j].priority+=100;break;
						*/
													
						
						case 1:p_xy[i][j].priority_left_slanting+=2;break;
						case -1:p_xy[i][j].priority_left_slanting+=1;break;
						case 2:p_xy[i][j].priority_left_slanting+=57;break;
						case -2:p_xy[i][j].priority_left_slanting+=10;break;
						case 3:p_xy[i][j].priority_left_slanting+=955;break;
						case -3:p_xy[i][j].priority_left_slanting+=244;break;
						case -4:p_xy[i][j].priority_left_slanting+=3996;break;
						case 4:p_xy[i][j].priority_left_slanting+=16000;break;
						
						default:break;
					}
				}
			}
		}
	}
}

int check_priority_right(int x_i,int y_i){
	if(x_i<=20 && y_i<=20)
	{
		if(black_number>=0){
			if(xy[x_i][y_i+1]==1){//为黑
				black_number++;
				y_i++;
				white_number=1;
				check_priority_right(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_horizontal=p_xy[x_i][y_i].priority_horizontal/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i][y_i+1]==-1){//为白
				white_number--;
				y_i++;
				black_number=-1;
				check_priority_right(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_horizontal=p_xy[x_i][y_i].priority_horizontal/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_right_down(int x_i,int y_i){
	if(x_i<=20 && y_i<=20)
	{
		if(black_number>=0){
			if(xy[x_i+1][y_i+1]==1){//为黑
				black_number++;
				x_i++;
				y_i++;
				white_number=1;
				check_priority_right_down(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_left_slanting=p_xy[x_i][y_i].priority_left_slanting/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i+1][y_i+1]==-1){//为白
				white_number--;
				x_i++;
				y_i++;
				black_number=-1;
				check_priority_right_down(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_left_slanting=p_xy[x_i][y_i].priority_left_slanting/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_down(int x_i,int y_i){
	if(x_i<=20 && y_i<=20)
	{
		if(black_number>=0){
			if(xy[x_i+1][y_i]==1){//为黑
				black_number++;
				x_i++;
				white_number=1;
				check_priority_down(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_vertical=p_xy[x_i][y_i].priority_vertical/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i+1][y_i]==-1){//为白
				white_number--;
				x_i++;
				black_number=-1;
				check_priority_down(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_vertical=p_xy[x_i][y_i].priority_vertical/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_left_down(int x_i,int y_i){
	if(x_i<=20 && y_i>=0)
	{
		if(black_number>=0){
			if(xy[x_i+1][y_i-1]==1){//为黑
				black_number++;
				x_i++;
				y_i--;
				white_number=1;
				check_priority_left_down(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_right_slanting=p_xy[x_i][y_i].priority_right_slanting/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i+1][y_i-1]==-1){//为白
				white_number--;
				x_i++;
				y_i--;
				black_number=-1;
				check_priority_left_down(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_right_slanting=p_xy[x_i][y_i].priority_right_slanting/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_left(int x_i,int y_i){
	if(x_i<=20 && y_i>=0)
	{
		if(black_number>=0){
			if(xy[x_i][y_i-1]==1){//为黑
				black_number++;
				y_i--;
				white_number=1;
				check_priority_left(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_horizontal=p_xy[x_i][y_i].priority_horizontal/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i][y_i-1]==-1){//为白
				white_number--;
				y_i--;
				black_number=-1;
				check_priority_left(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_horizontal=p_xy[x_i][y_i].priority_horizontal/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_left_up(int x_i,int y_i){
	if(x_i>=0 && y_i>=0)
	{
		if(black_number>=0){
			if(xy[x_i-1][y_i-1]==1){//为黑
				black_number++;
				white_number=1;
				x_i--;
				y_i--;
				check_priority_left_up(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_left_slanting=p_xy[x_i][y_i].priority_left_slanting/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i-1][y_i-1]==-1){//为白
				white_number--;
				black_number=-1;
				x_i--;
				y_i--;
				check_priority_left_up(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_left_slanting=p_xy[x_i][y_i].priority_left_slanting/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_up(int x_i,int y_i){
	if(x_i>=0 && y_i<=20)
	{
		if(black_number>=0){
			if(xy[x_i-1][y_i]==1){//为黑
				black_number++;
				x_i--;
				white_number=1;
				check_priority_up(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_vertical=p_xy[x_i][y_i].priority_vertical/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i-1][y_i]==-1){//为白
				white_number--;
				x_i--;
				black_number=-1;
				check_priority_up(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_vertical=p_xy[x_i][y_i].priority_vertical/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}
int check_priority_right_up(int x_i,int y_i){
	if(x_i>=0 && y_i<=20)
	{
		if(black_number>=0){
			if(xy[x_i-1][y_i+1]==1){//为黑
				black_number++;
				x_i--;
				y_i++;
				white_number=1;
				check_priority_right_up(x_i,y_i);
			}
			else if(black_number!=0){//为白或空
				if(xy[x_i][y_i]==WHITE)
					p_xy[x_i][y_i].priority_right_slanting=p_xy[x_i][y_i].priority_right_slanting/2;
				return return_number(black_number,white_number);
			}
		}
		if(white_number<=0){
			if(xy[x_i-1][y_i+1]==-1){//为白
				white_number--;
				x_i--;
				y_i++;
				black_number=-1;
				check_priority_right_up(x_i,y_i);
			}
			else{//为黑或空
				if(xy[x_i][y_i]==BLACK)
					p_xy[x_i][y_i].priority_right_slanting=p_xy[x_i][y_i].priority_right_slanting/2;
				return return_number(black_number,white_number);
			}
		}
	}
	return return_number(black_number,white_number);
}

void check_usable(){
	int i,j;
	for(i=0;i<=20;i++)
		for(j=0;j<20;j++){
			if(xy[i][j]==WHITE){
				if_usable_vertical(i,j);
				if_usable_horizontal(i,j);
				if_usable_left_slanting(i,j);
				if_usable_right_slanting(i,j);
			}
		}
}
void if_usable_vertical(int x_i,int y_i){
	int t=0,p=0;
	int temp_condition[5]={0};
	if(y_i>16){
		for(t=0;t<5;t++){
			if(y_i>20)
				break;
			p_xy[x_i][++y_i].priority_vertical=0;
		}
		return;
	}
	if(xy[x_i][y_i]==WHITE){
		for(t=0;t<5;t++){
			if(xy[x_i][++y_i]!=WHITE){
				temp_condition[t]=x_i*100+y_i;
				if(y_i>20) 
					return;
			}	
			else
				break;
		}
		if(t<5){
				for(p=0;p<t;p++){
					p_xy[temp_condition[p]/100][temp_condition[p]%100].priority_vertical=0;
				}
			}	
	}	
}
void if_usable_horizontal(int x_i,int y_i){
	int t=0,p=0;
	int temp_condition[5]={0};
	if(x_i>16){
		for(t=0;t<5;t++){
			if(x_i>20)
				break;
			p_xy[++x_i][y_i].priority_horizontal=0;
		}
		return;
	}
	if(xy[x_i][y_i]==WHITE){
		for(t=0;t<5;t++){
			if(xy[++x_i][y_i]!=WHITE){
				temp_condition[t]=x_i*100+y_i;
				if(y_i>20) 
					return;
			}
			else
				break;
		}
		if(t<5){
				for(p=0;p<t;p++){
					p_xy[temp_condition[p]/100][temp_condition[p]%100].priority_horizontal=0;
				}
			}	
	}	
}
void if_usable_left_slanting(int x_i,int y_i){
	int t=0,p=0;
	int temp_condition[5]={0};
	if(y_i>16 || x_i>16){
		for(t=0;t<5;t++){
			if(x_i>20 ||y_i>20)
				break;
			p_xy[++x_i][++y_i].priority_left_slanting=0;
		}
		return;
	}
	if(xy[x_i][y_i]==WHITE){
		for(t=0;t<5;t++){
			if(xy[++x_i][++y_i]!=WHITE){
				temp_condition[t]=x_i*100+y_i;
				if(y_i>20) 
					return;
			}
			else
				break;
		}
		if(t<5){
				for(p=0;p<t;p++){
					p_xy[temp_condition[p]/100][temp_condition[p]%100].priority_left_slanting=0;
				}
			}	
	}	
}
void if_usable_right_slanting(int x_i,int y_i){
	int t=0,p=0;
	int temp_condition[5]={0};
	if(y_i>16 ||x_i<5){
		for(t=0;t<5;t++){
			if(y_i>20 ||x_i<1)
				break;
			p_xy[--x_i][++y_i].priority_right_slanting=0;
		}
		return;
	}
	if(xy[x_i][y_i]==WHITE){
		for(t=0;t<5;t++){
			if(xy[--x_i][++y_i]!=WHITE){
				temp_condition[t]=x_i*100+y_i;
				if(y_i>20) 
					return;
			}
			else
				break;
		}
		if(t<5){
				for(p=0;p<t;p++){
					p_xy[temp_condition[p]/100][temp_condition[p]%100].priority_right_slanting=0;
				}
			}	
	}	
}
void check_with_blank(){
	int i,j;
	for(i=0;i<=20;i++)
		for(j=0;j<=20;j++){
			if(xy[i][j]!=NULL){
				check_with_blank_vertical(i,j);
				check_with_blank_horizontal(i,i);
				check_with_blank_left_slanting(i,j);
				check_with_blank_right_slanting(i,j);
			}
		}
}
void check_with_blank_vertical(int x_i,int y_i){
	int lastcheese_blank=0;
	int cheese_number=0;
	int blank_number=0;
	int i=0,j=0;
	int temp_condition[3]={0};
	if(xy[x_i][y_i]==BLACK){
		for(i=0;i<7;i++){
			if(xy[x_i][y_i]==BLACK){
				lastcheese_blank=0;
				cheese_number++;
				x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=x_i;
				blank_number++;
				j++;
				x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			x_i++;
		}
		switch(cheese_number){
			case 2:p_xy[temp_condition[0]][y_i].priority_vertical+=57+1;
				if(blank_number==2)p_xy[temp_condition[1]][y_i].priority_vertical+=57+1;break;
			case 3:p_xy[temp_condition[0]][y_i].priority_vertical+=995+1;
				if(blank_number==2)p_xy[temp_condition[1]][y_i].priority_vertical+=995+1;break;
			case 4:p_xy[temp_condition[0]][y_i].priority_vertical+=16000+1;break;
		}
		if(xy[x_i][y_i]==WHITE || xy[x_i-i][y_i]==WHITE){
			p_xy[temp_condition[0]][y_i].priority_vertical=p_xy[temp_condition[0]][y_i].priority_vertical/2;
			p_xy[temp_condition[1]][y_i].priority_vertical=p_xy[temp_condition[1]][y_i].priority_vertical/2;
		}
	}
	else if(xy[x_i][y_i]==WHITE){
		cheese_number=0;
		for(i=0;i>-7;i--){
			if(xy[x_i][y_i]==WHITE){
				lastcheese_blank=0;
				cheese_number--;
				x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=x_i;
				blank_number++;
				j++;
				x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			x_i++;
		}
		switch(cheese_number){
			case -2:p_xy[temp_condition[0]][y_i].priority_vertical+=10+1;
				if(blank_number==2)p_xy[temp_condition[1]][y_i].priority_vertical+=10+1;break;
			case -3:p_xy[temp_condition[0]][y_i].priority_vertical+=244+1;
				if(blank_number==2)p_xy[temp_condition[1]][y_i].priority_vertical+=244+1;break;
			case -4:p_xy[temp_condition[0]][y_i].priority_vertical+=3996+1;break;
		}
		if(xy[x_i][y_i]==BLACK || xy[x_i+i][y_i]==BLACK){
			p_xy[temp_condition[0]][y_i].priority_vertical=p_xy[temp_condition[0]][y_i].priority_vertical/2;
			p_xy[temp_condition[1]][y_i].priority_vertical=p_xy[temp_condition[1]][y_i].priority_vertical/2;
		}
	}
}
void check_with_blank_horizontal(int x_i,int y_i){
	int lastcheese_blank=0;
	int cheese_number=0;
	int i=0,j=0;
	int blank_number=0;
	int temp_condition[3]={0};
	if(xy[x_i][y_i]==BLACK){
		for(i=0;i<7;i++){
			if(xy[x_i][y_i]==BLACK){
				lastcheese_blank=0;
				cheese_number++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i;
				blank_number++;
				j++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			y_i++;
		}
		switch(cheese_number){
			case 2:p_xy[x_i][temp_condition[0]].priority_horizontal+=57+1;
				if(blank_number==2)p_xy[x_i][temp_condition[1]].priority_horizontal+=57+1;break;
			case 3:p_xy[x_i][temp_condition[0]].priority_horizontal+=995+1;
				if(blank_number==2)p_xy[x_i][temp_condition[1]].priority_horizontal+=995+1;break;
			case 4:p_xy[x_i][temp_condition[0]].priority_horizontal+=16000+1;break;
		}
		if(xy[x_i][y_i]==WHITE || xy[x_i-i][y_i]==WHITE){
			p_xy[temp_condition[0]][y_i].priority_horizontal=p_xy[temp_condition[0]][y_i].priority_horizontal/2;
			p_xy[temp_condition[1]][y_i].priority_horizontal=p_xy[temp_condition[1]][y_i].priority_horizontal/2;
		}
	}
	else if(xy[x_i][y_i]==WHITE){
		cheese_number=0;
		for(i=0;i>-7;i--){
			if(xy[x_i][y_i]==WHITE){
				lastcheese_blank=0;
				cheese_number--;
				y_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i;
				blank_number++;
				j++;
				y_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			
		}
		switch(cheese_number){
			case -2:p_xy[x_i][temp_condition[0]].priority_horizontal+=10+1;
				if(blank_number==2)p_xy[x_i][temp_condition[1]].priority_horizontal+=10+1;break;
			case -3:p_xy[x_i][temp_condition[0]].priority_horizontal+=244+1;
				if(blank_number==2)p_xy[x_i][temp_condition[1]].priority_horizontal+=244+1;break;
			case -4:p_xy[x_i][temp_condition[0]].priority_horizontal+=3996+1;break;
		}
		if(xy[x_i][y_i]==BLACK || xy[x_i+i][y_i]==BLACK){
			p_xy[temp_condition[0]][y_i].priority_horizontal=p_xy[temp_condition[0]][y_i].priority_horizontal/2;
			p_xy[temp_condition[1]][y_i].priority_horizontal=p_xy[temp_condition[1]][y_i].priority_horizontal/2;
		}
	}
}
void check_with_blank_left_slanting(int x_i,int y_i){
	int lastcheese_blank=0;
	int cheese_number=0;
	int i=0,j=0;
	int blank_number=0;
	int temp_condition[3]={0};
	if(xy[x_i][y_i]==BLACK){
		for(i=0;i<7;i++){
			if(xy[x_i][y_i]==BLACK){
				lastcheese_blank=0;
				cheese_number++;
				y_i++;x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i*100+x_i;
				blank_number++;
				j++;
				y_i++;x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			y_i++;x_i++;
			
		}
		switch(cheese_number){
			case 2:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting+=57+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_left_slanting+=57+1;break;
			case 3:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting+=995+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_left_slanting+=995+1;break;
			case 4:p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting+=16000+1;break;
		}
		if(xy[x_i][y_i]==WHITE || xy[x_i-i][y_i]==WHITE){
			p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting=p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting/2;
			p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting=p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting/2;
		}
	}
	
	else if(xy[x_i][y_i]==WHITE){
		cheese_number=0;
		for(i=0;i>-7;i--){
			if(xy[x_i][y_i]==WHITE){
				lastcheese_blank=0;
				cheese_number--;
				y_i++;x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i*100+x_i;
				blank_number++;
				j++;
				y_i++;x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i>=20) break;
			x_i++;y_i++;
		}
		switch(cheese_number){
			case -2:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting+=10+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_left_slanting+=10+1;break;
			case -3:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting+=39+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_left_slanting+=39+1;break;
			case -4:p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting+=500+1;break;
		}
		if(xy[x_i][y_i]==BLACK || xy[x_i+i][y_i]==BLACK){
			p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting=p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_left_slanting/2;
			p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting=p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_left_slanting/2;
		}
	}
}
void check_with_blank_right_slanting(int x_i,int y_i){
	int lastcheese_blank=0;
	int cheese_number=0;
	int i=0,j=0;
	int blank_number=0;
	int temp_condition[3]={0};
	if(xy[x_i][y_i]==BLACK){
		for(i=0;i<7;i++){
			if(xy[x_i][y_i]==BLACK){
				lastcheese_blank=0;
				cheese_number++;
				y_i--;x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i*100+x_i;
				blank_number++;
				j++;
				y_i--;x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i<=0) break;
			y_i--;x_i++;
			
		}
		switch(cheese_number){
			case 2:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting+=57+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_right_slanting+=57+1;break;
			case 3:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting+=995+1;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_right_slanting+=995+1;break;
			case 4:p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting+=16000+1;break;
		}
		if(xy[x_i][y_i]==WHITE || xy[x_i-i][y_i]==WHITE){
			p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting=p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting/2;
			p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting=p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting/2;
		}
	}
	else if(xy[x_i][y_i]==WHITE){
		cheese_number=0;
		for(i=0;i>-7;i--){
			if(xy[x_i][y_i]==WHITE){
				lastcheese_blank=0;
				cheese_number--;
				y_i--;x_i++;
				continue;
			}
			else if(lastcheese_blank==0 && xy[x_i][y_i]==NULL){
				lastcheese_blank=1;
				temp_condition[j]=y_i*100+x_i;
				blank_number++;
				j++;
				y_i--;x_i++;
				continue;
			}
			else{
				break;
			}
			if(x_i>=20 || y_i<=0) break;
			x_i++;y_i--;
		}
		switch(cheese_number){
			case -2:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting+=10;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_right_slanting+=10;break;
			case -3:p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting+=244;
				if(blank_number==2)p_xy[temp_condition[1]%100][temp_condition[1]/100].priority_right_slanting+=244;break;
			case -4:p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting+=3996;break;
		}
		if(xy[x_i][y_i]==BLACK || xy[x_i+i][y_i]==BLACK){
			p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting=p_xy[temp_condition[0]%100][temp_condition[0]/100].priority_right_slanting/2;
			p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting=p_xy[temp_condition[1]%100][temp_condition[0]/100].priority_right_slanting/2;
		}
	}
}
int return_number(int a,int b){
	if(a>=0-b)
		return a;
	else
		return b;
}
//cheeseboard
void chessboard(int cur_x,int cur_y){
	system("cls");
	int x_i;
	int y_i;
	printf("\t\t  ");
	for(int i=0;i<=20;i++){
		printf("%2d",i);
	}
	printf("\n");
	for(x_i=0;x_i<=20;x_i++){
		for(y_i=0;y_i<=20;y_i++){
			if(0==x_i){
				if(0==y_i){
					printf("\t\t%2d",x_i);
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┏");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
				else if(20==y_i){
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┓");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
					printf("\n");
				}
				else{
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┳");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
			}
			else if(20==x_i){
				if(0==y_i){
					printf("\t\t%2d",x_i);
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┗");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
				else if(20==y_i){
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┛");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
					printf("\n");
				}
				else{
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┻");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
			}
			else{
				if(0==y_i){
					printf("\t\t%2d",x_i);
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┣");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
				else if(20==y_i){
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("┫");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
					printf("\n");
				}
				else{
					if(0==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("╋");
					}
					else if(1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("○");
					}
					else if(-1==xy[x_i][y_i]){
						if(x_i==cur_x && y_i==cur_y)
							printf("╬");
						else
							printf("●");
					}
				}
			}
		}
	}
}
//begin_game
void single_game(){
	int cursor[2]={10,10};//光标位置,初始值(10,10)
	int order=0;
	int flag=0;
	int turn=0;
	int sum=0;
	char c;
	chessboard(cursor[0],cursor[1]);
	PlaySoundA("res\\gamewin.wav",NULL,SND_FILENAME|SND_ASYNC);
	while(true){
		system("cls");
		//printf("\t\t  ");
		chessboard(cursor[0],cursor[1]);
		if(order%2==0){
			//turn=COMPUTER;
			while(true){
				if(order==0){
					xy[10][10]=1;
					order++;
					break;
				}
				else{
					//int sum=computer_input(xy);
					int sum=choose_diffculty(diffculty);
					xy[sum/100][sum%100]=1;
					order++;
					PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
					break;
				}
			}
		}
		else{
			while(true){
				printf("白棋走：\n");
				c=getch();
				if(c==-32)
					c=getch();
				switch(c){
					case 'H':system("cls");cursor[0]--;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 'P':system("cls");cursor[0]++;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 'M':system("cls");cursor[1]++;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 'K':system("cls");cursor[1]--;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case ' ':system("cls");
							if(xy[cursor[0]][cursor[1]]!=0){
									PlaySoundA("res\\Windows.wav",NULL,SND_FILENAME|SND_ASYNC);
									chessboard(cursor[0],cursor[1]);
									}
							  else{
								  xy[cursor[0]][cursor[1]]=-1;
								  chessboard(cursor[0],cursor[1]);
								  order++;
							  }break;
					default:break;
				}
				if(xy[cursor[0]][cursor[1]]==-1 && c==' '){
					
					break;
				}
			}
		}
		flag=check();
		if(flag==1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("black win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			system("cls");
			break;
		}
		if(flag==-1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("white win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			system("cls");
			break;			
		}
	}

}
void double_game(){
	int cursor[2]={10,10};//光标位置,初始值(10,10)
	int order=0;
	int flag=0;
	int turn=0;
	char c;
	chessboard(cursor[0],cursor[1]);
	PlaySoundA("res\\gamewin.wav",NULL,SND_FILENAME|SND_ASYNC);
	while(true){
		system("cls");
		chessboard(cursor[0],cursor[1]);
		if(order%2==0){
			while(true){
				printf("黑棋走：\n");
				switch(c=getch()){
					case 'w':system("cls");cursor[0]--;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 's':system("cls");cursor[0]++;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 'd':system("cls");cursor[1]++;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case 'a':system("cls");cursor[1]--;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case ' ':system("cls");
							if(xy[cursor[0]][cursor[1]]!=0){
									PlaySoundA("res\\Windows.wav",NULL,SND_FILENAME|SND_ASYNC);
									chessboard(cursor[0],cursor[1]);
									}
							  else{
								  xy[cursor[0]][cursor[1]]=1;
								  chessboard(cursor[0],cursor[1]);
								  order++;
								  PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
							  }break;
					default:break;
				}
				if(xy[cursor[0]][cursor[1]]==1 && c==' '){
					break;
				}
			}
		}
		else{
			while(true){
				printf("白棋走：\n");
				switch(c=getch()){
					case '8':system("cls");cursor[0]--;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case '2':system("cls");cursor[0]++;if(cursor[0]==-1)cursor[0]=21;
										 if(cursor[0]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case '6':system("cls");cursor[1]++;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case '4':system("cls");cursor[1]--;if(cursor[1]==-1)cursor[0]=21;
										 if(cursor[1]==22)cursor[0]=0;
										 
										 chessboard(cursor[0],cursor[1]);
										 break;
					case '5':system("cls");
							if(xy[cursor[0]][cursor[1]]!=0){
									PlaySoundA("res\\Windows.wav",NULL,SND_FILENAME|SND_ASYNC);
									chessboard(cursor[0],cursor[1]);
									}
							  else{
								  xy[cursor[0]][cursor[1]]=-1;
								  chessboard(cursor[0],cursor[1]);
								  order++;
								  PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
							  }break;
					default:break;
				}
				if(xy[cursor[0]][cursor[1]]==-1 && c=='5'){				
					break;
				}
			}
		}
		flag=check();
		if(flag==1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("black win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			system("cls");
			break;
		}
		if(flag==-1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("white win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			system("cls");
			break;			
		}
	}

}
void network_game(){
	int cursor[2]={10,10};//光标位置,初始值(10,10)
	int order=0;
	int flag=0;
	int turn=0;
	int sum=0;
	char c;
	chessboard(cursor[0],cursor[1]);
	PlaySoundA("res\\gamewin.wav",NULL,SND_FILENAME|SND_ASYNC);

	if((Result=WSAStartup(MAKEWORD(2,2),&wsaData))!=0){
	printf("WSAStartup failed with error %d\n",Result);
	return;
	}
	ServerSocket=socket(AF_INET,
	SOCK_STREAM,
	IPPROTO_TCP);
	if(ServerSocket<0){
	printf("socket failed with error %d\n",WSAGetLastError());
	return;
	}
	memset(&ServerAddr,0,sizeof(ServerAddr));
	ServerAddr.sin_family=AF_INET;
	ServerAddr.sin_port=htons(ServerPort);
	ServerAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	Result=bind(ServerSocket,
	(SOCKADDR*)&ServerAddr,
	sizeof(ServerAddr));
	if(Result<0){
	printf("bind failed with error %d\n",WSAGetLastError());
	return;
	}
	Result=listen(ServerSocket,5);
	if(Result==SOCKET_ERROR){
	printf("listen failed with error %d\n",WSAGetLastError());
	return;
	}
	while(true){
		system("cls");
		chessboard(cursor[0],cursor[1]);
		printf("等待黑棋....\n");
		NewSocket=accept(ServerSocket,(SOCKADDR*)&ClientAddr,&ClientAddrLen);
		while(true){
			if(NewSocket<0){
				printf("accept failed with error %d\n",WSAGetLastError());
				return;
			}
			else{
				memset(ReceiveBuffer,0,sizeof(ReceiveBuffer));
				if((ReceiveLen=recv(NewSocket,
					ReceiveBuffer,
					1024,
					0))<0){
					printf("recv failed with error %d\n",WSAGetLastError());
					return;
				}
				if(ReceiveLen==0){
					printf("Receive Data Finished\n");
				}
				else{
					ReceiveBuffer[1023]='\0';
					//printf("Receive Data:%s\n",ReceiveBuffer);//接口部分
					sum=chars_to_int(ReceiveBuffer,strlen(ReceiveBuffer));
					xy[sum/100][sum%100]=1;
					cursor[0]=sum/100;
					cursor[1]=sum%100;
					chessboard(sum/100,sum%100);
					PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
					break;
				}
			}
		}
		while(true){
			system("cls");
			chessboard(cursor[0],cursor[1]);
			printf("白棋走：\n");
			switch(c=getch()){
				case 'w':system("cls");cursor[0]--;if(cursor[0]==-1)cursor[0]=21;
									 if(cursor[0]==22)cursor[0]=0;
									 
									 chessboard(cursor[0],cursor[1]);
									 break;
				case 's':system("cls");cursor[0]++;if(cursor[0]==-1)cursor[0]=21;
									 if(cursor[0]==22)cursor[0]=0;
									 
									 chessboard(cursor[0],cursor[1]);
									 break;
				case 'd':system("cls");cursor[1]++;if(cursor[1]==-1)cursor[0]=21;
									 if(cursor[1]==22)cursor[0]=0;
									 
									 chessboard(cursor[0],cursor[1]);
									 break;
				case 'a':system("cls");cursor[1]--;if(cursor[1]==-1)cursor[0]=21;
									 if(cursor[1]==22)cursor[0]=0;
									 
									 chessboard(cursor[0],cursor[1]);
									 break;
				case ' ':system("cls");
						if(xy[cursor[0]][cursor[1]]!=0){
								PlaySoundA("res\\Windows.wav",NULL,SND_FILENAME|SND_ASYNC);
								chessboard(cursor[0],cursor[1]);
								}
						  else{
							  xy[cursor[0]][cursor[1]]=-1;
							  chessboard(cursor[0],cursor[1]);
							  PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
						  }break;
				default:break;
			}
			if(xy[cursor[0]][cursor[1]]==-1 && c==' '){	
				sum=cursor[0]*100+cursor[1];
				memset(ReceiveBuffer,0,sizeof(ReceiveBuffer));
				Set_ReceiveBuffer(sum,ReceiveBuffer);
				SendLength=send(NewSocket,
					ReceiveBuffer,
					strlen(ReceiveBuffer),
					0);
				if(SendLength<0){
					printf("send failed with error %d\n",WSAGetLastError());
					return;
				}
				else {
					//printf("Send Data:%s\n",ReceiveBuffer);
				}
				break;		
			}
		}

		flag=check();
		if(flag==1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("black win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			printf("再来一把？（y/n）\n");
			if((c=getch())=='n'){
				if(closesocket(NewSocket)==SOCKET_ERROR)
					printf("close failed with error %d\n",WSAGetLastError());
				if(closesocket(ServerSocket)==SOCKET_ERROR)
					printf("close failed with error %d\n",WSAGetLastError());
				if(WSACleanup()==SOCKET_ERROR)
					printf("WSAClenup failed with error %d\n",WSAGetLastError());
				break;
			}
			else if((c=getch())=='y')
				memset(xy,0,sizeof(xy));	
		}
		if(flag==-1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("white win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(2000);
			printf("再来一把？（y/n）\n");
			if((c=getch())=='n'){
				if(closesocket(NewSocket)==SOCKET_ERROR)
					printf("close failed with error %d\n",WSAGetLastError());
				if(closesocket(ServerSocket)==SOCKET_ERROR)
					printf("close failed with error %d\n",WSAGetLastError());
				if(WSACleanup()==SOCKET_ERROR)
					printf("WSAClenup failed with error %d\n",WSAGetLastError());
				break;
			}
			else if((c=getch())=='y')
				memset(xy,0,sizeof(xy));		
		}
	}
}
void ai_game(){
	int cursor[2]={10,10};//光标位置,初始值(10,10)
	int order=0;
	int flag=0;
	int turn=0;
	chessboard(cursor[0],cursor[1]);
	PlaySoundA("res\\gamewin.wav",NULL,SND_FILENAME|SND_ASYNC);
	while(true){
		system("cls");
		//printf("\t\t  ");
		chessboard(cursor[0],cursor[1]);
		if(order%2==0){
			//turn=COMPUTER;
			while(true){
				if(order==0){
					xy[1][19]=1;
					order++;
					Sleep(1000);
					break;
				}
				else{
					int sum=computer_input(xy);
					xy[sum/100][sum%100]=1;
					order++;
					PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
					Sleep(1000);
					break;
				}
			}
		}
		else{
			while(true){			
				int sum=go(xy,1);
				xy[sum/100][sum%100]=-1;
				order++;
				PlaySoundA("res\\eat.wav",NULL,SND_FILENAME|SND_ASYNC);
				Sleep(1000);
				break;

			}
		}
	
		flag=check();
		if(flag==1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("black win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(5000);
			system("cls");
			break;
		}
		if(flag==-1){
			system("cls");
			printf("\t\t  ");
			printf("\n");
			chessboard(cursor[0],cursor[1]);
			printf("white win!\n");
			PlaySoundA("res\\Begin.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(5000);
			system("cls");
			break;			
		}
	}
}
void begin_game(int sytle){
	int diffculty=2;
	for(int i=0;i<21;i++)
				for(int j=0;j<21;j++){
					xy[i][j]=0;
				}
	switch(sytle){
		case SINGLE:choose_diffculty_easy();single_game();break;
		case DOUBLE:double_game();break;
		case NETWORK:network_game();break;
		case AI:ai_game();break;
		default:break;
	}
}
void single_player(){
	char c;
	while(1){
		system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t-_-!单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
		c=getch();
		if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			double_player();
		}
		if(c==13){
			sytle=SINGLE;	
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			for(int i=0;i<40;i++){
				if(i%2!=0)
					single_glisten_have();
				else
					single_glisten_no();
				Sleep(100);
			}
			system("cls");
			begin_game(sytle);
		}
	}

}
void double_player(){
	char c;
	while(1){
		system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t-_-!双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
		c=getch();
		if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			network_player();
		}
		if(c==13){
			sytle=DOUBLE;
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			for(int i=0;i<40;i++){
				if(i%2!=0)
					double_glisten_have();
				else
					double_glisten_no();
				Sleep(100);
			}
			begin_game(sytle);
		}
	}
}
void network_player(){
	char c;
	while(1){
		system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t-_-!联机对战\n");
		printf("\t\t\t\t    智能对战\n");
		c=getch();
		if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			ai_player();
		}
		if(c==13){
			sytle=NETWORK;
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			for(int i=0;i<40;i++){
				if(i%2!=0)
					network_glisten_have();
				else
					network_glisten_no();
				Sleep(100);
			}
			begin_game(sytle);
		}
	}
}
void ai_player(){
	char c;
	while(1){
		system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t-_-!智能对战\n");
		c=getch();
		if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			single_player();
		}
		if(c==13){
			sytle=AI;
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			for(int i=0;i<40;i++){
				if(i%2!=0)
					ai_glisten_have();
				else
					ai_glisten_no();
				Sleep(100);
			}
			begin_game(sytle);
		}
	}
}
//闪烁的登陆窗口
void single_glisten_have(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t-_-!单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
}
void single_glisten_no(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t            \n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
}
void double_glisten_have(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t-_-!双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
}
void double_glisten_no(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t            \n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t    智能对战\n");
}
void network_glisten_have(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t-_-!联机对战\n");
		printf("\t\t\t\t    智能对战\n");
}
void network_glisten_no(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t            \n");
		printf("\t\t\t\t    智能对战\n");
}
void ai_glisten_have(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t-_-!智能对战\n");
}
void ai_glisten_no(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    单人游戏\n");
		printf("\t\t\t\t    双人游戏\n");
		printf("\t\t\t\t    联机对战\n");
		printf("\t\t\t\t            \n");
}
/*void choose_diffculty_loadin(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    选择难度\n");
		printf("\t\t\t\t-_-!简单\n");
		printf("\t\t\t\t    中等\n");
		printf("\t\t\t\t    高级\n");
		while(true){
			int c;
			c=getch();
			if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			choose_diffculty_middle();
		}
		if(c==13){
			diffculty=EASY;
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			system("cls");
		}
	}
}*/
void choose_diffculty_easy(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    选择难度\n");
		printf("\t\t\t\t-_-!简单\n");
		printf("\t\t\t\t    中等\n");
		printf("\t\t\t\t    高级\n");
		while(true){
			int c;
			c=getch();
			if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			choose_diffculty_middle();
			return ;
		}
		if(c==13){
			diffculty=EASY;
			PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
			system("cls");
			break;
		}
	}
}
void choose_diffculty_middle(){
	system("cls");
		printf("\n\n\n\t\t");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\t\t   ■■  oooooooo     ooooo    o     o o   ■■\n");
		printf("\t\t   ■■     o            o   ooooo ooooooo ■■\n");
		printf("\t\t   ■■     o           o     ooo    o o   ■■\n");
		printf("\t\t   ■■     o          o     o o o   ooo   ■■\n");
		printf("\t\t   ■■  oooooooo ooooooooooo  o     o o   ■■\n");
		printf("\t\t   ■■     o   o      o       o     ooo   ■■\n");
		printf("\t\t   ■■     o   o      o       o     o o   ■■\n");
		printf("\t\t   ■■     o   o   o  o       o   ooooooo ■■\n");
		printf("\t\t   ■■     o   o    o o       o    o   o  ■■\n");
		printf("\t\t   ■■ ooooooooooo    o       o   o     o ■■\n");
		printf("\t\t   ■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
		printf("\t\t\t\t    选择难度\n");
		printf("\t\t\t\t    简单\n");
		printf("\t\t\t\t-_-!中等\n");
		printf("\t\t\t\t    高级\n");
		while(true){
			int c;
			c=getch();
			if(c==' '){
			PlaySoundA("res\\select.wav",NULL,SND_FILENAME|SND_ASYNC);
			Sleep(100);
			choose_diffculty_easy();
			return ;
			}
			if(c==13){
				diffculty=MIDDLE;
				PlaySoundA("res\\loadin.wav",NULL,SND_FILENAME|SND_ASYNC);
				system("cls");
				break;
			}
		}
}
//小鳖的AI
int go(int qp[][21],int color){
	int returnVal;
	int priority;
	int otherColor;
	int i,j;
	int searchLen,tempPriority;
	int LPosition,RPosition,LLen,RLen,LColor,RColor;
	int LIterRow,LIterCol,RIterRow,RIterCol;
	int LState,RState;
	int LBlank ,RBlank;
	int direction;

	priority = 100;
	tempPriority = 100;

	if(color == white){
		otherColor = black;
	}else {
		otherColor = white;
	}

	for(i=0;i<21;i++)
		for(j=0;j<21;j++){
			if(qp[i][j] != blank) continue;
			//row = i;
			//col = j;
			//确定属性
			
			
			direction = 4;

			while(direction--){ //循环四次 判断四个方向
			


			LLen = RLen = 0;
			LColor = RColor = blank;
			LPosition = RPosition = 1;
			LBlank = RBlank = 0;
			LState = RState = live;
			searchLen = 0;
			

			while(searchLen++ < 4){
				switch(direction){
					case 0:{LIterRow = i;
							LIterCol = j - searchLen;
							RIterRow = i;
							RIterCol = j + searchLen;
						   }break;
					case 1:{LIterRow = i - searchLen;
							LIterCol = j - searchLen;
							RIterRow = i + searchLen;
							RIterCol = j + searchLen;
						   }break;
					case 2:{LIterRow = i - searchLen;
							LIterCol = j ;
							RIterRow = i + searchLen;
							RIterCol = j ;
						   }break;
					case 3:{LIterRow = i + searchLen;
							LIterCol = j - searchLen;
							RIterRow = i - searchLen;
							RIterCol = j + searchLen;
						   }break;
				}
				if((LIterRow >= 0) && (LIterRow <= 20) && (LIterCol >= 0) && (LIterCol <= 20)){
					switch (qp[LIterRow][LIterCol]){
						case  blank:{
									   LBlank ++;
									}break;
						case  white:{if(LBlank > 1)break;
									if(LLen == 0){
										LLen += 1;
										LColor = white;
										LPosition = searchLen;
										if(LPosition == 1) LBlank ++;
									}else if(LColor == qp[LIterRow][LIterCol]){
						 				LLen += 1;
									}else {
										LState = dead;
									}
									}break;
						case black:{if(LBlank > 1)break;
									if(LLen == 0){
										LLen += 1;
										LColor = black;
										LPosition = searchLen;
										if(LPosition == 1) LBlank ++;
									}else if(LColor == qp[LIterRow][LIterCol]){
										LLen += 1;
									}else {
										LState = dead;
									}
									}break;
					}
				}

				if((RIterRow >= 0) && (RIterRow <= 20) && (RIterCol >= 0) && (RIterCol <= 20)){
					switch (qp[RIterRow][RIterCol]){
						case  blank:{
									   RBlank ++;
									}break;
						case  white:{
							if(RBlank > 1)break;
									if(RLen == 0){
										RLen += 1;
										RColor = white;
										RPosition = searchLen;
										if(RPosition == 1) RBlank ++;
									}else if(RColor == qp[RIterRow][RIterCol]){
						 				RLen += 1;
									}else {
										RState = dead;
									}
									}break;
						case black:{
							if(RBlank > 1)break;
									if(RLen == 0){
										RLen += 1;
										RColor = black;
										RPosition = searchLen;
										if(RPosition == 1) RBlank ++;
									}else if(RColor == qp[RIterRow][RIterCol]){
										RLen += 1;
									}else {
										RState = dead;
									}
									}break;
					}
				}
			}

			//判断优先级
			//如果两边是相同颜色
			if(LColor == RColor){
				switch(LLen+RLen){
					case 0:{
						   }break;
					case 1:break;
					case 2:{if(LColor == color){         //长度为2 己方
								if((LPosition == 1) && (RPosition == 1)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 51)  tempPriority = 51 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 54)  tempPriority = 54 ;
									}
									
								}else if((LPosition == 2) && (RPosition == 2)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 52)  tempPriority = 52 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 72)  tempPriority = 72 ;
									}else {
										if(tempPriority > 56)  tempPriority = 56 ;
									}

								}else {
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 50)  tempPriority = 50 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 55)  tempPriority = 55 ;
									}
								}
							//长度为2 对方
							}else { 
								if((LPosition == 1) && (RPosition == 1)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 60)  tempPriority = 60 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 62)  tempPriority = 62;
									}
									
								}else if((LPosition == 2) && (RPosition == 2)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 61)  tempPriority = 61;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 63)  tempPriority = 63 ;
									}
								}else {
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 60)  tempPriority = 60 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 62)  tempPriority = 62 ;
									}
								}
							}
						   }break;
							//长度为3 己方
					case 3:{if(LColor == color){         
								if((LPosition == 1) && (RPosition == 1)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 10)  tempPriority = 10 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 12)  tempPriority = 12 ;
									}
									
								}else if((LPosition == 2) && (RPosition == 2)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 30)  tempPriority = 30 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 30)  tempPriority = 30 ;
									}else {
										if(tempPriority > 30)  tempPriority = 30 ;
									}

								}else {
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 12)  tempPriority = 12 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 12)  tempPriority = 12 ;
									}else {
										if(tempPriority > 12)  tempPriority = 12 ;
									}
								}
							//长度为3 对方
							}else { 
								if((LPosition == 1) && (RPosition == 1)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 20)  tempPriority = 20 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 22)  tempPriority = 22 ;
									}
									
								}else if((LPosition == 2) && (RPosition == 2)){
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 40)  tempPriority = 40 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 40)  tempPriority = 40 ;
									}else {
										if(tempPriority > 40)  tempPriority = 40 ;
									}
								}else {
									if((LState == live) && (RState == live)){ //both live 
										if(tempPriority > 22)  tempPriority = 22 ;
									}else if((LState == dead) && (RState == dead)){//both dead
										if(tempPriority > 22)  tempPriority = 22 ;
									}else {
										if(tempPriority > 22)  tempPriority = 22 ;
									}
								}
							}
						   }break;
					default:{if(LColor == color){
								if((LPosition == 1) && (RPosition == 1)){//落子就赢
									if(tempPriority > 0)  tempPriority = 0 ;
								}else if((LPosition == 2) && (RPosition == 2)){
									if(tempPriority > 30)  tempPriority = 30 ;
								}else {//落子之后有赢点
									if(tempPriority > 11)  tempPriority = 11 ;
								}
							}else {
								if((LPosition == 1) && (RPosition == 1)){
									if(tempPriority > 1)  tempPriority = 1 ;
								}else if((LPosition == 2) && (RPosition == 2)){
									if(tempPriority > 40)  tempPriority = 40 ;
								}else {
									if(tempPriority > 21)  tempPriority = 21 ;
								}
							}
							}break;
				}
			}else{
				//处理左边
				switch(LLen){
					case 0:{
						   }break;
					case 1:{if(LColor == color){
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 70)  tempPriority = 70 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 71)  tempPriority = 71 ;
									}
								}else {
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 70)  tempPriority = 70 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 71)  tempPriority = 71 ;
									}
								}
								
							}else {
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
											if(tempPriority > 80)  tempPriority = 80 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 82)  tempPriority = 82 ;
									}
								}else {
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
											if(tempPriority > 81)  tempPriority = 81 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 82)  tempPriority = 82 ;
									}
								}
							}
						   }break;
					case 2:{if(LColor == color){
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 51)  tempPriority = 51 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 54)  tempPriority = 54 ;
									}
								}else{
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 50)  tempPriority = 50 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 55)  tempPriority = 55 ;
									}
								}
							}else {
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 60)  tempPriority = 60 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 62)  tempPriority = 62 ;
									}
								}else{
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 61)  tempPriority = 61 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 63)  tempPriority = 63 ;
									}
								}
							}
						   }break;
					case 3:{if(LColor == color){
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 10)  tempPriority = 10 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 12)  tempPriority = 12 ;
									}
								}else{
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 13)  tempPriority = 13 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 13)  tempPriority = 13 ;
									}else {
										if(tempPriority > 13)  tempPriority = 13 ;
									}
								}
							}else {
								if(LPosition == 1){
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 20)  tempPriority = 20 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 22)  tempPriority = 22 ;
									}
								}else{
									if((LState == live) && ((RPosition > 1) || (RLen == 0))){ //both live 
										if(tempPriority > 23)  tempPriority = 23 ;
									}else if((LState == dead) && (RPosition == 1)){//both dead
										if(tempPriority > 23)  tempPriority = 23 ;
									}else {
										if(tempPriority > 23)  tempPriority = 23;
									}
								}
							}
						   }break;
					default:{if(LColor == color){
								if(tempPriority > 0)  tempPriority = 0 ;
							}else {
								if(tempPriority > 1)  tempPriority = 1 ;
							}
							}break;
				}
				//处理右边
				switch(RLen){
					case 0:{
						   }break;
					case 1:{if(RColor == color){
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 70)  tempPriority = 70 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 71)  tempPriority = 71 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 70)  tempPriority = 70 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 71)  tempPriority = 71 ;
									}
								}
							}else {
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 80)  tempPriority = 80;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 82)  tempPriority = 82 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 81)  tempPriority = 81 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 82)  tempPriority = 82 ;
									}
								}
							}
						   }break;
					case 2:{if(RColor == color){
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 51)  tempPriority = 51 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 54)  tempPriority = 54 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 50)  tempPriority = 50 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 55)  tempPriority = 55 ;
									}
								}
							}else {
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 60)  tempPriority = 60 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 62)  tempPriority = 62 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 61)  tempPriority = 61 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 63)  tempPriority = 63 ;
									}
								}
							}
						   }break;
					case 3:{if(RColor == color){
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 10)  tempPriority = 10 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 12)  tempPriority = 12 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 13)  tempPriority = 13 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 13)  tempPriority = 13 ;
									}else {
										if(tempPriority > 13)  tempPriority = 13 ;
									}
								}
							}else {
								if(RPosition == 1){
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 20)  tempPriority = 20 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 100)  tempPriority = 100 ;
									}else {
										if(tempPriority > 22)  tempPriority = 22 ;
									}
								}else{
									if((RState == live) && ((LPosition > 1) || (LLen == 0))){ //both live 
										if(tempPriority > 23)  tempPriority = 23 ;
									}else if((RState == dead) && (LPosition == 1)){//both dead
										if(tempPriority > 23)  tempPriority = 23 ;
									}else {
										if(tempPriority > 23)  tempPriority = 23 ;
									}
								}
							}
						   }break;
					default:{if(RColor == color){
								if(tempPriority > 0)  tempPriority = 0 ;
							}else {
								if(tempPriority > 1)  tempPriority = 1 ;
							}
							}break;
				}//end of RLen
			}//end of priority
			}//end out while
		   if(priority > tempPriority){
			   priority = tempPriority;
			   returnVal = 100*i+j;
		   }
		}//end of for
		return returnVal;
}

int choose_diffculty(int diffculty){
	switch(diffculty){
		case EASY:return go(xy,1);break;
		case MIDDLE:return computer_input(xy);break;
		default:break;
	}
	return 0;
}
int chars_to_int(char buffer[],int len){
	int i,temp=0;
	for(i=0;i<len;i++)
		temp=temp*10+(buffer[i]-48);
	return temp;
}
void Set_ReceiveBuffer(int data,char buffer[]){
	int temp=data;
	buffer[0]=temp/1000+48;
	temp=data-data/1000*1000;
	buffer[1]=temp/100+48;
	temp=data-data/100*100;
	buffer[2]=temp/10+48;
	temp=data-data/10*10;
	buffer[3]=temp+48;
	buffer[4]='\0';
}