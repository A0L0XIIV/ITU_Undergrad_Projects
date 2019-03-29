n=1;
amax=1000;
eps=0.1;
nvals=n;
a=0;
while eps>=1e-10&a<=amax
    m=n-(40*x^1.5 - 875*n + 35000)/(60*x^0.5 - 875);
    nvals=[nvals;m];
    eps=abs(m-n);
    n=m;
    a=a+1;
end
