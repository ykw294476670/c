#include<stdio.h>
#include<string.h>

#define BookSize 100
#define BLHum 50
#define BLHnum 50
#define RRnum 50

/*主数据库文件*/
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


/*书号索引文件*/
typedef struct {
    int bno;
    int RecNo;
}BidxRecType;
typedef struct {
    BidxRecType BnoIdx[BookSize];
    int len;
}BnoIdxFile;


/*书名链头索引文件*/
typedef struct {
    char bname[21];
    int lhead;
    int RecNum;
}BNRecType;
typedef struct {
    BNRecType LHFrecl[BLHum];
    int len1;
}LHFile1;


/*作者链头索引文件*/
typedef struct {
    char author[9];
    int lhead;
    int RecNum;
}BARecType;
typedef struct {
    BARecType LHFrec2[BLHnum];
    int len2;
}LHFile2;


/*出版社链头索引问件*/
typedef struct {
    char press[11];
    int lhead;
    int RecNum;
}BPRecType;
typedef struct {
    BPRecType LHFrec3[BLHnum];
    int len3;
}LHFile3;


/*读者文件*/
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


/*借还书文件*/
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


/*追加一条图书记录建立相关文件*/
BookDbaseFile AppeDBaseRec(BookDbaseFile df)
{
    int i;
    printf("书号  书名  作者名 出版社 分类  藏书量\n");
    scanf("%d%s", df.BookDbase[i].bno, df.BookDbase[i].bname);
    scanf("%s%s", df.BookDbase[i].author, df.BookDbase[i].press);
    scanf("%s %d", df.BookDbase[i].sortno, &df.BookDbase[i].storenum);
    df.BookDbase[i].borrownum = 0;
    return df;
}

/*修改书号索引表的设计*/
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


/*修改书名索引以及书名链头索引的设计*/
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


/*修改作者索引以及作者链头索引表的设计*/
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


/*修改出版社的索引以及出版社链头索引表的设计*/
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


/*用二分查找实现书号查询算法*/
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


/*按书名查询算法的设计*/
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


/*按作者查询算法的设计*/
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



/*输出一条图书主数据库记录的设计*/
void ShowRec(BookDbaseFile df, int i)
{
    printf("书号  书名  作者名 出版社 分类号 可借数\n");
    printf("==============================================\n");
    printf("%d%12s", df.BookDbase[i].bno, df.BookDbase[i].bname);
    printf("%8s%12s", df.BookDbase[i].author, df.BookDbase[i].press);
    printf("%6s", df.BookDbase[i].sortno);
    printf("%4d\n", df.BookDbase[i].storenum - df.BookDbase[i].borrownum);
    printf("==============================================\n");
}

/*图书查询控制程序设计*/
void SearchBook(BookDbaseFile df, BnoIdxFile bif, LHFile1 f1, LHFile2 f2, LHFile3 f3)
{
    char sm[21], zz[9],cbs[11];
    int i, k, choose = 1;
    int sh;
    while (choose >= 1 && choose <= 5)
    {
        printf("图书查询子系统\n");
        printf("------------------\n");
        printf("1.书 号       2.书 名\n");
        printf("3.作 者       4.出版社\n");
        printf("5.退 出   查 询");
        printf("------------------\n");
        printf("    请 用 户 选 择：");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("输入学号：");
            scanf("%d", &sh);
            k = BinSearch(bif, sh);
            if (k == 0) {
                printf("没有要检查的图书，请检查是否输入有错\n");
                break;
            }
            ShowRec(df, k);
            break;

        case 2:
            printf("输入书名：");
            scanf("%", &sm);
            k = BnameFind(f1, sm);
            if (k == 0) {
                printf("没有要检查的图书，请检查是否输入有错\n");
                break;
            }
            for (i = k; i; i = df.BookDbase[i].namenext)
                ShowRec(df, i);
            break;

        case 3:
            printf("输入作者名：");
            scanf("%s", &zz);
            k = BauthFind(f2, zz);
            if (k == 0) {
                printf("没有要检查的图书，请检查是否输入有错\n");
                break;
            }
            for (i = k; i; i = df.BookDbase[i].authnext)
                ShowRec(df, i);
            break;

        case 4:
            printf("输入出版社：");
            scanf("%s", &cbs);
            

        case 5:
            return;
        }
    }
}


