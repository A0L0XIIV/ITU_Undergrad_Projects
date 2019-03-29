a(i) [1 20]
i = 1;
x = 1.2;
h = 10^-20;

while h>=1
    a(i) = ( sin(x+h)-sin(x) ) / h
    h = h * 10
    i = i + 1
end
