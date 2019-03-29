import matplotlib.pyplot as plt

#opening file
file = open("data.txt", "r")

#data list
data = []

#reading file
for line in file:
    #print(line)
    data.append(line)
#print(data)


xn = 0.0  #sum of xi for i=1 to n
xnu = 0.0 #sum of (xi-u') for i=1 to n


#for i in range (1, (len(data)+1) ):
#   xn = xn + float(data[i-1])
for item in data:
    #print(item)
    xn += float(item)

#mu
#u' = 1/n * sum i=1:n(xi)
u = 1/len(data) * xn


#for i in range (1, (len(data)+1) ):
#    xnu += pow( (data[i-1] - u), 2)
for item in data:
    xnu += (float(item)-u) * (float(item)-u)

#sigma square
#o^2' = 1/n * sum i=1:n(xi - u')^2
o2 = 1/len(data) * xnu

print(u)
print(o2)

#histogram
x = 1/(pow(2*3.14*o2, 1/2)) * pow(2.72, -(pow(x-u, 2))/2*o2 )

# the histogram of the data
n, bins, patches = plt.hist(x, 50, normed=1, facecolor='g', alpha=0.75)

plt.axis([0, 900, 0, 20])
plt.grid(True)
plt.show()

#data graph
plt.plot(data, len(data))
plt.show()


