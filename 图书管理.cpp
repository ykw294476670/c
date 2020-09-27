#include<stdio.h>
#include<string.h>

#define BookSize 100
#define BLHum 50
#define BLHnum 50
#define RRnum 50

/*�����ݿ��ļ�*/
typedef struct {
    int bno;
    char bname[21];
    int namenext;
    char author[9];
    int authnext;
    char press[11];
    int prenext;
    char sortno[4];
    int storenum;
    int borrownum;
}BookRecType;
typedef struct {
    BookRecType BookDbase[BookSize];
    int len;
}BookDbaseFile;


/*��������ļ�*/
typedef struct {
    int bno;
    int RecNo;
}BidxRecType;
typedef struct {
    BidxRecType BnoIdx[BookSize];
    int len;
}BnoIdxFile;


/*������ͷ�����ļ�*/
typedef struct {
    char bname[21];
    int lhead;
    int RecNum;
}BNRecType;
typedef struct {
    BNRecType LHFrecl[BLHum];
    int len1;
}LHFile1;


/*������ͷ�����ļ�*/
typedef struct {
    char author[9];
    int lhead;
    int RecNum;
}BARecType;
typedef struct {
    BARecType LHFrec2[BLHnum];
    int len2;
}LHFile2;


/*��������ͷ�����ʼ�*/
typedef struct {
    char press[11];
    int lhead;
    int RecNum;
}BPRecType;
typedef struct {
    BPRecType LHFrec3[BLHnum];
    int len3;
}LHFile3;


/*�����ļ�*/
typedef struct {
    int rno;
    char name[8];
    int bn1;
    int bn2;
}RRecType;
typedef struct {
    RRecType ReadRec[RRnum];
    int len;
}ReadFile;


/*�軹���ļ�*/
typedef struct {
    int rno;
    int bno;
    char date1[9];
    char date2[9];
}BbookRecType;
typedef struct {
    BbookRecType Bbook[BookSize];
    int len;
}BbookFile;


/*׷��һ��ͼ���¼��������ļ�*/
BookDbaseFile AppeDBaseRec(BookDbaseFile df)
{
    int i;
    printf("���  ����  ������ ������ ����  ������\n");
    scanf("%d%s", df.BookDbase[i].bno, df.BookDbase[i].bname);
    scanf("%s%s", df.BookDbase[i].author, df.BookDbase[i].press);
    scanf("%s %d", df.BookDbase[i].sortno, &df.BookDbase[i].storenum);
    df.BookDbase[i].borrownum = 0;
    return df;
}

/*�޸��������������*/
BnoIdxFile ChangeBnoIdxF(BookDbaseFile df, BnoIdxFile bif)
{
    int i, j, k = 1;
    i = df.len;
    j = bif.len;
    while (j >= 1)
    {
        if (df.BookDbase[i].bno>bif.BnoIdx[j].bno)
        {
            k = j + 1;
            break;
        }
        j--;
    }
    if (bif.len>0)
        for (j = bif.len; j >= k; j--)
            bif.BnoIdx[j + 1] = bif.BnoIdx[j];
    bif.BnoIdx[k].bno = df.BookDbase[i].bno;
    bif.BnoIdx[k].RecNo = i;
    bif.len++;
    return bif;
}


/*�޸����������Լ�������ͷ���������*/
LHFile1 ChangeLinkHeadF1(BookDbaseFile *df, LHFile1 lhf1)
{
    int i, j, k, m;
    char sm[21];
    i = df->len;
    strcpy(sm , df->BookDbase[i].bname);
    j = 1;
    k = 0;
    while (j <= lhf1.len1)
    {
        if (strcmp(sm, lhf1.LHFrecl[j].bname) == 0)
        {
            k = j;
            break;
        }
        j++;
    }
    if (k != 0)
    {
        df->BookDbase[i].namenext = lhf1.LHFrecl[k].lhead;
        lhf1.LHFrecl[k].lhead = i;
        lhf1.LHFrecl[k].RecNum++;
    }
    else
    {
        m = ++lhf1.len1;
        df->BookDbase[i].namenext = 0;
        lhf1.LHFrecl[m].lhead = i;
        lhf1.LHFrecl[m].RecNum = 1;
        strcpy(lhf1.LHFrecl[m].bname, sm);
    }
    return lhf1;
}


