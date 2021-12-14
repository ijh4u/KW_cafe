#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //전처리문
#include <string.h> //전처리문
#include <stdlib.h>

typedef struct //커피 구조체 선언
{
	char name[20]; //커피 이름
	int price;//커피 가격

} coffee;

typedef struct //디저트 구조체 선언
{
	char name[20]; //디저트 이름
	int price;//디저트 가격

} dessert;

typedef struct //장바구니 구조체 선언
{
	char name[20]; //장바구니에 담긴 이름
	int price; //장바구니에 담긴 가격
	int cnt;//장바구니에 담긴 개수
} cart;

set_coffee(coffee*); //커피 메뉴 초기 셋팅
set_dessert(dessert*); //커피 메뉴 초기 셋팅

void menu();//메뉴판 출력
void menucoffee(coffee*);//커피 메뉴 출력
void menudessert(dessert*);//디저트 메뉴 출력
void showcart(cart*, int count);//장바구니에 담긴 물건들의 수량과 금액, 총 금액을 보여준다.
void buy(int, int*, coffee*, dessert*, cart*);//어떤 메뉴와 수량을 입력하는 함수
void pay(cart*, int count, FILE*);// 장바구니에 담긴 및 바로 결제를 한다. 영수증이 txt파일로 저장
void delete(cart* c, int count, int num);//장바구니 삭제 함수

int main(void)
{
	coffee a[6];// 커피 구조체 선언
	dessert b[4];// 디저트 구조체 선언
	cart c[10] = { 0, };//장바구니 구조체 선언
	set_coffee(a);//커피 메뉴 설정
	set_dessert(b);//디저트 메뉴 설정

	printf("=================================================\n");
	printf("******************* KW Cafe *********************\n");
	int count = 0;// 장바구니 안의 목록 개수 초기화
	while (1)// 종료될 때 까지 반복
	{
		FILE* file = fopen("receipt.txt", "a+"); //receipt.txt파일로 영수증 출력 
		if (file == NULL) //파일 열기 실패시
		{
			printf("file open error!\n"); //오류 출력
			return; //종료
		}
		menu();// 전체 메뉴 출력 함수
		int sel = 0;// 메뉴 선택인자
		int more = 0;//추가 주문 선택 인자
		int p = 0;// 결제 선택 인자
		int del = 0;//삭제 인자
		scanf_s("%d", &sel);// 메뉴 선택인자 입력받음
		switch (sel)//switch 조건문 실행
		{
		case 1://커피메뉴
			menucoffee(a);
			break;
		case 2://디저트 메뉴
			menudessert(b);
			break;
		case 3://장바구니 조회 메뉴
			showcart(c, count);
			if (count == 0) break;
			printf("삭제할 목록이 있습니까?(1.YES 2.NO):");
			scanf_s("%d", &del);
			if (del == 1)
			{
				int idx = 0;
				printf("삭제할 메뉴의 번호를 입력하세요:");
				scanf_s("%d", &idx);//메뉴 입력
				delete(c, count--, idx);
				printf("삭제 완료\n");
				showcart(c, count);
				break;
			}
			else

				break;

		case 4://프로그램 종료

			return 0;
		default: //그 외
			printf("잘못된 선택입니다!\n"); //출력문
		}
		if (sel == 1 || sel == 2) // 커피 & 디저트 메뉴일 경우
		{
			buy(sel, &count, a, b, c);//구매를 위한 정보 
			printf("1.추가 주문 2.바로 결제:");
			scanf_s("%d", &more);//추가 주문 인자 입력
			switch (more)// 추가 주문 조건문
			{
			case 1://추가 주문일 경우
				break;
			case 2:// 장바구니 조회 후 결제 진행
				showcart(c, count);//장바구니 조회
				pay(c, count, file);// 장바구니 결제
				count = 0;//장바구니 목록 초기화
				fclose(file);//영수증 close
				break;
			default: //그 외
				printf("잘못된 선택입니다!\n");
				break;//출력문
			}
		}
		else if (sel == 3)// 장바구니 조회
		{
			if (count == 0)//목록이 없을 경우
			{
				continue;
			}
			else // 그 외의 경우
			{
				printf("결제하시겠습니까?(1.YES 2.NO):");// 장바구니 결제 결정
				scanf_s("%d", &p);//결제 인자 입력
				if (p == 1) //결제 할 경우
				{
					pay(c, count, file);//결제 함수
					count = 0;//장바구니 목록 초기화
					fclose(file);//영수증 close
				}
				else//결제하지 않을 경우
				{
					continue;
				}
			}
		}
		else//default인 경우
			continue;
	}
	return 0;
}
set_coffee(coffee* d) //커피 설정
{
	strcpy(d[0].name, "아메리카노"); //커피이름
	d[0].price = 4000; //커피 가격

	strcpy(d[1].name, "카페 라떼"); //커피이름
	d[1].price = 4500; //커피 가격

	strcpy(d[2].name, "바닐라라떼"); //커피이름
	d[2].price = 5000; //커피 가격

	strcpy(d[3].name, "에스프레소"); //커피이름
	d[3].price = 3500; //커피 가격

	strcpy(d[4].name, "카페 모카 "); //커피이름
	d[4].price = 4500; //커피 가격

	strcpy(d[5].name, "카푸치노"); //커피이름
	d[5].price = 4500; //커피 가격
}
set_dessert(dessert* d)//디저트 설정
{
	strcpy(d[0].name, "치즈 케이크"); //디저트이름
	d[0].price = 6000; //디저트 가격

	strcpy(d[1].name, "초콜릿 케이크"); //디저트이름
	d[1].price = 6000; //디저트 가격

	strcpy(d[2].name, "카스테라  "); //디저트이름
	d[2].price = 4000; //디저트 가격

	strcpy(d[3].name, "티라미수  "); //디저트이름
	d[3].price = 5500; //디저트 가격
}

