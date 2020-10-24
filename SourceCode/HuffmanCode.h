//Textcode.huf����ı��ļ����������Translation.txt���������
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
typedef struct{
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}Node,*HuffmanTree;
typedef char *HuffmanCode;

//��ʼ�˵�
void StartMenu();
//ѡ��Ȩֵ��С���������
void Select(HuffmanTree *Leaf,int n,int *Leaf1,int *Leaf2);
//���ɹ�������
void GenerateHuffmanTree(HuffmanTree *huffTree,int w[],int n);
//���ɹ���������
void Encode(HuffmanTree *huffTree,HuffmanCode *huffCode,int n,int ln[]);
//ѹ��д��.huf�ļ�
void Compression(HuffmanTree *huffTree,HuffmanCode *huffCode,int n,char filename[20],char *position);
//��ѹ����������̣�
void TransCode(HuffmanTree *huffTree,char *position,int n,char filename[20]);
//����ѹ����
void CompressionRate(char filename[20]);
//�ɹ�ѡ����ļ�
void Choices();