/*�޸����������Լ�������ͷ����������*/
LHFile2 ChangeLinkHeadF2(BookDbaseFile *df, LHFile2 lhf2)
{
    int i, j, k, m;
    char zz[9];
    i = df->len;
    strcpy(zz, df->BookDbase[i].author);
    j = 1;
    k = 0;
    while (j <= lhf2.len2)
    {
        if (strcmp(zz, lhf2.LHFrec2[j].author) == 0)
        {
            k = j;
            break;
        }
        j++;
    }
    if (k != 0)
    {
        df->BookDbase[i].authnext = lhf2.LHFrec2[k].lhead;
        lhf2.LHFrec2[k].lhead = i;
        lhf2.LHFrec2[k].RecNum = 1;
        strcpy(lhf2.LHFrec2[m].author, zz);
    }
    return lhf2;
}


/*�޸ĳ�����������Լ���������ͷ����������*/
LHFile3 ChangeLinkHeadF3(BookDbaseFile *df, LHFile3 lhf3)
{
    int i, j, k, m;
    char cbs[11];
    i = df->len;
    strcpy(cbs, df->BookDbase[i].press);
    j = 1;
    k = 0;
    while (j <= lhf3.len3)
    {
        if (strcmp(cbs, lhf3.LHFrec3[j].press) == 0)
        {
            k = j;
            break;
        }
        j++;
    }
    if (k != 0)
    {
        df->BookDbase[i].prenext = lhf3.LHFrec3[k].lhead;
        lhf3.LHFrec3[k].lhead = i;
        lhf3.LHFrec3[k].RecNum++;
    }
    else
    {
        m = ++lhf3.len3;
        df->BookDbase[i].prenext = 0;
        lhf3.LHFrec3[m].lhead = i;
        lhf3.LHFrec3[m].RecNum = i;
        strcpy(lhf3.LHFrec3[m].press, cbs);
    }
    return lhf3;
}


/*�ö��ֲ���ʵ����Ų�ѯ�㷨*/
int BinSearch(BnoIdxFile bif, int key)
{
    int low, high, mid;
    low = 1;
    high = bif.len;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key == bif.BnoIdx[mid].bno)
            return bif.BnoIdx[mid].RecNo;
        else
            if (key<bif.BnoIdx[mid].bno)
                high = mid - 1;
            else
                low = mid + 1;
    }
    return 0;
}


/*��������ѯ�㷨�����*/
int BnameFind(LHFile1 lhf1, char key[])
{
    int i, k = 0;
    for (i = 1; i<=lhf1.len1;i++)
    {
        if (strcmp(key, lhf1.LHFrecl[1].bname) == 0)
        {
            k = lhf1.LHFrecl[i].lhead;
            break;
        }
    }
    return k;
}


/*�����߲�ѯ�㷨�����*/
int BauthFind(LHFile2 lhf2, char key[])
{
    int i, k = 0;
    for (i = 1; i <= lhf2.len2; i++)
    {
        if (strcmp(key, lhf2.LHFrec2[i].author) == 0)
        {
            k = lhf2.LHFrec2[i].lhead;
            break;
        }
    }
    return k;
}



/*���һ��ͼ�������ݿ��¼�����*/
void ShowRec(BookDbaseFile df, int i)
{
    printf("���  ����  ������ ������ ����� �ɽ���\n");
    printf("==============================================\n");
    printf("%d%12s", df.BookDbase[i].bno, df.BookDbase[i].bname);
    printf("%8s%12s", df.BookDbase[i].author, df.BookDbase[i].press);
    printf("%6s", df.BookDbase[i].sortno);
    printf("%4d\n", df.BookDbase[i].storenum - df.BookDbase[i].borrownum);
    printf("==============================================\n");
}

