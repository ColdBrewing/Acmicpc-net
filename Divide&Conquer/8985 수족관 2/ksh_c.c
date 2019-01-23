//kimsunhee
//8985 : ������2
#include<stdio.h>
#include<stdlib.h>
#define MAX 150000
#define MAXHEIGHT 500000

typedef struct s1 {
	int height;
	int mark;
}drained;

void print(int, int*, int, int*);
drained* setDrainedHeight(int, int, int*, int*, drained*);
void result(int, int, int*, drained*);

int main() {
	int n, i, j;
	int x1, y1, x2, y2;
	int heights[MAX];  //�������� ���� �迭
	int length, totalholes;  //�������� �غ� ����  //�������� ���� ����
	int* holes;  //������ ������ ��ġ
	drained *drainedHeights; //���� ���� ���� ����

	//set array of height
	scanf("%d",&n);
	scanf("%d %d", &x1, &y1);
	length = 0;
	for (i = 1; i < n; i++) {
		scanf("%d %d", &x2, &y2);
		if (y2 == 0) break;
		if (x2 != x1)
			for (j = 0; j < (x2 - x1); j++)
				heights[length++] = y2;
		x1 = x2;
		y1 = y2;
	}
	//set location of holes
	scanf("%d",&totalholes);
	holes = (int*)calloc(totalholes, sizeof(int));
	for (i = 0; i < totalholes; i++) {
		scanf("%d %d %d %d", &holes[i], &x2, &y1, &y2);
	}
	//print input
//	print(length, heights, totalholes, holes);


	/*set real heights of drained water*/
	drainedHeights = (drained*)calloc(length, sizeof(drained));
	drainedHeights = setDrainedHeight(length,totalholes,holes,heights,drainedHeights);
/*	for (i = 0; i < length; i++)
		printf("%d ", drainedHeights[i].height);
	printf("\n\n");
*/
	/**/
	result(length, totalholes, holes, drainedHeights);

	return 0;
}

void print(int len, int* heights, int total, int* holes) {
	int i;

	for (i = 0; i < len; i++)
		printf("%d ",heights[i]);
	printf("\n");
	
	for (i = 0; i < total; i++)
		printf("%d ",holes[i]);
	printf("\n");
}

drained* setDrainedHeight(int length, int totalholes, int* holes, int* heights, drained* drainedHeights) {
	int i, j;
	int min;

	for (i = 0; i < totalholes; i++) { //��� ���۵��� ��������
		min = heights[holes[i]];
		//����
		for (j = holes[i]; j >= 0; j--) {
			if (i!=0 && j == holes[i - 1]) //�ٸ� ������ ������ stop
				break;
			min = heights[j] < min ? heights[j] : min;
			if (drainedHeights[j].mark == 0) {
				drainedHeights[j].height = min;
				drainedHeights[j].mark = 1;
			}
			else
				drainedHeights[j].height = drainedHeights[j].height > min ? drainedHeights[j].height : min;
		}
		//������
		for (j = holes[i] + 1; j < length; j++) {
			if (i != totalholes-1 && j == holes[i + 1]) //�ٸ� ������ ������ stop
				break;
			min = heights[j] < min ? heights[j] : min;
			if (drainedHeights[j].mark == 0) {
				drainedHeights[j].height = min;
				drainedHeights[j].mark = 1;
			}
			else
				drainedHeights[j].height = drainedHeights[j].height > min ? drainedHeights[j].height : min;
		}
	}
	return drainedHeights;
}

void result(int length, int totalholes, int* holes, drained* drainedHeights) {
	int countholes = 0;
	int countwater = 0;
	int i, j;
	int totalWater = 0;
	float totalTime = 0;

	while (1) {
		countwater = 0;
		countholes = 0;
		for (i = 0; i < length; i++) {
			if (drainedHeights[i].height-- > 0) {
				countwater++;
				for (j = 0; j < totalholes; j++)
					if (i == holes[j])
						countholes++;
			}
		}
		if (countholes == 0)
			break;
		totalWater += countwater;
		totalTime += (float)countwater / (float)countholes;
	}
	printf("%.2f\n%d",totalTime, totalWater);
}