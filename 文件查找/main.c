#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
typedef struct information *stack;
struct information
{
    char path[FILENAME_MAX];
    char houZuiMing[10];
    time_t creat;
    int i;
    stack next;
};
struct Queue
{
    stack front,rear;
} ;
int houZuiMingSearch(stack S,char* houZuiMing);
void FileSearch(char *to_search,int specialNumber,char *special,int *number,struct information**S);
void MinTimeCreat(stack S);
int main()
    {
          printf("��������ҷ�Χ��");
          char string[FILENAME_MAX];
          scanf("%s",&string);
          char *to_search=string;

          printf("\n������ؼ��֣�");
          char special[100];
          scanf("%s",special);

          struct Queue *Q=(struct Queue*)malloc(sizeof(struct Queue));
          Q->front=Q->rear=(stack)malloc(sizeof(struct information));//ͷ�ڵ�
          Q->front->next=NULL;


          int number=0;
          FileSearch(to_search,strlen(special),special,&number,&(Q->rear));
           printf("\n\n�������������������ϱ��Ǵ˴β��ҵ������ļ�������������������������");
          printf("\n\n\n���йؼ��� %s �ļ��� %d ��",special,number);

          printf("\n\n������Ҫ���ҵĺ�׺����");
          char houZuiMing[10];
          scanf("%s",houZuiMing);

          printf("\n���β���\n");
          printf("\n\n�������������������Ϻ�׺��(%s)���ļ���%d������������������\n",houZuiMing,houZuiMingSearch(Q->front,houZuiMing));

          MinTimeCreat(Q->front->next);
        }
void FileSearch(char *to_search,int specialNumber,char *special,int *number,stack *S)
{
    long handle;   //���
    struct _finddata_t fileinfo;   //�ļ���Ϣ�ṹ��
    handle=_findfirst(to_search,&fileinfo);   //��һ�β���
    if(handle==-1) return 0;//����ʧ�ܣ��������
    do{
        if(fileinfo.attrib==_A_SUBDIR) //���ļ���
            {
                if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)continue;
                char to_search_new[FILENAME_MAX];
                strcpy(to_search_new,to_search);
                *(to_search_new+strlen(to_search_new)-1)='\0';
                strcat(to_search_new,fileinfo.name);

                strcat(to_search_new,"\\*");
                FileSearch(to_search_new,specialNumber,special,number,S);
                }
        else    //���ļ�
            {
                int i,m=0,k=0;
                for(i=0;i<strlen(fileinfo.name);i++)
                    if(*(fileinfo.name+i)==*(special+k))
                        {
                            k++;
                            if(k==specialNumber)break;
                        }
                if(k==specialNumber)//�ؼ��ַ���
                    {
                        (*number)++;
                        char to_search_new[FILENAME_MAX];
                        strcpy(to_search_new,to_search);
                        *(to_search_new+strlen(to_search_new)-1)='\0';
                        strcat(to_search_new,fileinfo.name);
                        printf("%s \n",to_search_new);

                        //��ź�׺��
                        (*S)->next=(stack)malloc(sizeof(struct information));
                        *S=(*S)->next;
                        (*S)->i=0;
                        (*S)->next=NULL;
                        strcpy((*S)->path,to_search_new);
                        (*S)->creat=fileinfo.time_create;
                         i=strlen(fileinfo.name)-1;
                        while(1)
                        {
                            if(fileinfo.name[i--]=='.')break;
                        }
                        i=i+1;

                        while(*(fileinfo.name+i)!='\0')

                        {
                            *((*S)->houZuiMing+(m++))=*(fileinfo.name+i);
                            i++;
                        }

                    }
            }

    } while(!_findnext(handle,&fileinfo));//���ҳɹ�Ϊ0
    //�������

     _findclose(handle);//�����˹رվ��

    return 0;
}
int houZuiMingSearch(stack S,char* houZuiMing)
{
    int k=0;
    while(S)
    {
        if(!strcmp(S->houZuiMing,houZuiMing))
                {
                    k++;
                    printf("%s\n",S->path);
                    S->i=1;
                }
        stack S1=S;
        S=S->next;
        //free(S1);
    }
    return k;
}
void MinTimeCreat(stack S)
{
    time_t min=S->creat;
    char Q[FILENAME_MAX];
    while(S&&S->i)
    {
        if(S->creat<=min){min=S->creat;strcpy(Q,S->path);}
        S=S->next;
    }
    printf("\n����ʱ�������FILE \n%s",Q);
}