/*ͼ���ѯ���Ƴ������*/
void SearchBook(BookDbaseFile df, BnoIdxFile bif, LHFile1 f1, LHFile2 f2, LHFile3 f3)
{
    char sm[21], zz[9],cbs[11];
    int i, k, choose = 1;
    int sh;
    while (choose >= 1 && choose <= 5)
    {
        printf("ͼ���ѯ��ϵͳ\n");
        printf("------------------\n");
        printf("1.�� ��       2.�� ��\n");
        printf("3.�� ��       4.������\n");
        printf("5.�� ��   �� ѯ");
        printf("------------------\n");
        printf("    �� �� �� ѡ ��");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("����ѧ�ţ�");
            scanf("%d", &sh);
            k = BinSearch(bif, sh);
            if (k == 0) {
                printf("û��Ҫ����ͼ�飬�����Ƿ������д�\n");
                break;
            }
            ShowRec(df, k);
            break;

        case 2:
            printf("����������");
            scanf("%", &sm);
            k = BnameFind(f1, sm);
            if (k == 0) {
                printf("û��Ҫ����ͼ�飬�����Ƿ������д�\n");
                break;
            }
            for (i = k; i; i = df.BookDbase[i].namenext)
                ShowRec(df, i);
            break;

        case 3:
            printf("������������");
            scanf("%s", &zz);
            k = BauthFind(f2, zz);
            if (k == 0) {
                printf("û��Ҫ����ͼ�飬�����Ƿ������д�\n");
                break;
            }
            for (i = k; i; i = df.BookDbase[i].authnext)
                ShowRec(df, i);
            break;

        case 4:
            printf("��������磺");
            scanf("%s", &cbs);
            

        case 5:
            return;
        }
    }
}


/*�軹�鴦���㷨*/
void BorrowBook(BookDbaseFile *bf, BnoIdxFile bif, BbookFile *bbf, ReadFile *rf)
{
    char jyrq[9];
    int sh, dzh;
    int i, j, k = 0;
    printf("������ߺ�   ���  ��������\n");
    scanf("%d%d%s", &dzh, &sh, jyrq);
    for (i = 1; i <= rf->len; i++)
    {
        if (dzh == rf->ReadRec[i].rno)
        {
            k = i;
            break;
        }
    }
    if (k == 0)
    {
        printf("�Ƿ����ߣ�\n");
        return;
    }
    if (rf->ReadRec[k].bn2 >= rf->ReadRec[k].bn1)
    {
        printf("���ѽ���!\n");
        return;
    }
    j = BinSearch(bif, sh);
    if (j == 0)
    {
        printf("�Ƿ���ţ�");
            return;
    }
    if (bf->BookDbase[j].borrownum >= bf->BookDbase[j].storenum)
    {
        printf("ͼ���ѽ��\n");
        return;
    }
    i = ++bbf->len;
    bbf->Bbook[i].rno = dzh;
    bbf->Bbook[i].bno = sh;
    strcpy(bbf->Bbook[i].date1, jyrq);
    rf->ReadRec[k].bn2++;
    bf->BookDbase[j].borrownum++;
    printf("����ɹ���\n");
}

/*���鴦���㷨�����*/
void BackBook(BookDbaseFile *bf,BnoIdxFile bif ,BbookFile *bbf, ReadFile *rf)
{
    char hsrq[8];
    int sh, dzh;
    int i, j, k = 0, m = 0;
    printf("���ߺ� ���  ��������\n");
    scanf("%d%d%s", &dzh, &sh, hsrq);
    for (i = 1; i <= rf->len; i++)
    {
        if (dzh == rf->ReadRec[i].rno)
        {
            k = i;
            break;
        }
    }
    if (k == 0)
    {
        printf("�Ƿ����ߣ�\n");
        return;
    }
    for (i = 1; i <= bbf->len; i++)
        if (sh == bbf->Bbook[i].bno)
        {
            m = i;
            break;
        }
    if (m == 0)
    {
        printf("�Ƿ���ţ�\n");
        return;
    }
    j = BinSearch(bif, sh);
    if (j == 0)
    {
        printf("�Ƿ���ţ�\n");
        return;
    }
    rf->ReadRec[k].bn2--;
    bf->BookDbase[j].borrownum--;
    strcpy(bbf->Bbook[m].date2, hsrq);
    printf("����ɹ���\n");
}

