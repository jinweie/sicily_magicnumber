#include "iostream"
#include "string"
#include "queue"
using namespace std;

#define max 45000

typedef struct
{
	int x, y;    //x��ʾ��һ�е�����y��ʾ�ڶ��е���
	string op;  //�洢ABC����
}Node;

Node start;
Node final;
bool isvisit[45000];
Node array[max]; //����һ��������Ϊ����

void Operate(Node *node, int type)
{
	if(type == 1)   //����A�����������л���
	{
		int swap = node->x;
		node->x = node->y;
		node->y = swap;

		node->op = node->op + 'A'; //��op�ַ�������A
	}
	
	else if (type == 2)
	{
		node->x = (node->x % 10) * 1000 + node->x / 10;
		node->y = (node->y % 10) * 1000 + node->y / 10;

		node->op = node->op + 'B';
	}

	else if (type == 3)
	{
		int i = node->x / 1000 * 1000;
		int j = node->x - i;
		int a = j / 100;
		int b = (j - a * 100)/10;
		int i1 = node->y / 1000 * 1000;
		int j1 = node->y - i1;
		int c = j1 / 100;
		int d = (j1 - c * 100)/10;
		node->x = i + c*100 + a*10 + node->x%10;
		node->y = i1 + d*100 + b*10 + node->y%10;

		node->op = node->op + 'C';
	}
}

bool is_final(Node node)   //�ж��Ƿ��Ѿ��ɹ�
{
	if(node.x == final.x && node.y == final.y)
		return true;
	return false;
}

int cantor(int n, int size) //����nΪҪ����չ��������sizeΪȫ���е�λ��
{
	int arr[8];
	int f[] = {1,1,2,6,24,120,720,5040,40320};
	int sum = 0;

	for (int i = size -1; i >= 0; i--) //��n�ĸ���λ�ϵ����浽arr��
	{
		arr[i] = n % 10;
		n /= 10;
	}
	//����չ��
	for (int i = 0; i < size - 1; i++)
	{
		int counter = 0;
		for(int j = i+1; j < size; j++)
			if(arr[i] > arr[j])
				counter++;
		sum += f[size- i-1] * counter;
	}

	return sum;
}

int main()
{
	int n; //�������Ĳ���
	
	start.x = 1234;
	start.y = 8765;
	start.op = "";
	
	while(cin>>n && n != -1)
	{   
		//Node array[max];  //����һ��������Ϊ����
		final.x = 0;
		final.y = 0;
		for (int i = 0; i < 45000; i++ )
		{
			isvisit[i] = 0;
		}
		for (int i = 0; i < max-1; i++)
		{
			array[i].x = 0;
			array[i].y = 0;
		}
		int fp = 0;
		int rp = 0; //fp,rp�ֱ�ָ�����ͷ��β

		bool sign = false;//�жϽ����ı�ʶ
		int num; //�������
		Node top,temp;
		
		//�����һ�е�������4����ת��Ϊһ����λ��
		for (int i = 0; i < 4; i++)
		{
			cin>>num;
			final.x *= 10;
			final.x += num;
		}
		//����ڶ��е�������4����ת��Ϊһ����λ��
		for (int i = 0; i < 4; i++)
		{
			cin>>num;
			final.y *= 10;
			final.y += num;
		}
		//cout<<"finalΪ��"<<final.x<<final.y<<endl;
		array[fp] = start; //start���
		//cout<<"start�����"<<endl;
		rp++;

		while(fp != rp)   //���зǿ�
		{
			
			top = array[fp];//ȡ����Ԫ��

			//�ж��Ƿ񳬹������ĳ���
			if (top.op.size() > n)
				break;
			else if (is_final(top))
			{
				sign = true;
				break;
			}
			//����ABC����
			for (int i = 1; i < 4; i++)
			{
				temp = top;
				//cout<<"ԭ����Ϊ��"<<temp.x<<temp.y<<endl;
				Operate(&temp, i);  //���Ƚ���A����
				//cout<<"A����"<<temp.x<<temp.y<<endl;
				num = cantor(temp.x * 10000 + temp.y, 8);//��ǰ�Ķ���Ԫ��Ϊtop����temp���п���չ��
				//�жϸ�״̬�Ƿ񱻷��ʹ������û�б����ʹ���������Ϊ�ѷ��ʣ�������״̬���
				if (!isvisit[num])
				{
					isvisit[num] = true;  
					array[rp++] = temp;//û�з��ʹ����
					//cout<<"temp���"<<endl;
				}
			}
			fp++;  //ɾ������Ԫ��
		}
		if(sign)
		{
			if(top.op.size() == 0)
				cout<<"0"<<endl;
			else
				cout<<top.op.size()<<" "<<top.op<<endl;
		}
		else
			cout<<-1<<endl;
	}
	
	return 0;
}