/*借还书处理算法*/
void BorrowBook(BookDbaseFile *bf, BnoIdxFile bif, BbookFile *bbf, ReadFile *rf)
{
    char jyrq[9];
    int sh, dzh;
    int i, j, k = 0;
    printf("输入读者号   书号  借阅日期\n");
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
        printf("非法读者！\n");
        return;
    }
    if (rf->ReadRec[k].bn2 >= rf->ReadRec[k].bn1)
    {
        printf("书已借满!\n");
        return;
    }
    j = BinSearch(bif, sh);
    if (j == 0)
    {
        printf("非法书号！");
            return;
    }
    if (bf->BookDbase[j].borrownum >= bf->BookDbase[j].storenum)
    {
        printf("图书已借出\n");
        return;
    }
    i = ++bbf->len;
    bbf->Bbook[i].rno = dzh;
    bbf->Bbook[i].bno = sh;
    strcpy(bbf->Bbook[i].date1, jyrq);
    rf->ReadRec[k].bn2++;
    bf->BookDbase[j].borrownum++;
    printf("借书成功！\n");
}

/*还书处理算法的设计*/
void BackBook(BookDbaseFile *bf,BnoIdxFile bif ,BbookFile *bbf, ReadFile *rf)
{
    char hsrq[8];
    int sh, dzh;
    int i, j, k = 0, m = 0;
    printf("读者号 书号  还书日期\n");
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
        printf("非法读者！\n");
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
        printf("非法书号！\n");
        return;
    }
    j = BinSearch(bif, sh);
    if (j == 0)
    {
        printf("非法书号！\n");
        return;
    }
    rf->ReadRec[k].bn2--;
    bf->BookDbase[j].borrownum--;
    strcpy(bbf->Bbook[m].date2, hsrq);
    printf("还书成功！\n");
}

/*读者管理子系统*/
ReadFile ReaderManage(ReadFile rf)
{
    int i;
    char yn = 'y';
    i = ++rf.len;
    while (yn == 'y' || yn == 'Y')
    {
        printf("输入读者号   读者名 可借图书数\n");
        scanf("%d %s", &rf.ReadRec[i].rno, rf.ReadRec[i].name);
        scanf("%d", &rf.ReadRec[i].bn1);
        rf.ReadRec[i].bn2 = 0;
        printf("继续输入吗？y/n:");
        getchar();
        scanf("%c",&yn);
    }
    rf.len=i-1;
    return rf;
}

/*写各类文件*/
void writefile(BookDbaseFile bf, BnoIdxFile bif, LHFile1 f1, LHFile2 f2, LHFile3 f3, ReadFile rf, BbookFile bbf)
{
    FILE *fp;
    int i;
    //图书主文件 
    fp = fopen("book", "wb");
    for (i = 1; i <= bf.len; i++)
        fwrite(&bf.BookDbase[i],sizeof(BookRecType), 1, fp);
    fclose(fp);
    //图书索引文件 
    fp = fopen("bidx", "wb");
    for (i = 1; i <= bif.len; i++)
        fwrite(&bif.BnoIdx[i], sizeof(BidxRecType), 1, fp);
    fclose(fp);
    //书名索引链头文件 
    fp = fopen("nidx", "wb");
    for (i = 1; i <= f1.len1; i++)
        fwrite(&f1.LHFrecl[i], sizeof(BNRecType), 1, fp);
    fclose(fp);
    //作者索引链头文件
    fp = fopen("aidx", "wb");
    for (i = 1; i <= f2.len2; i++)
        fwrite(&f2.LHFrec2[i], sizeof(BARecType), 1, fp);
    fclose(fp);
    //出版社索引链头文件
    fp = fopen("pidx", "wb");
    for (i = 1; i <= f3.len3; i++)
        fwrite(&f3.LHFrec3[i], sizeof(BPRecType), 1, fp);
    fclose(fp);
    //读者文件
    fp = fopen("read", "wb");
    for (i = 1; i <= rf.len; i++)
        fwrite(&rf.ReadRec[i], sizeof(RRecType), 1, fp);
    fclose(fp);
    //借还书文件
    fp = fopen("bbff", "wb");
    for (i = 1; i <= bbf.len; i++)
        fwrite(&bbf.Bbook[i], sizeof(BbookRecType), 1, fp);
    fclose(fp);
}