/*���߹�����ϵͳ*/
ReadFile ReaderManage(ReadFile rf)
{
    int i;
    char yn = 'y';
    i = ++rf.len;
    while (yn == 'y' || yn == 'Y')
    {
        printf("������ߺ�   ������ �ɽ�ͼ����\n");
        scanf("%d %s", &rf.ReadRec[i].rno, rf.ReadRec[i].name);
        scanf("%d", &rf.ReadRec[i].bn1);
        rf.ReadRec[i].bn2 = 0;
        printf("����������y/n:");
        getchar();
        scanf("%c",&yn);
    }
    rf.len=i-1;
    return rf;
}

/*д�����ļ�*/
void writefile(BookDbaseFile bf, BnoIdxFile bif, LHFile1 f1, LHFile2 f2, LHFile3 f3, ReadFile rf, BbookFile bbf)
{
    FILE *fp;
    int i;
    //ͼ�����ļ� 
    fp = fopen("book", "wb");
    for (i = 1; i <= bf.len; i++)
        fwrite(&bf.BookDbase[i],sizeof(BookRecType), 1, fp);
    fclose(fp);
    //ͼ�������ļ� 
    fp = fopen("bidx", "wb");
    for (i = 1; i <= bif.len; i++)
        fwrite(&bif.BnoIdx[i], sizeof(BidxRecType), 1, fp);
    fclose(fp);
    //����������ͷ�ļ� 
    fp = fopen("nidx", "wb");
    for (i = 1; i <= f1.len1; i++)
        fwrite(&f1.LHFrecl[i], sizeof(BNRecType), 1, fp);
    fclose(fp);
    //����������ͷ�ļ�
    fp = fopen("aidx", "wb");
    for (i = 1; i <= f2.len2; i++)
        fwrite(&f2.LHFrec2[i], sizeof(BARecType), 1, fp);
    fclose(fp);
    //������������ͷ�ļ�
    fp = fopen("pidx", "wb");
    for (i = 1; i <= f3.len3; i++)
        fwrite(&f3.LHFrec3[i], sizeof(BPRecType), 1, fp);
    fclose(fp);
    //�����ļ�
    fp = fopen("read", "wb");
    for (i = 1; i <= rf.len; i++)
        fwrite(&rf.ReadRec[i], sizeof(RRecType), 1, fp);
    fclose(fp);
    //�軹���ļ�
    fp = fopen("bbff", "wb");
    for (i = 1; i <= bbf.len; i++)
        fwrite(&bbf.Bbook[i], sizeof(BbookRecType), 1, fp);
    fclose(fp);
}


/*�������ļ�*/
void readfile(BookDbaseFile *bf, BnoIdxFile *bif, LHFile1 *f1, LHFile2 *f2, LHFile3 *f3, ReadFile *rf, BbookFile *bbf)
{
    FILE *fp;
    int i;
    //��ͼ�����ļ�
    fp = fopen("book", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&bf->BookDbase[i], sizeof(BookRecType), 1, fp);
        i++;
        if (feof(fp))break;
    }
    bf->len = i - 2;
    fclose(fp);
    //����������ļ�
    fp = fopen("bidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&bif->BnoIdx[i], sizeof(BidxRecType), 1, fp);
        i++;
    }
    bif->len = i - 2;
    fclose(fp);
    //�����������ļ�
    fp = fopen("nidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f1->LHFrecl[i], sizeof(BNRecType), 1, fp);
        i++;
    }
    f1->len1 = i - 2;
    fclose(fp);
    //�����������ļ�
    fp = fopen("aidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f2->LHFrec2[i], sizeof(BARecType), 1, fp);
        i++;
    }
    f2->len2 = i - 2;
    fclose(fp);
    //��������������ͷ�ļ�
    fp = fopen("pidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f3->LHFrec3[i], sizeof(BPRecType), 1, fp);
        i++;
    }
    f3->len3 = i - 2;
    fclose(fp);
    //�������ļ�
    fp = fopen("read", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&rf->ReadRec[i], sizeof(RRecType), 1, fp);
        i++;
    }
    rf->len = i - 2;
    fclose(fp);
    //���軹���ļ�
    fp = fopen("bbff", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&bbf->Bbook[i], sizeof(BbookRecType), 1, fp);
        i++;
    }
    bbf->len = i - 2;
    fclose(fp);
}

