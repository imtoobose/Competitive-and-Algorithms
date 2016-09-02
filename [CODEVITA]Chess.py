from sys import stdin, stdout
for line in stdin:
  line= line.rstrip().lstrip()
  if (len(line)>0):
    thestr, player = (woo.readline().lstrip().rstrip().split())


#thestr, player = (woo.readline().lstrip().rstrip().split())
arrstr = thestr.split('/')
board   = [['X' for x in range(8)] for x in range(8)]
knights = []

row=0
for i in arrstr:
  col=0
  for j in i:
    if 48<=ord(j)<=57:
      for k in range(ord(j)-48):
        board[row][col]='X'
        col+=1
    else:
      if player=='w' and j =='N':
        knights.append([row, col])
      elif player=='b' and j=='n':
        knights.append([row, col])
      if 65<=ord(j)<=90:
        j='w'
      else:
       j = 'b'
      board[row][col]= j
      col+=1
  row+=1
answers=[]
#up left
#up right
#left up
#right up
#left down
#right down
#bottom left 
#bottom down

for i in knights:
  posrow = str(8- i[0])
  poscol = unichr(97+ i[1])
  pos    = poscol+posrow
  #print i[0], i[1], pos
  moves=[]

  #move up left
  if i[0]-2>=0:
    #move left
    if i[1]-1>=0:
      val= board[i[0]-2][i[1]-1]
      if val=='X' or (not val==player):
        moves.append([i[0]-2, i[1]-1])
  #up right
  if i[0]-2>=0:
    if i[1]+1<=7:
      val= board[i[0]-2][i[1]+1]
      if val=='X' or (not val==player):
        moves.append([i[0]-2, i[1]+1])

  if i[1]-2 >=0:
    #move up
    if i[0]-1>=0:
      val= board[i[0]-1][i[1]-2]
      if val=='X' or (not val==player):
        moves.append([i[0]-1, i[1]-2])
  #right up
  if i[1]+2<=7:
    if i[0]-1>=0:
      val= board[i[0]-1][i[1]+2]
      if val=='X' or (not val==player):
        moves.append([i[0]-1, i[1]+2])
  #left down
  if i[1]-2>=0:
    if i[0]+1<=7:
      val= board[i[0]+1][i[1]-2]
      if val=='X' or (not val==player):
        moves.append([i[0]+1, i[1]-2])    
  #right down
  if i[1]+2<=7:
    if i[0]+1<=7:
      val= board[i[0]+1][i[1]+2]
      if val=='X' or (not val==player):
        moves.append([i[0]+1, i[1]+2])  
  #down left
  if i[0]+2<=7:
    if i[1]-1>=0:
      val= board[i[0]+2][i[1]-1]
      if val=='X' or (not val==player):
        moves.append([i[0]+2, i[1]-1])
  #down right
  if i[0]+2<=7:
    if i[1]+1>=0:
      val= board[i[0]+2][i[1]+1]
      if val=='X' or (not val==player):
        moves.append([i[0]+2, i[1]+1])
  for kkk in moves:
    foorow= str(8- kkk[0])
    foocol = unichr(97+ kkk[1])
    foo = pos+foocol+foorow
    answers.append(foo)
stdout.write('[')
for i in range(len(answers)-1):
  stdout.write(answers[i])
  stdout.write(', ')
stdout.write(answers[len(answers)-1])
stdout.write(']')
