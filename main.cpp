#include <fstream>
#include <bits\stdc++.h>
using namespace std;
ifstream fin("joc.in.c");
ofstream fout("joc.out.c");
short int v[8][8][5950], n=0, xra=0, yra=4, xrn=7, yrn=4, m=0;
bool ra[5950], rn[5950], tsa[5950], tda[5950], tsn[5950], tdn[5950], w;

bool deplasare(short int i1, short int j1, short int i2, short int j2)
{
    if(j1!=j2)
        return 0;
    if((i1-i2)*pow(-1, n)>=0)
        return 0;
    if(abs(i2-i1)>2)
        return 0;
    if(v[i2][j2][n]!=0)
        return 0;
    if(i2==i1+2)
        if(v[i1+1][j1][n]!=0)
            return 0;
    if(i2==i1-2)
        if(v[i1-1][j1][n]!=0)
            return 0;
    return 1;
}
bool atac(short int i1, short int j1, short int i2, short int j2)
{
    if((i2-i1)*pow(-1, n)!=1)
        return 0;
    if(abs(j2-j1)!=1)
        return 0;
    if(v[i1][j1][n]*v[i2][j2][n]>=0)
        return 0;
    return 1;
}
bool passant(short int i1, short int j1, short int i2, short int j2)
{
    if(abs(v[i1][j1][n])!=1)
        return 0;
    if((i2-i1)*pow(-1, n)!=1)
        return 0;
    if(abs(j2-j1)!=1)
        return 0;
    if(v[i1][j2][n]*v[i1][j1][n]!=-1)
        return 0;
    if(v[i2+int(pow(-1, n))][j2][n]!=0)
        return 0;
    if(v[i1][j2][n-1]!=0)
        return 0;
    if(v[i2+int(pow(-1, n))][j2][n-1]*v[i1][j1][n]!=-1)
        return 0;
    return 1;
}
bool pion(short int i1, short int j1, short int i2, short int j2)
{
    if((deplasare(i1, j1, i2, j2)==1) || (atac(i1, j1, i2, j2)==1) || (passant(i1, j1, i2, j2)==1))
        return 1;
    return 0;
}