/*���ز˵�*/
int main(void)
{
    int j, m, k = 1;
    char xz = 'n';
    BookDbaseFile bf;
    BnoIdxFile bif;
    LHFile1 f1;
    LHFile2 f2;
    LHFile3 f3;
    ReadFile rf;
    BbookFile bbf;
    while (k <= 5)
    {
        printf("ͼ�����ϵͳ\n");
        printf("============\n");
        printf(" 1.ϵͳά�� \n");
        printf(" 2.���߹��� \n");
        printf(" 3.ͼ����� \n");
        printf(" 4.ͼ����ͨ \n");
        printf(" 5.�˳�ϵͳ \n");
        printf("============\n");
        printf(" ��ѡ��1-5��");
        scanf("%d", &k);
        switch (k)
        {
            case 1:
                printf("ϵͳά��\n");
                printf("--------\n");
                printf("1.��ʼ��\n");
                printf("2. �� ��\n");
                printf("--------\n");
                printf("��ѡ��\n");
                scanf("%d", &m);
                switch (m)
                {
                case 1:
                    printf("��ʼ��ֻ����һ�Σ������أ���ʼ����y/n:");
                    getchar();
                    scanf("%c", &xz);
                    if ( xz == 'y' || xz == 'Y')
                    {
                        bf.len = bif.len = f1.len1 = f2.len2 = 0;
                        f3.len3 = rf.len = bbf.len = 0;
                    }
                    break;

                case 2:
                    readfile(&bf, &bif, &f1, &f2, &f3, &rf, &bbf);
                    break;
                }
                break;

            case 2:
                ReaderManage(rf);
                break;

            case 3:
                printf("ͼ�������ϵͳ\n");
                printf("--------------\n");
                printf("1.ͼ����Ϣ����\n");
                printf("2.ͼ����Ϣ��ѯ\n");
                printf("--------------\n");
                printf("  �� ѡ �� ��");
                scanf("%d", &j);
                if (j == 1)
                {
                    char yn = 'y';
                    int k = 1;
                    while (yn = 'y' || yn == 'Y')
                    {
                        bf = AppeDBaseRec(bf);
                        bif = ChangeBnoIdxF(bf, bif);
                        f1 = ChangeLinkHeadF1(&bf, f1);
                        f2 = ChangeLinkHeadF2(&bf, f2);
                        f3 = ChangeLinkHeadF3(&bf, f3);
                        ShowRec(bf, k);
                        k++;
                        printf("����������y/n:");
                        getchar();
                        scanf("%c", &yn);
                    }
                }
                else
                    SearchBook(bf, bif, f1, f2, f3);
                break;

            case 4:
                    printf("ͼ����ͨ��ϵͳ\n");
                    printf("--------------\n");
                    printf(" 1. ���鴦��  \n");
                    printf(" 2. ���鴦��  \n");
                    printf("--------------\n");
                    printf("  �� ѡ �� :  \n");
                    scanf("%d", &j);
                    if (j == 1)
                        BorrowBook(&bf, bif, &bbf, &rf);
                    else if (j == 2)
                        BackBook(&bf, bif, &bbf, &rf);
                    break;

                case 5:
                    printf("ϵͳ����д�̣����Ժ�......\n");
                    writefile(bf, bif, f1, f2, f3, rf, bbf);
                    printf("�ټ���\n");
                    return 0;
        }

    }
}


