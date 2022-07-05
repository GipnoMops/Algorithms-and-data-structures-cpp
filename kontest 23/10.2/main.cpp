#include <stdio.h>
#include <stdlib.h>

#define NN 10000
#define MM 1000

int a[MM],b[MM],c[MM];
int x[NN],y[NN];
int res[NN];
int res2[NN];
FILE *fi, *fo;
int n,m,r;

int sgn(int x) {
    return (x>0)?(1):(-1);
}

int cmp(int j1, int j2) {
    int i;
    for(i=0;i<m;i++) {
        if(sgn(a[i]*x[j1]+b[i]*y[j1]+c[i])!=sgn(a[i]*x[j2]+b[i]*y[j2]+c[i]))
            return 0;
    }
    return 1;
}

int main(void) {
    int i,j;
    int p1,p2;
    fi=fopen("candles.in","r");
    fo=fopen("candles.out","w");

    fscanf(fi,"%d%d%d",&n,&m,&r);
    for(i=0;i<n;i++) {
        res[i]=i;
        fscanf(fi,"%d%d",&x[i],&y[i]);
    }
    for(i=0;i<m;i++) {
        fscanf(fi,"%d%d%d",&a[i],&b[i],&c[i]);
    }
    for(j=0;j<m;j++) {
        r=0;
        for(i=0;i<n;i++) {
            if(a[j]*x[i]+b[j]*y[i]+c[j]==0) return 1;
            if(a[j]*x[i]+b[j]*y[i]+c[j]<0)
                r++;
            res2[i]=res[i];
        }
        p1=0;
        p2=r;
        for(i=0;i<n;i++) {
            if(a[j]*x[res2[i]]+b[j]*y[res2[i]]+c[j]<0)
                res[p1++]=res2[i];
            else
                res[p2++]=res2[i];
        }
    }
    for(i=1;i<n;i++) {
        if(cmp(res[i-1],res[i])) {
            fprintf(fo,"YES\n");
            fclose(fi);
            fclose(fo);
            return 0;
        }
    }
    fprintf(fo,"NO\n");

    fclose(fi);
    fclose(fo);
    return 0;
}