bool linie(short int i1, short int j1, short int i2, short int j2)
{
    short int j;
    if(i1!=i2)
        return 0;
    if(j1==j2)
        return 0;
    if(v[i1][j1][n]*v[i2][j2][n]>0)
        return 0;
    if(j2-j1>1)
        for(j=j1+1; j<j2; j++)
            if(v[i1][j][n]!=0)
                return 0;
    if(j1-j2>1)
        for(j=j2+1; j<j1; j++)
            if(v[i1][j][n]!=0)
                return 0;
    return 1;
}
bool coloana(short int i1, short int j1, short int i2, short int j2)
{
    short int i;
    if(j1!=j2)
        return 0;
    if(i1==i2)
        return 0;
    if(v[i1][j1][n]*v[i2][j2][n]>0)
        return 0;
    if(i2-i1>1)
        for(i=i1+1; i<i2; i++)
            if(v[i][j1][n]!=0)
                return 0;
    if(i1-i2>1)
        for(i=i2+1; i<i1; i++)
            if(v[i][j2][n]!=0)
                return 0;
    return 1;
}
bool tura(short int i1, short int j1, short int i2, short int j2)
{
    if((coloana(i1, j1, i2, j2)==1) || (linie(i1, j1, i2, j2)==1))
        return 1;
    return 0;
}
bool cal(short int i1, short int j1, short int i2, short int j2)
{
    if(v[i1][j1][n]*v[i2][j2][n]>0)
        return 0;
    if((j2==j1-2) && (i2==i1+1))
        return 1;
    if((j2==j1-1) && (i2==i1+2))
        return 1;
    if((j2==j1+1) && (i2==i1+2))
        return 1;
    if((j2==j1+2) && (i2==i1+1))
        return 1;
    if((j2==j1+2) && (i2==i1-1))
        return 1;
    if((j2==j1+1) && (i2==i1-2))
        return 1;
    if((j2==j1-1) && (i2==i1-2))
        return 1;
    if((j2==j1-2) && (i2==i1-1))
        return 1;
    return 0;
}
bool nebun(short int i1, short int j1, short int i2, short int j2)
{
    short int i;
    if(i1==i2)
        return 0;
    if(abs(j2-j1)!=abs(i2-i1))
        return 0;
    if(v[i1][j1][n]*v[i2][j2][n]>0)
        return 0;
    if(i2>i1)
    {
        if(j2-j1>1)
            for(i=i1+1; i<i2; i++)
                if(v[i][i-i1+j1][n]!=0)
                    return 0;
        if(j1-j2>1)
            for(i=i1+1; i<i2; i++)
                if(v[i][j1+i1-i][n]!=0)
                    return 0;
    }
    if(i2<i1)
    {
        if(j2-j1>1)
            for(i=i2+1; i<i1; i++)
                if(v[i][j1+i1-i][n]!=0)
                    return 0;
        if(j1-j2>1)
            for(i=i2+1; i<i1; i++)
                if(v[i][i-i1+j1][n]!=0)
                    return 0;
    }
    return 1;
}
bool regen(int i1, int j1, int i2, int j2)
{
    if(abs(i1-i2)<=1)
        if(abs(j1-j2)<=1)
            if(v[i1][j1][n]*v[i2][j2][n]<=0)
                if((abs(i1-i2)==1) || (abs(j1-j2)==1))
                    return 1;
    return 0;
}
bool regina(short int i1, short int j1, short int i2, short int j2)
{
    if((tura(i1, j1, i2, j2)==1) || (nebun(i1, j1, i2, j2)==1))
        return 1;
    return 0;
}
bool piesagen(short int i1, short int j1, short int i2, short int j2)
{
    if(abs(v[i1][j1][n])==1)
        return pion(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==2)
        return tura(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==3)
        return cal(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==4)
        return nebun(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==5)
        return regen(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==6)
        return regina(i1, j1, i2, j2);
    return 0;
}
bool sah(short int x, short int y)
{
    short int i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            if(abs(v[i][j][n])==1)
            {
                if(atac(i, j, x, y)==1)
                    return 1;
            }
            else
            {
                if(piesagen(i, j, x, y)==1)
                    return 1;
            }
        }
    return 0;
}
bool mic(short int i1, short int j1, short int i2, short int j2)
{
    bool x=1;
    if(i1!=i2)
        return 0;
    if(j2!=j1+2)
        return 0;
    if(v[i1][j1+1][n]!=0)
        return 0;
    if(v[i2][j2][n]!=0)
        return 0;
    if(sah(i1, j1)==1)
        return 0;
    v[i1][j1+1][n]=pow(-1, n);
    if(sah(i1, j1+1)==1)
        x=0;
    v[i1][j1+1][n]=0;
    if(x==0)
        return 0;
    if(j1!=4)
        return 0;
    if(n%2==0)
    {
        if(i1!=0)
            return 0;
        if(ra[n]!=0)
            return 0;
        if(tda[n]!=0)
            return 0;
    }
    if(n%2==1)
    {
        if(i1!=7)
            return 0;
        if(rn[n]!=0)
            return 0;
        if(tdn[n]!=0)
            return 0;
    }
    return 1;
}
bool mare(short int i1, short int j1, short int i2, short int j2)
{
    bool x=1;
    if(i1!=i2)
        return 0;
    if(j2!=j1-2)
        return 0;
    if(v[i1][j1-1][n]!=0)
        return 0;
    if(v[i2][j2][n]!=0)
        return 0;
    if(v[i1][j1-3][n]!=0)
        return 0;
    if(sah(i1, j1)==1)
        return 0;
    v[i1][j1-1][n]=pow(-1, n);
    if(sah(i1, j1-1)==1)
        x=0;
    v[i1][j1-1][n]=0;
    if(x==0)
        return 0;
    if(j1!=4)
        return 0;
    if(n%2==0)
    {
        if(i1!=0)
            return 0;
        if(ra[n]!=0)
            return 0;
        if(tsa[n]!=0)
            return 0;
    }
    if(n%2==1)
    {
        if(i1!=7)
            return 0;
        if(rn[n]!=0)
            return 0;
        if(tsn[n]!=0)
            return 0;
    }
    return 1;
}
bool rege(short int i1, short int j1, short int i2, short int j2)
{
    if((regen(i1, j1, i2, j2)==1) || (mic(i1, j1, i2, j2)==1) || (mare(i1, j1, i2, j2)==1))
        return 1;
    return 0;
}
bool piesa(short int i1, short int j1, short int i2, short int j2)
{
    if(abs(v[i1][j1][n])==1)
        return pion(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==2)
        return tura(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==3)
        return cal(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==4)
        return nebun(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==5)
        return rege(i1, j1, i2, j2);
    if(abs(v[i1][j1][n])==6)
        return regina(i1, j1, i2, j2);
    return 0;
}
bool autosah(short int i1, short int j1, short int i2, short int j2)
{
    short int xr, yr, i, j;
    bool x;
    if(pow(-1, n)==1)
    {
        xr=xra;
        yr=yra;
    }
    if(pow(-1, n)==-1)
    {
        xr=xrn;
        yr=yrn;
    }
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            v[i][j][n+1]=v[i][j][n];
    v[i1][j1][n+1]=0;
    v[i2][j2][n+1]=v[i1][j1][n];
    if(passant(i1, j1, i2, j2)==1)
        v[i1][j2][n+1]=0;
    if(mic(i1, j1, i2, j2)==1)
    {
        v[i1][5][n+1]=v[i1][7][n];
        v[i1][7][n+1]=0;
    }
    if(mare(i1, j1, i2, j2)==1)
    {
        v[i1][3][n+1]=v[i1][0][n];
        v[i1][0][n+1]=0;
    }
    n++;
    if((i1==xr) && (j1==yr))
    {
        xr=i2;
        yr=j2;
    }
    x=sah(xr, yr);
    n--;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            v[i][j][n+1]=0;
    return x;
}
bool corect(short int i1, short int j1, short int i2, short int j2)
{
    if(piesa(i1, j1, i2, j2)==0)
        return 0;
    if(autosah(i1, j1, i2, j2)==1)
        return 0;
    if(v[i1][j1][n]*pow(-1, n)<=0)
        return 0;
    return 1;
}
bool mat(short int x, short int y)
{
    short int i, j, k, l;
    if(sah(x, y)==0)
        return 0;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            for(k=0; k<8; k++)
                for(l=0; l<8; l++)
                    if(corect(i, j, k, l)==1)
                        return 0;
    return 1;
}
bool pat(short int x, short int y)
{
    short int i, j, k, l;
    if(sah(x, y)==1)
        return 0;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            for(k=0; k<8; k++)
                for(l=0; l<8; l++)
                    if(corect(i, j, k, l)==1)
                        return 0;
    return 1;
}
bool insuficient()
{
    short int i, j, cai=0, nebuni=0, xneb[2], yneb[2], k=0;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            if(abs(v[i][j][n])==1)
                return 0;
            if(abs(v[i][j][n])==2)
                return 0;
            if(abs(v[i][j][n])==6)
                return 0;
            if(abs(v[i][j][n])==3)
                cai++;
            if(cai==2)
                return 0;
            if(abs(v[i][j][n])==4)
                nebuni++;
            if(nebuni==3)
                return 0;
        }
    if((cai!=0) && (nebuni!=0))
        return 0;
    if(nebuni==2)
    {
        for(i=0; i<8; i++)
            for(j=0; j<8; j++)
                if(abs(v[i][j][n])==4)
                {
                    xneb[k]=i;
                    yneb[k]=j;
                    k++;
                }
        if(v[xneb[0]][yneb[0]][n]*v[xneb[1]][yneb[1]][n]>0)
            return 0;
        if((xneb[0]+yneb[0]+xneb[1]+yneb[1])%2==1)
            return 0;
    }
    return 1;
}
bool pozitii3()
{
    short int i, j, k, s=0, cn=n;
    bool t=1, pas;
    for(k=n%2; k<n; k+=2)
    {
        for(i=0; i<8; i++)
            for(j=0; j<8; j++)
            {
                if(v[i][j][k]!=v[i][j][n])
                    t=0;
                if(abs(v[i][j][k])==1)
                {
                    pas=passant(i, j, i+pow(-1, n), j+1);
                    n=k;
                    if(pas!=passant(i, j, i+pow(-1, n), j+1))
                        t=0;
                    n=cn;
                    pas=passant(i, j, i+pow(-1, n), j-1);
                    n=k;
                    if(pas!=passant(i, j, i+pow(-1, n), j-1))
                        t=0;
                    n=cn;
                }
            }
        pas=mic(4, 0, 6, 0);
        n=k;
        if(pas!=mic(4, 0, 6, 0))
            t=0;
        n=cn;
        pas=mare(4, 0, 2, 0);
        n=k;
        if(pas!=mare(4, 0, 2, 0))
            t=0;
        n=cn;
        pas=mic(4, 7, 6, 7);
        n=k;
        if(pas!=mic(4, 7, 6, 7))
            t=0;
        n=cn;
        pas=mare(4, 7, 2, 7);
        n=k;
        if(pas!=mare(4, 7, 2, 7))
            t=0;
        n=cn;
        if(t==1)
            s++;
        t=1;
        if(s==2)
            return 1;
    }
    return 0;
}
bool pozitii5()
{
    short int i, j, k, s=0, cn=n;
    bool t=1, pas;
    for(k=n%2; k<n; k+=2)
    {
        for(i=0; i<8; i++)
            for(j=0; j<8; j++)
                {
                    if(v[i][j][k]!=v[i][j][n])
                        t=0;
                    if(abs(v[i][j][k])==1)
                    {
                        pas=passant(i, j, i+pow(-1, n), j+1);
                        n=k;
                        if(pas!=passant(i, j, i+pow(-1, n), j+1))
                            t=0;
                        n=cn;
                        pas=passant(i, j, i+pow(-1, n), j-1);
                        n=k;
                        if(pas!=passant(i, j, i+pow(-1, n), j-1))
                            t=0;
                        n=cn;
                    }
                }
        pas=mic(4, 0, 6, 0);
        n=k;
        if(pas!=mic(4, 0, 6, 0))
            t=0;
        n=cn;
        pas=mare(4, 0, 2, 0);
        n=k;
        if(pas!=mare(4, 0, 2, 0))
            t=0;
        n=cn;
        pas=mic(4, 7, 6, 7);
        n=k;
        if(pas!=mic(4, 7, 6, 7))
            t=0;
        n=cn;
        pas=mare(4, 7, 2, 7);
        n=k;
        if(pas!=mare(4, 7, 2, 7))
            t=0;
        n=cn;
        if(t==1)
            s++;
        t=1;
        if(s==4)
            return 1;
    }
    return 0;
}
bool remiza()
{
    if(mat(xra, yra)==1)
        return 0;
    if(mat(xrn, yrn)==1)
        return 0;
    if((pat(xra, yra)==1) && (n%2==0))
        return 1;
    if((pat(xrn, yrn)==1) && (n%2==1))
        return 1;
    if(insuficient()==1)
        return 1;
    if((pozitii3()==1) && (w==1))
        return 1;
    if((m>=50) && (w==1))
        return 1;
    if(pozitii5()==1)
        return 1;
    if(m==75)
        return 1;
    return 0;
}
bool promovare(short int i1, short int j1, short int i2, short int j2)
{
    if(abs(v[i1][j1][n])==1)
        if(pion(i1, j1, i2, j2)==1)
        {
            if(n%2==0)
                if(i2==7)
                    return 1;
            if(n%2==1)
                if(i2==0)
                    return 1;
        }
    return 0;
}
int main()
{
    short int i, j, i1, j1, i2, j2, q;
    v[0][0][0]=2;
    v[0][1][0]=3;
    v[0][2][0]=4;
    v[0][3][0]=6;
    v[0][4][0]=5;
    v[0][5][0]=4;
    v[0][6][0]=3;
    v[0][7][0]=2;
    for(i=0; i<8; i++)
        v[1][i][0]=1;
    for(i=2; i<6; i++)
        for(j=0; j<8; j++)
            v[i][j][0]=0;
    for(i=0; i<8; i++)
        v[6][i][0]=-1;
    v[7][0][0]=-2;
    v[7][1][0]=-3;
    v[7][2][0]=-4;
    v[7][3][0]=-6;
    v[7][4][0]=-5;
    v[7][5][0]=-4;
    v[7][6][0]=-3;
    v[7][7][0]=-2;
    ra[0]=0;
    rn[0]=0;
    tsa[0]=0;
    tsn[0]=0;
    tda[0]=0;
    tdn[0]=0;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
            fout<<v[i][j][0]<<' ';
        fout<<'\n';
    }
    while((mat(xra, yra)==0) && (mat(xrn, yrn)==0) && (remiza()==0))
    {
        fin>>i1>>j1;
        if(v[i1][j1][n]*pow(-1, n)<=0)
            fin>>i1>>j1;
            else
                {fin>>i2>>j2;
        if(corect(i1, j1, i2, j2)==1)
        {
            for(i=0; i<8; i++)
                for(j=0; j<8; j++)
                    v[i][j][n+1]=v[i][j][n];
            v[i2][j2][n+1]=v[i1][j1][n];
            v[i1][j1][n+1]=0;
            if(passant(i1, j1, i2, j2)==1)
                v[i1][j2][n+1]=0;
            if(mic(i1, j1, i2, j2)==1)
            {
                v[i1][5][n+1]=v[i1][7][n];
                v[i1][7][n+1]=0;
            }
            if(mare(i1, j1, i2, j2)==1)
            {
                v[i1][3][n+1]=v[i1][0][n];
                v[i1][0][n+1]=0;
            }
            if((i1==xra) && (j1==yra))
            {
                xra=i2;
                yra=j2;
                ra[n+1]=1;
            }
            else
                ra[n+1]=ra[n];
            if((i1==xrn) && (j1==yrn))
            {
                xrn=i2;
                yrn=j2;
                rn[n+1]=1;
            }
            else
                rn[n+1]=rn[n];
            if((i1==0) && (j1==0))
                tsa[n+1]=1;
            else
                tsa[n+1]=tsa[n];
            if((i2==0) && (j2==0))
                tsa[n+1]=1;
            else
                tsa[n+1]=tsa[n];
            if((i1==0) && (j1==7))
                tda[n+1]=1;
            else
                tda[n+1]=tda[n];
            if((i2==0) && (j2==7))
                tda[n+1]=1;
            else
                tda[n+1]=tda[n];
            if((i1==7) && (j1==0))
                tsn[n+1]=1;
            else
                tsn[n+1]=tsn[n];
            if((i2==7) && (j2==0))
                tsn[n+1]=1;
            else
                tsn[n+1]=tsn[n];
            if((i1==7) && (j1==7))
                tdn[n+1]=1;
            else
                tdn[n+1]=tdn[n];
            if((i2==7) && (j2==7))
                tdn[n+1]=1;
            else
                tdn[n+1]=tdn[n];
            if(abs(v[i1][j1][n])==1)
                m=0;
            if(v[i2][j2][n]!=0)
                m=0;
            if(passant(i1, j1, i2, j2)==1)
                m=0;
            if(abs(v[i1][j1][n])!=1)
                if(abs(v[i2][j2][n])==0)
                    if(passant(i1, j1, i2, j2)==0)
                        m++;
            if(promovare(i1, j1, i2, j2)==1)
            {
                fin>>q;
                v[i2][j2][n+1]=q;
            }
            n++;
            fout<<'\n';
            for(i=0; i<8; i++)
            {
                for(j=0; j<8; j++)
                    fout<<v[i][j][n]<<' ';
                fout<<'\n';
            }
            fin>>w;
            if(mat(xra, yra)==1)
                fout<<'\n'<<"Negrul a castigat";
            if(mat(xrn, yrn)==1)
                fout<<'\n'<<"Albul a castigat";
            if(remiza()==1)
                fout<<'\n'<<"Remiza";
        }
    }
    }
    return 0;
}
