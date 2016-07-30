from sys import stdin, stdout
import queue
t= int(stdin.readline())
for y in range(t):
    n, e= map(int, stdin.readline().rstrip().split())
    arr= [[0 for x in range (n)]for x in range (n)]
    for i in range (e):
        x,y= map(int, stdin.readline().rstrip().split())
        arr[x-1][y-1]=1
        arr[y-1][x-1]=1
    s= int(stdin.readline())
    val= [-1 for x in range (n)]
    #bfs
    q= queue.Queue(maxsize=0)
    q.put(s)
    val[s-1]=0
    while(not q.empty()):
        p=q.get()
        for v in range (n):
            if arr[p-1][v] ==1:
                if val[v]==-1:
                    val[v]= val[p-1]+6
                    q.put(v+1)
                    
                    
    del val[s-1]
    for jj in val:
        stdout.write(str(jj))
        stdout.write(" ")
    stdout.write("\n")