void menu()//메뉴 출력 함수
{
	printf("=================================================\n");
	printf(" 1. Coffee \n");
	printf(" 2. Dessert \n");
	printf(" 3. 장바구니 보기\n");
	printf(" 4. 프로그램 종료\n");
	printf(" 메뉴 선택하세요:");
}
void menucoffee(coffee* d)// 커피 메뉴 출력함수
{
	printf("=================================================\n");
	printf("번호	이름		Tall / Grande / Venti\n");// 번호 이름 가격(사이즈) 순서
	for (int i = 0; i < 6; i++)//반복문을 메뉴 개수 만클 돌면서 메뉴 출력
	{
		printf("%d	%s	%d / %d   / %d\n", i + 1, d[i].name, d[i].price, d[i].price + 500, d[i].price + 1000);
	}
	printf("=================================================\n");
}
void menudessert(dessert* d)//디저트 메뉴 함수 출력
{
	printf("=================================================\n");
	printf("번호	이름		가격\n");//번호 이름 가격
	for (int i = 0; i < 4; i++)//디저트 메뉴 개수만큼 반복문 실행
	{
		printf("%d	%s	%d\n", i + 1, d[i].name, d[i].price);//메뉴 출력
	}
	printf("=================================================\n");
}
void showcart(cart* c, int count)//장바구니 조회 함수
{
	int total = 0;

	if (count == 0)
	{
		printf("주문하신 메뉴가 없습니다.\n");
	}
	else {
		printf("=================================================\n");
		printf("주문하신 메뉴들은 아래와 같습니다.\n");
		printf("=================================================\n");
		printf("번호	메뉴			가격	수량\n");//장바구니 목록 출력
		for (int i = 0; i < count; i++)
		{
			printf("%d	%s		%d	%d\n", i + 1, c[i].name, c[i].price, c[i].cnt);//목록 출력
			total += (c[i].price * c[i].cnt);//총금액 저장
		}
		printf("=================================================\n");
		printf("총 결제 금액은 %d 원 입니다.\n", total);//총 금액 출력
	}
}
void buy(int sel, int* count, coffee* a, dessert* b, cart* c)// 물건 구매를 위한 함수
{
	int num = 0;//주문할 메뉴 번호 인자 초기화
	int cnt = 0;// 메뉴 갯수 인자 초기화
	int exit = 0;// 반복문 끝낼 조건 인자
	int size = 0;//메뉴의 사이즈 인자
	char s1[10] = "[T]";//Tall 일경우 메뉴 뒤에 [T] 붙임
	char s2[10] = "[G]";//Grande 일경우 메뉴 뒤에 [G] 붙임
	char s3[10] = "[V]";//Venti 일경우 메뉴 뒤에 [V] 붙임
	while (exit == 0) //exit가 0이 아닐 때 까지 반복
	{
		switch (sel) //메뉴 선택 인자 
		{
		case 1:
			printf("주문하실 메뉴의 번호를 입력하세요:");
			scanf_s("%d", &num);//주문 메뉴 번호 입력
			switch (num) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6://1~6R까지는 메뉴 입력
				printf("주문하신 음료 : %s\n", a[num - 1].name);//배열-1 후 메뉴 이름 출력
				printf("주문하실 메뉴의 개수를 입력하세요:");
				scanf_s("%d", &cnt);//개수 입력
				printf("주문하신 음료의 수량 : %d 개\n", cnt);
				printf("주문하실 메뉴의 사이즈를 입력하세요(1.Tall 2.Grande 3.Venti):");
				scanf_s("%d", &size);//사이즈 입력

				if (cnt > 0) //개수가 0보다 클 경우
				{
					strcpy(c[*count].name, a[num - 1].name);//장바구니에 이름 설정
					switch (size)//사이즈에 따른 switch문 
					{
					case 1://Tall 일겨우
						printf("주문하신 음료의 사이즈 : Tall \n");
						strcat(c[*count].name, s1);//[T]이어붙임
						c[*count].price = a[num - 1].price;//원래 가격
						c[*count].cnt = cnt;//개수 저장
						(*count)++;//장바구니 목록 후위증가
						break;
					case 2:
						printf("주문하신 음료의 사이즈 :Grande\n");
						strcat(c[*count].name, s2);//[G] 이어붙임
						c[*count].price = a[num - 1].price + 500;//500원 추가
						c[*count].cnt = cnt;//개수 저장
						(*count)++;//장바구니 목록 후위증가
						break;
					case 3:
						printf("주문하신 음료의 사이즈 : Venti\n");
						strcat(c[*count].name, s3);//[V]이어붙임
						c[*count].price = a[num - 1].price + 1000;//1000원 추가
						c[*count].cnt = cnt;//개수 저장
						(*count)++;//장바구니 목록 후위증가
						break;
					default:
						printf("잘못된 수량입니다.\n ");
					}

					exit++;//반복문 탈출을 위한 조건인자
					break;
				}
				else {
					printf("잘못된 수량입니다.\n ");// 개수가 0보다 작을경우
					exit++;//탈출
					break;
				}
			default:
				printf("잘못된 입력입니다.\n");
			}
			break;
		case 2:
			printf("주문하실 메뉴의 번호를 입력하세요:");
			scanf_s("%d", &num);// 케익 메뉴 번호 입력
			switch (num) {
			case 1:
			case 2:
			case 3:
			case 4://1~4는 케잌메뉴
				printf("주문하신 디저트 : %s\n", b[num - 1].name);//메뉴이름 저장
				printf("주문하실 메뉴의 개수를 입력하세요:");
				scanf_s("%d", &cnt);//메뉴 개수 저장
				printf("주문하신 디저트의 수량 : %d 개\n", cnt);
				if (cnt > 0) {
					strcpy(c[*count].name, b[num - 1].name);//메뉴 이름 장바구니저장
					c[*count].price = b[num - 1].price;//메뉴 가격 장바구니 저장
					c[*count].cnt = cnt;//메뉴의 개수 장바구니 저장
					exit++;//탈출
					(*count)++;//장바구니 목록 
					break;
				}
				else {
					printf("잘못된 수량입니다.\n ");
					exit++;//탈출
					break;
				}
			default:
				printf("잘못된 입력입니다.\n");
			}
			break;
		default: //그 외
			printf("잘못된 선택입니다!\n"); //출력문
		}
	}
}
void pay(cart* c, int count, FILE* file)//영수증 출력 함수
{
	int total = 0;
	printf("계산이 완료되었습니다!\n");
	printf("=================================================\n"); //출력문
	printf("****************** KW Cafe**** ****************\n");
	fprintf(file, "====================================\n");
	fprintf(file, "		  영수증\n");
	fprintf(file, "====================================\n");
	fprintf(file, "번호	메뉴			가격	수량\n");
	for (int i = 0; i < count; i++)//장바구니 목록만큼  반복
	{
		fprintf(file, "%d	%s		%d	%d\n", i + 1, c[i].name, c[i].price, c[i].cnt);//메뉴 정보 저장
		total += (c[i].price * c[i].cnt);//총금액 영수증 저장
	}
	fprintf(file, "====================================\n");
	fprintf(file, "총 결제 금액: %d 원 \n", total);//총 금액 출력 저장
	fprintf(file, "====================================\n");

}
void delete(cart* c, int count, int num)
{
	int i = num - 1;
	if (c == NULL)return;
	while (1) {
		if (i < count) {
			c[i] = c[i + 1];
			i++;
		}
		else
			break;
	}
}
