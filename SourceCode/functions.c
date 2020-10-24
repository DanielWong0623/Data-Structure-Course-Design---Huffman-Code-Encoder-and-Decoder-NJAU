#include"HuffmanCode.h"
//��ʼ�˵�
void StartMenu()
{
    printf("*********************************************************************\n");
    printf("*   ��ӭʹ�ñ�ϵͳ����ϵͳ�ṩ�ı��ļ��Ĺ���������/���빦��         *\n");
    printf("*                     �����б����£�                                *\n");
    printf("*                 1.��ȡһ���ı��ļ�                                *\n");
    printf("*                 2.���ɸ��ļ��Ĺ���������                          *\n");
    printf("*                 3.�Ը��ı��ļ����б���                            *\n");
    printf("*                 4.������ļ���ԭ�ļ���С�Աȣ��鿴ѹ����          *\n");
    printf("*                 5.���ݱ�����з�������                            *\n");
    printf("*                 0.�˳���ϵͳ                                      *\n");
    printf("*********************************************************************\n");
}
//ѡ��Ȩֵ��С���������
void Select(HuffmanTree *Leaf,int n,int *Leaf1,int *Leaf2)
{
    int i;
    int minLeaf;
    for(i=1;i<=n;i++){
        if((*Leaf)[i].parent==0)
        {
            minLeaf=i;
            break;
        }
    }
    for(i=1;i<=n;i++)
    {
        if((*Leaf)[i].parent==0)
            if((*Leaf)[i].weight<(*Leaf)[minLeaf].weight)
                minLeaf=i;
    }
    *Leaf1=minLeaf;
    for(i=1;i<=n;i++){
        if((*Leaf)[i].parent==0&&i!=(*Leaf1))
        {
            minLeaf=i;
            break;
        }
    }
    for(i=1;i<=n;i++){
        if((*Leaf)[i].parent==0&&i!=(*Leaf1))
            if((*Leaf)[i].weight<(*Leaf)[minLeaf].weight)
                minLeaf=i;
    }
    *Leaf2=minLeaf;
}
//���ɹ�������
void GenerateHuffmanTree(HuffmanTree *huffTree,int w[],int n)
{
    int sumLeaf=2*n-1;
    int leaf1,leaf2;
    int i;
    *huffTree=(HuffmanTree)malloc((sumLeaf+1)*sizeof(Node));
    for(i=1;i<=n;i++)
    {
        (*huffTree)[i].weight=w[i-1];
        (*huffTree)[i].parent=0;
        (*huffTree)[i].lchild=0;
        (*huffTree)[i].rchild=0;
    }
    for(i=n+1;i<=sumLeaf;i++)
    {
        (*huffTree)[i].weight=0;
        (*huffTree)[i].parent=0;
        (*huffTree)[i].lchild=0;
        (*huffTree)[i].rchild=0;
    }
    printf("\n������������������£�\n");
    for(i=n+1;i<=sumLeaf;i++)
    {
        Select(huffTree,i-1,&leaf1,&leaf2);
        (*huffTree)[leaf1].parent=i;
        (*huffTree)[leaf2].parent=i;
        (*huffTree)[i].lchild=leaf1;
        (*huffTree)[i].rchild=leaf2;
        (*huffTree)[i].weight=(*huffTree)[leaf1].weight+(*huffTree)[leaf2].weight;
        printf("���ϲ��������Ȩֵ��%d %d���ϲ��ɵĽ��Ȩֵ��%d\n",(*huffTree)[leaf1].weight,(*huffTree)[leaf2].weight,(*huffTree)[i].weight);
    }
    printf("\n��������������ϡ�\n");
}
//���ɹ���������
void Encode(HuffmanTree *huffTree,HuffmanCode *huffCode,int n,int ln[])
{
   // FILE *fw,*fp;//���벢д���ļ�
   // char ch;
    int i,k,start,p;
    unsigned int mark;
    char *cd=(char*)malloc(n*sizeof(char));
    huffCode=(HuffmanCode*)malloc((n+1)*sizeof(char*));
    cd[n-1]='\0';
    for(i=1;i<=n;i++)
    {
        start=n-1;
        for(mark=i,p=(*huffTree)[i].parent;p!=0;mark=p,p=(*huffTree)[p].parent)
        {
            if((*huffTree)[p].lchild==mark)
                cd[--start]='0';
            else cd[--start]='1';
        }
        huffCode[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(huffCode[i],&cd[start]);
    }
    free(cd);
    printf("���������£�\n");
	for(k=0,i=1;k<93;k++)
	{
		if(ln[k]!=0)
		{
            if(k==91) printf("���з� : %s\n",huffCode[i]);
            else if(k==92) printf("�س��� : %s\n",huffCode[i]);
            else printf("%c : %s\n",k+32,huffCode[i]);
			i++;
		}
	}
}
//ѹ��д��.huf�ļ�
void Compression(HuffmanTree *huffTree,HuffmanCode *huffCode,int n,char filename[20],char *position)
{
    unsigned char char_temp;//�ݴ�8bits�ַ�
    unsigned long file_len=0;//ͳ���ļ��ܳ��ȣ���ʼֵ��Ϊ0
    char code_buf[25]="\0";//���뻺����
    unsigned int code_len;//���볤��
    FILE *fp,*fw;
    //��ȫ�ֱ�����ÿ����������ʱ����Ҫ���½��б���
    int i,start,p,pos;
    unsigned int mark;
    char *cd=(char*)malloc(n*sizeof(char));
    huffCode=(HuffmanCode*)malloc((n+1)*sizeof(char*));
    cd[n-1]='\0';
    for(i=1;i<=n;i++)
    {
        start=n-1;
        for(mark=i,p=(*huffTree)[i].parent;p!=0;mark=p,p=(*huffTree)[p].parent)
        {
            if((*huffTree)[p].lchild==mark)
                cd[--start]='0';
            else cd[--start]='1';
        }
        huffCode[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(huffCode[i],&cd[start]);
    }
    free(cd);//�������
    //��ʼд��huf�ļ�
    fp=fopen(filename,"rb");
    fw=fopen("Textcode.huf","wb");
    fread((char*)&char_temp,sizeof(unsigned char),1,fp);//��������ʽ����һ���ַ���ÿ��8bits
    while(!feof(fp))
    {
        for(i=1;i<=n;i++)//ѭ���ҵ�ƥ���ַ������б���
            if(char_temp==position[i-1])
            {
                pos=i-1;
                strcat(code_buf,huffCode[pos+1]);//�����ַ���Ӧ�����������ݴ��뻺�����Դ�����
            }
        while(strlen(code_buf)>=8)//��8λ(һ���ֽڳ���)Ϊ����Ԫ
        {
            char_temp='\0';//����ַ��ݴ�ռ䣬��Ϊ�ݴ��ַ���Ӧ����
            for(i=0;i<8;++i)
            {
                char_temp<<=1;//����һλ��Ϊ��һ��bit�ڳ�λ��
                if(code_buf[i]=='1')
                    char_temp|=1;//������Ϊ1��ʹ�û������������ӵ��ֽ����λ
            }
            fwrite((char*)&char_temp,sizeof(unsigned char),1,fw);//���ֽڶ�Ӧ��������ļ�
            strcpy(code_buf,code_buf+8);//���뻺��ȥ���Ѵ����ǰ8λ
        }
        fread((char*)&char_temp,sizeof(unsigned char),1,fp);//ÿ�ζ�ȡ8bits
    }
    code_len=strlen(code_buf);//���������8bits�ı���
    if(code_len>0)
    {
        char_temp='\0';
        for(i=0;i<code_len;++i)
        {
            char_temp <<= 1;
            if(code_buf[i]=='1')
                char_temp |= 1;
        }
        char_temp <<= 8-code_len;//�������ֶδ�β���Ƶ��ֽڸ�λ���ಿ��0
        fwrite((char*)&char_temp,sizeof(unsigned char),1,fw);//�������һ���ֽ�
    }
    fclose(fp);
    fclose(fw);
}   
//��ѹ����������̣�
void TransCode(HuffmanTree *huffTree,char *position,int n,char filename[20])
{
    int i,root=2*n-1;//�ܽ�����
    unsigned long file_len;//�ı��ܳ���
    unsigned long writen_len=0;//�����ļ�д�볤��
    unsigned char code_temp;//�ݴ�8bits����
    //�򿪶�ȡ��д����ļ�
    FILE *fp,*fw;
	FILE *fl;
	fl=fopen(filename,"rb");
	fseek(fl,0L,SEEK_END);
	file_len=ftell(fl);
	fclose(fl);
    fp=fopen("Textcode.huf","rb");
    fw=fopen("Translation.txt","wb");

    while(1)
    {
        fread((char*)&code_temp,sizeof(unsigned char),1,fp);//��8bits
        for(i=0;i<8;++i)
        {
            //�ɸ�����ֱ��Ҷ�������ƥ������Ӧ�ַ�
            if(code_temp & 128)//��Ϊ0
                root=(*huffTree)[root].rchild;
            else
                root=(*huffTree)[root].lchild;
            
            if((*huffTree)[root].lchild==0&&(*huffTree)[root].rchild==0)
            {
                fwrite((char*)&position[root-1],sizeof(unsigned char),1,fw);
                writen_len++;
                if(writen_len==file_len)//���Ƴ�������forѭ��
                    break;
                root=2*n-1;//root��λ
            }
            code_temp<<=1;//���ƹ�ƥ��
        }
        if(writen_len==file_len) break;
    }
    //�ر��ļ�
    fclose(fp);
    fclose(fw);
}
//����ѹ����
void CompressionRate(char filename[20])
{
    FILE *fp1,*fp2;
    double len1,len2;
    fp1=fopen("Textcode.huf","rb");
    fp2=fopen(filename,"rb");;
    fseek(fp1,0L,SEEK_END);
    fseek(fp2,0L,SEEK_END);
    len1=ftell(fp1);
    len2=ftell(fp2);
    printf("\n���ı��ĵ�ѹ����Ϊ���ٷ�֮%2.3lf\n",100-len1/len2*100);
    fclose(fp1);
    fclose(fp2);
}
void Choices()
{
	printf("Ŀǰ�ɹ�ѡ����ļ��У� 1.BestSeller.txt  2.Gatsby.txt 3.Rye.txt\n");
}