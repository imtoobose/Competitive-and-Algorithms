from sys import stdin, stdout
count =1
arr = []
chars = []
for line in stdin:
    if not line.strip():
        continue
    else:
        if count == 1:
            try:
                #arr = [(x) if x.strip() for x in line.strip().split('|')]
                for w in line.strip().split('|'):
                    if w.strip():
                        arr.append(w)
                count = 2
                if arr[len(arr)-1]=="-1" or len(arr[len(arr)-1])<1:
                    count = 1
                    raise ValueError
            except:
                break
        elif count == 2:
            try:
                chars = list(line.strip())
                break
            except:
                count=1
                break

if len(chars)<10 or len(set(chars))<10 or count<2 or len(arr)<11:
    stdout.write("-1")
else:
    #print (arr)
    poses = {}
    for w in range(len(arr)-1):
        if len(arr[w])>1:
            for i in range(len(arr[w])-1):
                poses[int(arr[w][i])]= int(arr[w][len(arr[w])-1])
    toadd= arr[len(arr)-1]
    for w in range(len(toadd)-1):
        poses[int(toadd[w])]+=10
    firstval = int(toadd[len(toadd)-1])
    for i in range(len(poses)-1, -1, -1):
        poses[i]-= firstval;
        firstval = poses[i]
    #print(poses)
    for i in poses:
        stdout.write(chars[poses[i]])
