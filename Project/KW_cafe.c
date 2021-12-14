#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //��ó����
#include <string.h> //��ó����
#include <stdlib.h>

typedef struct //Ŀ�� ����ü ����
{
	char name[20]; //Ŀ�� �̸�
	int price;//Ŀ�� ����

} coffee;

typedef struct //����Ʈ ����ü ����
{
	char name[20]; //����Ʈ �̸�
	int price;//����Ʈ ����

} dessert;

typedef struct //��ٱ��� ����ü ����
{
	char name[20]; //��ٱ��Ͽ� ��� �̸�
	int price; //��ٱ��Ͽ� ��� ����
	int cnt;//��ٱ��Ͽ� ��� ����
} cart;

set_coffee(coffee*); //Ŀ�� �޴� �ʱ� ����
set_dessert(dessert*); //Ŀ�� �޴� �ʱ� ����

void menu();//�޴��� ���
void menucoffee(coffee*);//Ŀ�� �޴� ���
void menudessert(dessert*);//����Ʈ �޴� ���
void showcart(cart*, int count);//��ٱ��Ͽ� ��� ���ǵ��� ������ �ݾ�, �� �ݾ��� �����ش�.
void buy(int, int*, coffee*, dessert*, cart*);//� �޴��� ������ �Է��ϴ� �Լ�
void pay(cart*, int count, FILE*);// ��ٱ��Ͽ� ��� �� �ٷ� ������ �Ѵ�. �������� txt���Ϸ� ����
void delete(cart* c, int count, int num);//��ٱ��� ���� �Լ�

int main(void)
{
	coffee a[6];// Ŀ�� ����ü ����
	dessert b[4];// ����Ʈ ����ü ����
	cart c[10] = { 0, };//��ٱ��� ����ü ����
	set_coffee(a);//Ŀ�� �޴� ����
	set_dessert(b);//����Ʈ �޴� ����

	printf("=================================================\n");
	printf("******************* KW Cafe *********************\n");
	int count = 0;// ��ٱ��� ���� ��� ���� �ʱ�ȭ
	while (1)// ����� �� ���� �ݺ�
	{
		FILE* file = fopen("receipt.txt", "a+"); //receipt.txt���Ϸ� ������ ��� 
		if (file == NULL) //���� ���� ���н�
		{
			printf("file open error!\n"); //���� ���
			return; //����
		}
		menu();// ��ü �޴� ��� �Լ�
		int sel = 0;// �޴� ��������
		int more = 0;//�߰� �ֹ� ���� ����
		int p = 0;// ���� ���� ����
		int del = 0;//���� ����
		scanf_s("%d", &sel);// �޴� �������� �Է¹���
		switch (sel)//switch ���ǹ� ����
		{
		case 1://Ŀ�Ǹ޴�
			menucoffee(a);
			break;
		case 2://����Ʈ �޴�
			menudessert(b);
			break;
		case 3://��ٱ��� ��ȸ �޴�
			showcart(c, count);
			if (count == 0) break;
			printf("������ ����� �ֽ��ϱ�?(1.YES 2.NO):");
			scanf_s("%d", &del);
			if (del == 1)
			{
				int idx = 0;
				printf("������ �޴��� ��ȣ�� �Է��ϼ���:");
				scanf_s("%d", &idx);//�޴� �Է�
				delete(c, count--, idx);
				printf("���� �Ϸ�\n");
				showcart(c, count);
				break;
			}
			else

				break;

		case 4://���α׷� ����

			return 0;
		default: //�� ��
			printf("�߸��� �����Դϴ�!\n"); //��¹�
		}
		if (sel == 1 || sel == 2) // Ŀ�� & ����Ʈ �޴��� ���
		{
			buy(sel, &count, a, b, c);//���Ÿ� ���� ���� 
			printf("1.�߰� �ֹ� 2.�ٷ� ����:");
			scanf_s("%d", &more);//�߰� �ֹ� ���� �Է�
			switch (more)// �߰� �ֹ� ���ǹ�
			{
			case 1://�߰� �ֹ��� ���
				break;
			case 2:// ��ٱ��� ��ȸ �� ���� ����
				showcart(c, count);//��ٱ��� ��ȸ
				pay(c, count, file);// ��ٱ��� ����
				count = 0;//��ٱ��� ��� �ʱ�ȭ
				fclose(file);//������ close
				break;
			default: //�� ��
				printf("�߸��� �����Դϴ�!\n");
				break;//��¹�
			}
		}
		else if (sel == 3)// ��ٱ��� ��ȸ
		{
			if (count == 0)//����� ���� ���
			{
				continue;
			}
			else // �� ���� ���
			{
				printf("�����Ͻðڽ��ϱ�?(1.YES 2.NO):");// ��ٱ��� ���� ����
				scanf_s("%d", &p);//���� ���� �Է�
				if (p == 1) //���� �� ���
				{
					pay(c, count, file);//���� �Լ�
					count = 0;//��ٱ��� ��� �ʱ�ȭ
					fclose(file);//������ close
				}
				else//�������� ���� ���
				{
					continue;
				}
			}
		}
		else//default�� ���
			continue;
	}
	return 0;
}
set_coffee(coffee* d) //Ŀ�� ����
{
	strcpy(d[0].name, "�Ƹ޸�ī��"); //Ŀ���̸�
	d[0].price = 4000; //Ŀ�� ����

	strcpy(d[1].name, "ī�� ��"); //Ŀ���̸�
	d[1].price = 4500; //Ŀ�� ����

	strcpy(d[2].name, "�ٴҶ��"); //Ŀ���̸�
	d[2].price = 5000; //Ŀ�� ����

	strcpy(d[3].name, "����������"); //Ŀ���̸�
	d[3].price = 3500; //Ŀ�� ����

	strcpy(d[4].name, "ī�� ��ī "); //Ŀ���̸�
	d[4].price = 4500; //Ŀ�� ����

	strcpy(d[5].name, "īǪġ��"); //Ŀ���̸�
	d[5].price = 4500; //Ŀ�� ����
}
set_dessert(dessert* d)//����Ʈ ����
{
	strcpy(d[0].name, "ġ�� ����ũ"); //����Ʈ�̸�
	d[0].price = 6000; //����Ʈ ����

	strcpy(d[1].name, "���ݸ� ����ũ"); //����Ʈ�̸�
	d[1].price = 6000; //����Ʈ ����

	strcpy(d[2].name, "ī���׶�  "); //����Ʈ�̸�
	d[2].price = 4000; //����Ʈ ����

	strcpy(d[3].name, "Ƽ��̼�  "); //����Ʈ�̸�
	d[3].price = 5500; //����Ʈ ����
}

