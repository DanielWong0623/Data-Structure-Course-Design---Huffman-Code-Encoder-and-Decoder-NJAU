#include"HuffmanCode.h"
int main()
{
	HuffmanTree huffTree;
	HuffmanCode huffCode;
	FILE *fp;
	char ch,filename[20];
    int i=0,k=0,ln[93];//��Ÿ����ַ����ִ�����93Ϊ�ı��ĵ����ܳ��ֵ������ַ�
    int *w,validNum=0;//w��Ÿ��ַ�Ȩֵ��validNumΪ�ַ���������
    char *position;//������Ҫ,��¼��Ӧλ�õ��ַ�
    int control,flag=1;

    for(i=0;i<93;i++) ln[i]=0;//���ַ����ִ�����ʼֵΪ0
    printf("���ߣ� ����, �ƿ�182, ѧ��:19218201\n\n");
    while(1)
    {
        StartMenu();
        printf("��������Ҫ���еĲ��������֣���");
        scanf("%d",&control);
        switch(control){
            case 1:
			Choices();
            printf("���������ȡ���ļ�����"); 
            scanf("%s",filename);
            if(!(fp=fopen(filename,"r")))
            {
                printf("�޷����ļ�����ȷ�������Ѵ��ڵ��ļ�����\n");
                exit(-2);
            }
            //��ѭ��ͳ�Ʋ�ͬ�ַ����ֵĴ���
            while(ch!=EOF)
            {
                ch=fgetc(fp);
                if(ch>=32&&ch<=122)
                    ln[ch-' ']++;//��91����Ϊ�����ַ��������ո�
                else if(ch==10)
                    ln[91]++;//��Ϊ���з�
                else 
                    ln[92]++;
                putchar(ch);//����ĵ�����
            }
            fclose(fp);
			printf("\n");
            //���ͳ�ƽ��
            for(i=0;i<93;i++)
            {
                if(ln[i]!=0){
                    validNum++;//������ֵ��ַ�������
                    if(i==91) printf("�س��� ���ִ��� %d\n",ln[i]);
                    else if(i==92) printf("���з� ���ִ��� %d\n",ln[i]);
                    else printf(" %c ���ִ�����%d\n",' '+i,ln[i]);
                }
            }
	        printf("\n�����й���%d�ֲ�ͬ���ַ���\n",validNum);
            //��Ϊ�����֪�������ָ����࣬������ڶ�̬�ֲ����Ȩ�ص�����
            w=(int*)malloc((validNum)*sizeof(int));
            position=(char*)malloc((validNum)*sizeof(char));
            //��������
	        for(i=0;i<93;i++)
                if(ln[i]!=0){
                    w[k]=ln[i];
                    if(i==91) position[k]=10;
                    else if(i==92) position[k]=13;
                    else position[k]=i+' ';
                    k++;
                }
            printf("%s�ļ��򿪲���ȡ�ɹ���\n",filename);
            printf("��ִ����һ��������\n\n\n");
            break;
            case 2:
            GenerateHuffmanTree(&huffTree,w,validNum);
	        Encode(&huffTree,&huffCode,validNum,ln);
            printf("��ִ����һ��������\n\n\n");
            break;
            case 3:
            Compression(&huffTree,&huffCode,validNum,filename,position);
            printf("������ɡ���д��Textcode.huf�ļ��С�\n");
            printf("��ִ����һ��������\n\n\n");
            break;
            case 4:
            CompressionRate(filename);
            printf("��ִ����һ��������\n\n\n");
            break;
            case 5:
            TransCode(&huffTree,position,validNum,filename);
            printf("������ɡ���д��Translation.txt�ļ���\n");
            printf("��ִ����һ��������\n\n\n");
            break;
            case 0:
            flag=0;
            break;
            default:printf("��Чָ����������룡\n");
            continue;
        }
        if(flag==0)
        break;
    }
    printf("\n\n��л����ʹ�ã������ڿ����ڳ��������ļ����ҵ�Textcode.huf��Translation.txt�ļ���\n\n\n");
    return 0;
}