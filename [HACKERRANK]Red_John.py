from sys import stdin,stdout
import math
t= int(stdin.readline())
while t>0:
	n = int (stdin.readline())
	m=[0 for x in range (n+1)]
	m[0]=1
	m[1]=1
	def func (n):
		for i in range (2,n+1):
			x= m[i-4] if i-4>=0 else 0
			y= m[i-1] if i-1>=0 else 0
			m[i]=x+y
		return m[n]
    
	val= func(n)
	
	notprime= [0 for x in range (val+1)]
	notprime[0]=1
	notprime[1]=1
	for i in range (2, int(math.sqrt(val))+1):
		for j in range (i*i, val+1, i):
			notprime[j]=1
		                
	    
	ans= int(notprime.count(0))
	stdout.write(str(ans))
	stdout.write("\n")
	t=t-1