void menu()//�޴� ��� �Լ�
{
	printf("=================================================\n");
	printf(" 1. Coffee \n");
	printf(" 2. Dessert \n");
	printf(" 3. ��ٱ��� ����\n");
	printf(" 4. ���α׷� ����\n");
	printf(" �޴� �����ϼ���:");
}
void menucoffee(coffee* d)// Ŀ�� �޴� ����Լ�
{
	printf("=================================================\n");
	printf("��ȣ	�̸�		Tall / Grande / Venti\n");// ��ȣ �̸� ����(������) ����
	for (int i = 0; i < 6; i++)//�ݺ����� �޴� ���� ��Ŭ ���鼭 �޴� ���
	{
		printf("%d	%s	%d / %d   / %d\n", i + 1, d[i].name, d[i].price, d[i].price + 500, d[i].price + 1000);
	}
	printf("=================================================\n");
}
void menudessert(dessert* d)//����Ʈ �޴� �Լ� ���
{
	printf("=================================================\n");
	printf("��ȣ	�̸�		����\n");//��ȣ �̸� ����
	for (int i = 0; i < 4; i++)//����Ʈ �޴� ������ŭ �ݺ��� ����
	{
		printf("%d	%s	%d\n", i + 1, d[i].name, d[i].price);//�޴� ���
	}
	printf("=================================================\n");
}
void showcart(cart* c, int count)//��ٱ��� ��ȸ �Լ�
{
	int total = 0;

	if (count == 0)
	{
		printf("�ֹ��Ͻ� �޴��� �����ϴ�.\n");
	}
	else {
		printf("=================================================\n");
		printf("�ֹ��Ͻ� �޴����� �Ʒ��� �����ϴ�.\n");
		printf("=================================================\n");
		printf("��ȣ	�޴�			����	����\n");//��ٱ��� ��� ���
		for (int i = 0; i < count; i++)
		{
			printf("%d	%s		%d	%d\n", i + 1, c[i].name, c[i].price, c[i].cnt);//��� ���
			total += (c[i].price * c[i].cnt);//�ѱݾ� ����
		}
		printf("=================================================\n");
		printf("�� ���� �ݾ��� %d �� �Դϴ�.\n", total);//�� �ݾ� ���
	}
}
void buy(int sel, int* count, coffee* a, dessert* b, cart* c)// ���� ���Ÿ� ���� �Լ�
{
	int num = 0;//�ֹ��� �޴� ��ȣ ���� �ʱ�ȭ
	int cnt = 0;// �޴� ���� ���� �ʱ�ȭ
	int exit = 0;// �ݺ��� ���� ���� ����
	int size = 0;//�޴��� ������ ����
	char s1[10] = "[T]";//Tall �ϰ�� �޴� �ڿ� [T] ����
	char s2[10] = "[G]";//Grande �ϰ�� �޴� �ڿ� [G] ����
	char s3[10] = "[V]";//Venti �ϰ�� �޴� �ڿ� [V] ����
	while (exit == 0) //exit�� 0�� �ƴ� �� ���� �ݺ�
	{
		switch (sel) //�޴� ���� ���� 
		{
		case 1:
			printf("�ֹ��Ͻ� �޴��� ��ȣ�� �Է��ϼ���:");
			scanf_s("%d", &num);//�ֹ� �޴� ��ȣ �Է�
			switch (num) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6://1~6R������ �޴� �Է�
				printf("�ֹ��Ͻ� ���� : %s\n", a[num - 1].name);//�迭-1 �� �޴� �̸� ���
				printf("�ֹ��Ͻ� �޴��� ������ �Է��ϼ���:");
				scanf_s("%d", &cnt);//���� �Է�
				printf("�ֹ��Ͻ� ������ ���� : %d ��\n", cnt);
				printf("�ֹ��Ͻ� �޴��� ����� �Է��ϼ���(1.Tall 2.Grande 3.Venti):");
				scanf_s("%d", &size);//������ �Է�

				if (cnt > 0) //������ 0���� Ŭ ���
				{
					strcpy(c[*count].name, a[num - 1].name);//��ٱ��Ͽ� �̸� ����
					switch (size)//����� ���� switch�� 
					{
					case 1://Tall �ϰܿ�
						printf("�ֹ��Ͻ� ������ ������ : Tall \n");
						strcat(c[*count].name, s1);//[T]�̾����
						c[*count].price = a[num - 1].price;//���� ����
						c[*count].cnt = cnt;//���� ����
						(*count)++;//��ٱ��� ��� ��������
						break;
					case 2:
						printf("�ֹ��Ͻ� ������ ������ :Grande\n");
						strcat(c[*count].name, s2);//[G] �̾����
						c[*count].price = a[num - 1].price + 500;//500�� �߰�
						c[*count].cnt = cnt;//���� ����
						(*count)++;//��ٱ��� ��� ��������
						break;
					case 3:
						printf("�ֹ��Ͻ� ������ ������ : Venti\n");
						strcat(c[*count].name, s3);//[V]�̾����
						c[*count].price = a[num - 1].price + 1000;//1000�� �߰�
						c[*count].cnt = cnt;//���� ����
						(*count)++;//��ٱ��� ��� ��������
						break;
					default:
						printf("�߸��� �����Դϴ�.\n ");
					}

					exit++;//�ݺ��� Ż���� ���� ��������
					break;
				}
				else {
					printf("�߸��� �����Դϴ�.\n ");// ������ 0���� �������
					exit++;//Ż��
					break;
				}
			default:
				printf("�߸��� �Է��Դϴ�.\n");
			}
			break;
		case 2:
			printf("�ֹ��Ͻ� �޴��� ��ȣ�� �Է��ϼ���:");
			scanf_s("%d", &num);// ���� �޴� ��ȣ �Է�
			switch (num) {
			case 1:
			case 2:
			case 3:
			case 4://1~4�� �ɟ�޴�
				printf("�ֹ��Ͻ� ����Ʈ : %s\n", b[num - 1].name);//�޴��̸� ����
				printf("�ֹ��Ͻ� �޴��� ������ �Է��ϼ���:");
				scanf_s("%d", &cnt);//�޴� ���� ����
				printf("�ֹ��Ͻ� ����Ʈ�� ���� : %d ��\n", cnt);
				if (cnt > 0) {
					strcpy(c[*count].name, b[num - 1].name);//�޴� �̸� ��ٱ�������
					c[*count].price = b[num - 1].price;//�޴� ���� ��ٱ��� ����
					c[*count].cnt = cnt;//�޴��� ���� ��ٱ��� ����
					exit++;//Ż��
					(*count)++;//��ٱ��� ��� 
					break;
				}
				else {
					printf("�߸��� �����Դϴ�.\n ");
					exit++;//Ż��
					break;
				}
			default:
				printf("�߸��� �Է��Դϴ�.\n");
			}
			break;
		default: //�� ��
			printf("�߸��� �����Դϴ�!\n"); //��¹�
		}
	}
}
void pay(cart* c, int count, FILE* file)//������ ��� �Լ�
{
	int total = 0;
	printf("����� �Ϸ�Ǿ����ϴ�!\n");
	printf("=================================================\n"); //��¹�
	printf("****************** KW Cafe**** ****************\n");
	fprintf(file, "====================================\n");
	fprintf(file, "		  ������\n");
	fprintf(file, "====================================\n");
	fprintf(file, "��ȣ	�޴�			����	����\n");
	for (int i = 0; i < count; i++)//��ٱ��� ��ϸ�ŭ  �ݺ�
	{
		fprintf(file, "%d	%s		%d	%d\n", i + 1, c[i].name, c[i].price, c[i].cnt);//�޴� ���� ����
		total += (c[i].price * c[i].cnt);//�ѱݾ� ������ ����
	}
	fprintf(file, "====================================\n");
	fprintf(file, "�� ���� �ݾ�: %d �� \n", total);//�� �ݾ� ��� ����
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
