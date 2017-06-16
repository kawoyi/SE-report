/*�㷨˼�룺
��Ҫ˼����ʵ��1���ƣ���֮ͬ������
1�����˼����㣬
����Щ�㵱�ɰ뾶Ϊ0��԰����������м��ɡ�
2����ά�������ά

*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//����ṹ��
typedef struct balloon {
	double x;       //����x����
	double y;		//����y����
	double z;		//����z����
	double r;		//��뾶
}Balloon;

//�������������Ѿ����õ�����
typedef struct balloonList {
	struct balloonList * next;
	Balloon balloon;
}BalloonList;

void insert(Balloon balloon);
double distance(Balloon b1, Balloon b2);
int judge(Balloon b);
void putBalloon();
void putPoint(double x, double y,double z);

BalloonList *head = NULL;
double step = 0.01;							//�ı�����λ�õ���С��λ
int num = 0;                                //��������ĸ���
double sumr = 0;							//������¼r^2֮��

int main() {
	int n, pointNum, i;
	printf("����������������: ");
	scanf("%d", &n);
	printf("������������: ");
	scanf("%d", &pointNum);
	for (i = 0; i < pointNum; i++) {
		printf("�������%d���������(�ո����)��", i + 1);
		double x, y, z;
		scanf("%lf %lf", &x, &y,&z);
		putPoint(x, y, z);
	}
	printf("\n����\t x����\t y����\t z����\t �뾶\t r^2֮��\n");
	for (i = 0; i < n; i++) {
		putBalloon();
	}
	printf("\nr^2֮�����Ϊ:\t %lf\n", sumr);
	system("pause");
	return 0;
	}
//�����õĵ���Ϊ�뾶Ϊ0�ĵ�����������
void putPoint(double x, double y,double z) {
	Balloon balloon = { x, y, z, 0 };
	insert(balloon);
}
//����������������
void insert(Balloon balloon) {
	BalloonList * newBalloon = (BalloonList *)malloc(sizeof(BalloonList));
	newBalloon->balloon = balloon;
	newBalloon->next = head;
	head = newBalloon;
}
//�ı�����ĳ�ʼλ�ã������������������
void putBalloon() {
	Balloon balloon = { -1 + step, -1 + step, -1 + step, 0 };
	Balloon maxBalloon = balloon;
	int i, j, k;
	for (i = 0; balloon.x < 1; ++i) {
		balloon.x += step;
		balloon.y = -1 + step;
		for (j = 0; balloon.y < 1; ++j) {
			balloon.y += step;
			balloon.z = -1 + step;
			for (k = 0; balloon.z < 1; ++k) {
				balloon.z += step;
				balloon.r = 0;
				double rstep = 0.1;
				while (rstep > 0.00001) {
					if (balloon.r > maxBalloon.r) {
						maxBalloon = balloon;
					}
					balloon.r += rstep;
					if (!judge(balloon)) {//�����򲻺��ʣ���С�뾶�벽�����³���
						balloon.r -= rstep;
						rstep /= 10;
					}
				}
			}
		}
	}
	if (judge(maxBalloon)) {
		insert(maxBalloon);
		num++;
		sumr += maxBalloon.r * maxBalloon.r;
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBalloon.x, maxBalloon.y, maxBalloon.z, maxBalloon.r, sumr);
	}
}
//�ж��¼���������Ƿ���Ϲ���
int judge(Balloon b) {
	//������������[-1��1]��
	if ((fabs(b.x) + b.r) > 1 || (fabs(b.y) + b.r) > 1 || (fabs(b.z) + b.r) > 1) {
		return 0;
	}
	//���αȽ�����b�����������Ƿ��ཻ
	BalloonList *tmp = head;
	while (tmp) {
		Balloon balloon = tmp->balloon;
		if (distance(b, balloon) < b.r + balloon.r) {
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}
//�ж�����֮��ľ���
double distance(Balloon b1, Balloon b2) {
	double x1 = b1.x;
	double y1 = b1.y; 
	double z1 = b1.z;
	double x2 = b2.x;
	double y2 = b2.y;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +(z1 - z2)*(z1 - z2), 0.5);
}