/*读各类文件*/
void readfile(BookDbaseFile *bf, BnoIdxFile *bif, LHFile1 *f1, LHFile2 *f2, LHFile3 *f3, ReadFile *rf, BbookFile *bbf)
{
    FILE *fp;
    int i;
    //读图书主文件
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
    //读书好索引文件
    fp = fopen("bidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&bif->BnoIdx[i], sizeof(BidxRecType), 1, fp);
        i++;
    }
    bif->len = i - 2;
    fclose(fp);
    //读书名索引文件
    fp = fopen("nidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f1->LHFrecl[i], sizeof(BNRecType), 1, fp);
        i++;
    }
    f1->len1 = i - 2;
    fclose(fp);
    //读作者索引文件
    fp = fopen("aidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f2->LHFrec2[i], sizeof(BARecType), 1, fp);
        i++;
    }
    f2->len2 = i - 2;
    fclose(fp);
    //读出版社索引链头文件
    fp = fopen("pidx", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&f3->LHFrec3[i], sizeof(BPRecType), 1, fp);
        i++;
    }
    f3->len3 = i - 2;
    fclose(fp);
    //读读者文件
    fp = fopen("read", "rb");
    i = 1;
    while (!feof(fp))
    {
        fread(&rf->ReadRec[i], sizeof(RRecType), 1, fp);
        i++;
    }
    rf->len = i - 2;
    fclose(fp);
    //读借还书文件
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

/*主控菜单*/
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
        printf("图书管理系统\n");
        printf("============\n");
        printf(" 1.系统维护 \n");
        printf(" 2.读者管理 \n");
        printf(" 3.图书管理 \n");
        printf(" 4.图书流通 \n");
        printf(" 5.退出系统 \n");
        printf("============\n");
        printf(" 请选择1-5：");
        scanf("%d", &k);
        switch (k)
        {
            case 1:
                printf("系统维护\n");
                printf("--------\n");
                printf("1.初始化\n");
                printf("2. 读 盘\n");
                printf("--------\n");
                printf("请选择：\n");
                scanf("%d", &m);
                switch (m)
                {
                case 1:
                    printf("初始化只能做一次，需慎重！初始化吗？y/n:");
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
                printf("图书管理子系统\n");
                printf("--------------\n");
                printf("1.图书信息输入\n");
                printf("2.图书信息查询\n");
                printf("--------------\n");
                printf("  请 选 择 ：");
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
                        printf("继续输入吗？y/n:");
                        getchar();
                        scanf("%c", &yn);
                    }
                }
                else
                    SearchBook(bf, bif, f1, f2, f3);
                break;

            case 4:
                    printf("图书流通子系统\n");
                    printf("--------------\n");
                    printf(" 1. 借书处理  \n");
                    printf(" 2. 还书处理  \n");
                    printf("--------------\n");
                    printf("  请 选 择 :  \n");
                    scanf("%d", &j);
                    if (j == 1)
                        BorrowBook(&bf, bif, &bbf, &rf);
                    else if (j == 2)
                        BackBook(&bf, bif, &bbf, &rf);
                    break;

                case 5:
                    printf("系统正在写盘，请稍后......\n");
                    writefile(bf, bif, f1, f2, f3, rf, bbf);
                    printf("再见！\n");
                    return 0;
        }

    }
}


