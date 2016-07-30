from sys import stdin, stdout
inversions=0
def mergesort(arr):
  if len(arr)==0 or len(arr)==1:
    return arr
  a= mergesort(arr[0: len(arr)//2])
  b= mergesort(arr[len(arr)//2: len(arr)])
  return merge(a,b)

def merge(a, b):
  c= []
  global inversions
  while len (a)>0 and len(b)>0:
    if(a[0]<b[0]):
      c.append(a[0])
      a.pop(0)
    else:
      c.append(b[0])
      b.pop(0)
      inversions+= len(a)

  while(len(a)>0):
    c.append(a[0])
    a.pop(0)
  while(len(b)>0):
    c.append(b[0])
    b.pop(0)

  return c

arr = []
with open ('intarray.txt', 'r') as f:
  for line in f:
    arr.append(int(line))
    
v= mergesort(arr)
print(inversions)
